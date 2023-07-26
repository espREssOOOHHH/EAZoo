//
// Created by Lhuna on 2023/6/2.
//

#include "QEA/QuantumGeneticAlgorithm.hpp"

#include <utility>

QuantumGeneticAlgorithm::QuantumGeneticAlgorithm(int Dimension):dimension(Dimension)
{
    if(Dimension < 1)
        throw std::logic_error("Variable dimension cannot smaller than 1!");
}


int QuantumGeneticAlgorithm::mutation(Chromosome& chromosome, const std::string& observe, const std::string& target) const
{
    if(observe.size() != target.size() or observe.size() != chromosome.length)
        throw std::runtime_error("Error occurs in observation!");
    for(auto index = 0; index < chromosome.length; index++)
    {
        if(observe[index] < target[index])
            chromosome.U(index, theta);
        else if(observe[index] > target[index])
            chromosome.U(index, -1 * theta);
        else
            ;
    }

    return 1;
}

int QuantumGeneticAlgorithm::crossOver() noexcept
{
    for(auto i = 0; i < chromosomes[0].length; i++)
        for(auto j = chromosomes.size() - 1; j > 0; j--)
            for(auto k = i; k < chromosomes[0].length; k++)
                std::swap(chromosomes[j].qBits[k],
                          chromosomes[j - 1].qBits[k]);
    return 0;
}

int QuantumGeneticAlgorithm::encoder()
{
    sub_length.resize(dimension);
    for(auto index = 0; index < dimension; index++)
    {
        auto length_interval =
                bounds_of_variables[index].UpperBound - bounds_of_variables[index].LowerBound;
        sub_length[index] = std::ceil(std::log(
                length_interval / bounds_of_variables[index].Precision) / std::log(2));
    }

    chromosomes.resize(population_size, Chromosome(std::accumulate(
            sub_length.begin(), sub_length.end(), 0)));

    return 0;
}

std::tuple<std::vector<std::string>, std::vector<double>, double>
        QuantumGeneticAlgorithm::execute(std::function<double (std::vector<double>)> EvalFunction,
                                         std::vector<Bound> BoundsOfVariables,
                                     long MaxEvolutionTime, int PopulationSize, bool DoStatistics)
{
    //init hyper args
    const auto MIN_NUM = LONG_MIN;
    eval_function = std::move(EvalFunction);
    bounds_of_variables = std::move(BoundsOfVariables);
    population_size = PopulationSize;
    max_evolution_time = MaxEvolutionTime;

    std::vector<std::string> statisticsResult;//return statistics result
    if (DoStatistics)
    {
        statisticsResult.resize(max_evolution_time+2);
        statisticsResult[0] = "index,";
        for (auto i = 0; i < dimension; i++)
        {
            statisticsResult[0] += std::to_string(i);
            statisticsResult[0] += ',';
        }
        statisticsResult[0] += "adaptibility";
    }

    //timing begin
    auto start = std::chrono::high_resolution_clock::now();

    //chromosome init
    encoder();

    //seek the best item in set and show
    auto show_best_item = [&](int turn, const std::vector<double> &val) {
        if (DoStatistics)
        {
            statisticsResult[turn+1] = std::to_string(turn) + ',';
            std::for_each(val.begin(), val.end(), [&](auto v){
                statisticsResult[turn+1] += std::to_string(v)+',';});

            if (not (turn % 100))
            {
                std::cout << "\33[2J" << std::endl;   //clear the screen
                std::cout << "\33[0;0H" << std::endl; //cursor return to start point
                std::cout << "optimizing...." << std::endl;
                std::cout << "turn " << turn << " /" << max_evolution_time << std::endl;
            }
        }
        else
        {
            std::cout << "round " << turn<<':';
            std::for_each(val.begin(), val.end(),[](auto v){std::cout<<v<<',';});
            std::cout<< std::endl;
        }
    };

    double max_adaptability = MIN_NUM;
    std::string targetStr;//best observation
    std::vector<std::string> obs_vec;//all observation
    obs_vec.reserve(chromosomes.size());
    auto obs_vec_pt = obs_vec.begin();
    auto best_chromosome_index = 0;

    auto do_observation = [&](){
        obs_vec.clear();
        obs_vec_pt = obs_vec.begin();
        std::for_each(chromosomes.begin(), chromosomes.end(),[&](const auto& item){
            auto obs = item.Observe();
            if(auto val = eval_function(decoder(obs)); val > max_adaptability)
                max_adaptability = val, targetStr = obs, best_chromosome_index = &item - &chromosomes[0];
            obs_vec.emplace(obs_vec_pt++, std::move(obs));
        });
    };

    for(auto turn  = 0; turn < max_evolution_time; turn++)
    {
        do_observation();
        obs_vec_pt = obs_vec.begin();
        for(size_t i = 0; auto & item : chromosomes)
        {
            if(best_chromosome_index == i)
                ;
            else
                mutation(item, *obs_vec_pt, obs_vec[best_chromosome_index]);
            obs_vec_pt++;
        }
        show_best_item(turn, decoder(targetStr));
        crossOver();
    }

    do_observation();
    show_best_item(max_evolution_time, decoder(targetStr));

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "time consumed is " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<<
              "s ("<<std::chrono::duration<double,std::milli>(end - start).count() <<" ms )"<< std::endl;


    return std::make_tuple(std::move(statisticsResult), std::move(decoder(targetStr)), max_adaptability);

}

std::vector<double> QuantumGeneticAlgorithm::decoder(const std::string& str)
{
    //lambda converting binary string to decimal
    auto to_decimal = [&](decltype(str.begin()) begin, decltype(begin) end){
        double val = 0;
        auto i = 0;
        for(auto pt = end - 1; pt >= begin; pt--)
        {
            val += std::pow(2, i) * (*pt == '1' ? 1 : 0);
            i++;
        }
        return val;
    };

    std::vector<double> val;
    auto pt = str.begin();
    auto bound = bounds_of_variables.begin();

    for(auto subLength : sub_length)
    {
        val.push_back(to_decimal(pt, pt + subLength) * bound->Precision + bound->LowerBound);
        bound++;
        pt += subLength;
    }


    return std::move(val);
}

