#ifndef BASEDATABASEREADER_H
#define BASEDATABASEREADER_H

#include "BaseCSVManager.h"
#include "DataBaseManager.h"
#include <iostream>
using namespace std;

class BaseDataBaseReader : public BaseCSVManager
{
public:
    BaseDataBaseReader(string sql, string database_name) : BaseCSVManager()
    {
        this->partical_name = "";
        this->current_entry = 0;
        DataBaseManager *db = new DataBaseManager();
        db->init(database_name);

        MYSQL_RES *res = db->getResult(sql);

        this->data = std::vector<std::vector<float>>();

        if (res) // 返回了结果集
        {
            int num_fields = mysql_num_fields(res); // 获取结果集中总共的字段数，即列数
            for (int i = 0; i < num_fields; i++)
            {
                this->data.push_back(std::vector<float>());
            }
            this->column_num = num_fields;

            int num_rows = mysql_num_rows(res); // 获取结果集中总共的行数
            this->total_entries = num_rows;
            for (int i = 0; i < num_rows; i++)  // 输出每一行
            {
                // 获取下一行数据
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row == NULL)
                    break;

                for (int j = 0; j < num_fields; j++) // 输出每一字段
                {
                    this->data[j].push_back(atof(row[j]));
                }
            }
        }
    }
};

#endif
