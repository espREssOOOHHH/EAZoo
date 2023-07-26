#include <iostream>
#include <exception>
#include <vector>
#include <cmath>
#include <string>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <tuple>

class GeneticAlgorithm
{
public:
	//struct and complex types

	//interval args
	struct Bound
	{
		double LowerBound;
		double UpperBound;
		double Precision;
	};

private:
	//struct and complex types

	//Chromosome
	class Chromosome
	{
	public:
		std::string str;//chromosome in string form
		unsigned int dimension;//variable number
		std::vector<double> values;//variable values
		//std::vector<size_t> sub_length;//length of each variable in chromosome
		double adaptibility;//value of eval function

	public:
		std::string show_values(bool ShowVariable=true, bool ShowAdaptibility=true,
			bool ShowChromosomeStr=false)//print essential value
		{
			std::string return_val;
			if (ShowVariable) 
			{
				for (auto item : values)
				{
					return_val += std::to_string(item) + ',';
				}
			}
			if (ShowAdaptibility)
				return_val += std::to_string(adaptibility) + ',';
			if (ShowChromosomeStr)
				return_val += str;
			return return_val;
		}
	};
	std::vector<size_t> sub_length;//length of each variable in chromosome
public:
	//construction function, must specify dimension!
	GeneticAlgorithm(unsigned int Dimension):dimension(Dimension) {};
	bool tester()
	{
		bounds_of_variables = std::vector<struct GeneticAlgorithm::Bound>{ {-5,5,0.0001}, { -5,5,0.0001 } };
		//auto result = encoder(2, std::vector<double>{-1.6707,-4.5202},bounds);

		eval_function = [](std::vector<double> v) {
			double result = 0.01; std::for_each(v.begin(), v.end(), [&](double x) {result *= x; }); return result; };
		
		std::vector<GeneticAlgorithm::Chromosome> chromosome;
		for (auto i = 1.0; i < 5; i+=0.1)
		{
			chromosome.push_back(std::move(encoder(2, { (double)i,(double)i}, bounds_of_variables)));
		}

		decltype(chromosome) result3 = roulette_selection(chromosome);

		auto ret_val=crossover(result3);
		ret_val=mutation(result3);

		return true;
	}

	//do GA execute
	std::tuple<std::vector<std::string>,std::vector<double>,double> 
		execute(std::function<double(std::vector<double>)>,
		std::vector<struct GeneticAlgorithm::Bound>, long MaxEvolutionTime,
		unsigned int PopulationSize, double ProbabilityCrossover, double ProbabilityMutation,
		bool DoStatistics);

protected:
	//methods

	GeneticAlgorithm::Chromosome encoder(unsigned int, const std::vector<double>&, const std::vector<struct GeneticAlgorithm::Bound>&);
	std::vector<double> decoder(unsigned int, const std::vector<struct GeneticAlgorithm::Bound>&, const std::string&);
	std::vector<GeneticAlgorithm::Chromosome> roulette_selection(std::vector<GeneticAlgorithm::Chromosome>& x);//roulette selection function : choose offspring chromosomes
	int crossover(std::vector<GeneticAlgorithm::Chromosome>&);//do crossover on chromosome set
	int mutation(std::vector<GeneticAlgorithm::Chromosome>&);//do mutation on chromosome set

private:
	//variables and constants

	//arguments
	unsigned int population_size;//number of chromosome
	long max_evolution_time;//number of cycles repeated
	unsigned int dimension;//variable number
	
	//encoding related
	std::vector<GeneticAlgorithm::Chromosome> chromosomes;//store all chromosome
	std::vector< GeneticAlgorithm::Bound> bounds_of_variables;//store all boundary of variables

	//evaluation related
	std::function<double(std::vector<double>)> eval_function;//evaluate function

	//crossover and mutation related
	double probability_crossover;//probability of crossover on each pair of chromosome 
	double probability_mutation;//probality of mutation on each point of gene

protected:
	//utility methods

	std::vector<double> get_random_numbers(unsigned int, struct GeneticAlgorithm::Bound={ 0, 1, 0.0000000001 });

};


