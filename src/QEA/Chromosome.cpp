//
// Created by Lhuna on 2023/6/9.
//

#include "QEA/Chromosome.hpp"


Chromosome::Chromosome(int length):length(length)
{
    qBits.resize(length);
    auto randomSet = get_random_numbers(length, 0, 1);
    auto numPt = randomSet.begin();
    for(auto &qBit : qBits)
    {
        auto num = *numPt;
        qBit = {num, std::sqrt((1 - num * num))};
        numPt++;
    }
}

std::string Chromosome::Observe() const
{
    auto randomSet = get_random_numbers(length,0,1);
    std::string result(length,'0');
    for(auto i = 0; i < length; i++)
    {
        if(randomSet[i] > std::pow(qBits[i][0],2))
            result[i] = '1';
    }
    return result;
}

std::string Chromosome::ShowRawData()
{
    std::string ret_val;
    std::stringstream ss;
    for(const auto& item : qBits)
    {
        ss << item << '\n';
    }
    return ss.str();
}

int Chromosome::U(int location, double theta)
{
    if(location < 0 or location > qBits.size())
        return -1;
    Eigen::Matrix<double,2,2> gate{
        {std::cos(theta), -1 * std::sin(theta)},
        {std::sin(theta),      std::cos(theta)}
    };
    qBits[location] = gate * qBits[location];
    return 1;
}


double Chromosome::get_a_random_number(double lower, double upper)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(lower, upper);
    return dis(gen);
}

std::vector<double> Chromosome::get_random_numbers(unsigned int N, double lower, double upper)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(lower, upper);

    std::vector<double> result(N);
    std::for_each(result.begin(), result.end(), [&](double& item) {
                      item = dis(gen);
                  }
    );
    return result;
}