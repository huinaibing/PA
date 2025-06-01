#include "ProbFilter.h"
#include <random>

ProbFilter::ProbFilter(float prob)
{
    this->prob = prob;
}

ProbFilter::~ProbFilter()
{
}

bool ProbFilter::filter(float value)
{
    std::random_device rd;  // 非确定性随机源（硬件熵）
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎
    std::uniform_int_distribution<> dis(0, 1);
    if (dis(gen) < prob)
    {
        return true;
    }
    else
    {
        return false;
    }
}