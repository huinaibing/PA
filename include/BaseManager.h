/**
 * @file BaseManager.h
 * @author Qiuyu Xia (you@domain.com)
 * @brief 所有manager的基类
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include <string>
#include "Rtypes.h"  // For Long64_t

class BaseManager
{
public:
    virtual std::string getParticalName() = 0;
    virtual Long64_t getTotalEntries() = 0;
    virtual void setCurrentEntry(Long64_t entry) = 0;
    virtual ~BaseManager() = default;
};

#endif
