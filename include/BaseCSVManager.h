/**
 * @file BaseCSVManager.h
 * @author Autumnrain Summer (you@domain.com)
 * @brief 读取以CSV格式存储数据的类
 * @details 这个数据存储在data[column][entry]中，这个类目前只能读取以空格隔开的csv文件
 * @version 0.1
 * @date 2025-07-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef BASE_CSV_MANAGER_H
#define BASE_CSV_MANAGER_H

#include "BaseManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "TROOT.h"
class BaseCSVManager : public BaseManager
{
public:
    BaseCSVManager(const char *file_path, const char *partical_name, int column_num);
    BaseCSVManager() {};
    std::string getParticalName() override;
    Long64_t getTotalEntries() override;
    void setCurrentEntry(Long64_t entry) override;
    float getDataByColumn(int column);

protected:
    std::string partical_name;
    int column_num;
    std::vector<std::vector<float>> data;
    Long64_t current_entry;
    Long64_t total_entries;
};

#endif
