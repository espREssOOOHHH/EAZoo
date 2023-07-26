#include <iostream>
#include <fstream>
#include "QEA/QuantumGeneticAlgorithm.hpp"
#include "GA/GeneticAlgorithm.hpp"
int main()
{
    auto EA_Type = "QEA";//this can be "GA" and "QEA"

    //These are parameters both GA and QEA required.
    const auto DIMENSION = 10;
    auto max_evolution_time = 100;
    auto population_size = 200;
    auto print_statistics = false;
    auto output_file_path = "./output.csv";

    //These arguments only for GA
    auto probability_crossover = 0.4;
    auto probability_mutation = 0.005;

    auto Griewanke_function = [&](std::vector<double> v){
        double result = 0;
        std::for_each(v.begin(), v.end(), [&](double i){result += pow(i,2); });
        result /= 4000;
        double production = 1;
        for(auto i = 0; i < DIMENSION; i++)
            production *= std::cos(v[i]/std::sqrt(i+1));
        result -= production;
        result += 1;
        return -std::abs(result);
    };
    auto eval_function = Griewanke_function;

    auto Print_result = [&](
            const std::vector<double>& value_result, double adaptability_result,
            const std::vector<std::string>& statistics_result) {
        std::cout << "\n result is: point (";
        for (auto val: value_result) {
            std::cout << val << "  ";
        }
        std::cout << ")" << std::endl << " adaptability is " << adaptability_result << std::endl;

        if (not print_statistics)
            return 0;

        std::fstream output_file(output_file_path);
        if (not output_file.is_open()) {
            std::cerr << "output file does not exist!" << std::endl;
            return -1;
        }
        for (auto item: statistics_result) {
            output_file << item << std::endl;
        }
        std::cout << "Result has written to  " << output_file_path << std::endl;
    };

    //NOTICE: when bounds are not equal 2**n, result may run without bound
    if("QEA" == EA_Type)
    {
        QuantumGeneticAlgorithm quantumGeneticAlgorithm(DIMENSION);
        auto bounds_of_variables = std::vector<QuantumGeneticAlgorithm::Bound>(DIMENSION, {
            -512, 512, 0.0625});
        auto [statistics_result, value_result, adaptability_result] =
                quantumGeneticAlgorithm.execute(eval_function, bounds_of_variables,
                                                max_evolution_time, population_size,
                                                print_statistics);
        Print_result(value_result, adaptability_result, statistics_result);
    }
    if("GA" == EA_Type)
    {
        GeneticAlgorithm geneticAlgorithm(DIMENSION);
        auto bounds_of_variables = std::vector<GeneticAlgorithm::Bound>(DIMENSION, {
            -512, 512, 0.0625});
        auto [statistics_result,value_result, adaptability_result]=
                geneticAlgorithm.execute(eval_function,bounds_of_variables,
                                         max_evolution_time,population_size,
                                         probability_crossover,
                                         probability_mutation,print_statistics);
        Print_result(value_result, adaptability_result, statistics_result);
    }

    return 1;
}
