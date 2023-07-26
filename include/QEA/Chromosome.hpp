//
// Created by Lhuna on 2023/6/9.
//

#ifndef ALGOTEST_CHROMOSOME_HPP
#define ALGOTEST_CHROMOSOME_HPP

#include <eigen3/Eigen/Core>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <algorithm>
#include <random>

//#include "Util.hpp"

class QuantumGeneticAlgorithm;

class Chromosome{
public:
    explicit Chromosome(int length);
    Chromosome() = delete;

    [[nodiscard]] std::string Observe() const;

    friend class QuantumGeneticAlgorithm;

    std::string ShowRawData();

    int U(int location, double theta);

protected:
    int length;//the length of chromosome
    std::vector<Eigen::Vector2d> qBits;//storage of all quantum bits

private:
    static double get_a_random_number(double lower=-1, double upper=1);
    static std::vector<double> get_random_numbers(unsigned int N,double lower=-1, double upper=1);

};


#endif //ALGOTEST_CHROMOSOME_HPP
