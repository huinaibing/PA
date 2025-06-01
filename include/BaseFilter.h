#ifndef FILTER_H
#define FILTER_H

#include <functional>

class BaseFilter
{
public:
    BaseFilter();
    ~BaseFilter();

    virtual bool filter(float value) = 0;
};

#endif
