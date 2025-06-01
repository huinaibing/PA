#include "BaseCSVManager.h"

BaseCSVManager::BaseCSVManager(const char *file_path, const char *partical_name, int column_num)
{
    this->partical_name = partical_name;
    this->column_num = column_num;
    this->data = std::vector<std::vector<float>>();

    for (int i = 0; i < column_num; i++)
    {
        this->data.push_back(std::vector<float>());
    }

    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return;
    }

    float tmp;
    while (file >> tmp) {  // Read first value
        this->data[0].push_back(tmp);
        
        // Read remaining values for this row
        bool row_complete = true;
        for (int i = 1; i < column_num; i++) {
            if (!(file >> tmp)) {
                row_complete = false;
                break;
            }
            this->data[i].push_back(tmp);
        }
        
        if (!row_complete) {
            std::cerr << "Warning: Incomplete row in file " << file_path << std::endl;
            break;
        }
    }

    this->total_entries = this->data[0].size();
    this->current_entry = 0;

    file.close();
}

std::string BaseCSVManager::getParticalName()
{
    return this->partical_name;
}

Long64_t BaseCSVManager::getTotalEntries()
{
    return this->total_entries;
}

void BaseCSVManager::setCurrentEntry(Long64_t entry)
{
    this->current_entry = entry;
}

float BaseCSVManager::getDataByColumn(int column)
{
    return this->data[column][this->current_entry];
}
