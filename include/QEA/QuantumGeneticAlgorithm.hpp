//
// Created by Lhuna on 2023/6/2.
//

#ifndef ALGOTEST_QUANTUMGENETICALGORITHM_HPP
#define ALGOTEST_QUANTUMGENETICALGORITHM_HPP

#include "QEA/Chromosome.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <functional>
#include <exception>
#include <chrono>
#include <tuple>

class QuantumGeneticAlgorithm{
public:
    //struct and complex types

    //interval args
    //Please make sure [UpperBound - LowerBound]/Precision be the form of 2^n,
    //Or the algorithm may run out of the bound.
    struct Bound
    {
        double LowerBound;
        double UpperBound;
        double Precision;
    };
public:
    explicit QuantumGeneticAlgorithm(int Dimension);
    std::tuple<std::vector<std::string>, std::vector<double>, double> execute(
            std::function<double (std::vector<double>)> EvalFunction, std::vector<Bound> BoundsOfVariables,
                long MaxEvolutionTime, int PopulationSize, bool DoStatistics);

private:
    //variables and constants

    //arguments
    unsigned int population_size;//number of chromosome
    long max_evolution_time;//number of cycles repeated
    unsigned int dimension;//variable number
    double theta = 0.1 * std::numbers::pi;//the angle qubit rotates

    //encoding related
    std::vector<Chromosome> chromosomes;//store all chromosome
    std::vector<Bound> bounds_of_variables;//store all boundary of variables
    std::vector<int> sub_length;//length of each variable in chromosome

    //evaluation related
    std::function<double(std::vector<double>)> eval_function;//evaluate function
protected:
    int mutation(Chromosome&, const std::string& observe, const std::string& target) const;//do mutation on chromosome set
    int crossOver() noexcept;//do cross over on chromosome set

    //inner methods
protected:
    int encoder();//encoding all chromosomes
    std::vector<double> decoder(const std::string&);//decoding observation into values

};


#endif //ALGOTEST_QUANTUMGENETICALGORITHM_HPP
