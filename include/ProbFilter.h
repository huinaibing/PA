#ifndef PROB_FILTER_H
#define PROB_FILTER_H

#include "BaseFilter.h"
class ProbFilter : public BaseFilter
{
public:
    ProbFilter(float prob);
    ~ProbFilter();
    bool filter(float value);

private:
    float prob;
};

#endif