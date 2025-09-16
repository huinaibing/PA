/**
 * @file IterableBaseManager.h
 * @author Qiu yu Xia (you@domain.com)
 * @brief 可迭代的基类，设计中以后估计会用
 * @version 0.1
 * @date 2025-09-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef ITERABLE_BASE_MANAGER_H
#define ITERABLE_BASE_MANAGER_H

#include <cstdint>
#include <string>

template <typename T>
class IterableBaseManagerIterator;

template <typename T>
class IterableBaseManager
{
public:
    using Iterator = IterableBaseManagerIterator<T>;
    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;

    virtual string getParticleName() = 0;
};

template <typename T>
class IterableBaseManagerIterator {
public:
    virtual T& operator*() = 0;          
    virtual IterableBaseManagerIterator& operator++() = 0; 
    virtual bool operator!=(const IterableBaseManagerIterator& other) const = 0; 
    virtual ~IterableBaseManagerIterator() = default;
};

#endif
