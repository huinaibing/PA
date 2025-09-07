#include "DataBaseManager.h"
using namespace std;


bool DataBaseManager::init(std::string db_name, std::string host, std::string user, std::string passwd)
{
    mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), 0, NULL, 0);
    if (mysql == NULL)
    {
        std::cout << "Error: " << mysql_error(mysql);
        return false;
    }
    return true;
}

MYSQL_RES* DataBaseManager::getResult(string sql)
{
    if (mysql_query(mysql, sql.c_str()))
    {
        std::cout << "Query Error: " << mysql_error(mysql);
        return nullptr;
    }

    return mysql_store_result(mysql);
}

bool DataBaseManager::simpleGetResultFromSQL(std::string sql)
{
    // mysql_query()执行成功返回0,执行失败返回非0值。
    if (mysql_query(mysql, sql.c_str()))
    {
        std::cout << "Query Error: " << mysql_error(mysql);
        return false;
    }
    else // 查询成功
    {
        result = mysql_store_result(mysql); // 获取结果集
        if (result)                         // 返回了结果集
        {
            int num_fields = mysql_num_fields(result); // 获取结果集中总共的字段数，即列数
            int num_rows = mysql_num_rows(result);     // 获取结果集中总共的行数
            for (int i = 0; i < num_rows; i++)         // 输出每一行
            {
                // 获取下一行数据
                row = mysql_fetch_row(result);
                if (row == NULL)
                    break;

                for (int j = 0; j < num_fields; j++) // 输出每一字段
                {
                    std::cout << row[j] << "\t\t";
                }
                std::cout << std::endl;
            }
        }
        else // result==NULL
        {
            if (mysql_field_count(mysql) == 0) // 代表执行的是update,insert,delete类的非查询语句
            {
                // (it was not a SELECT)
                int num_rows = mysql_affected_rows(mysql); // 返回update,insert,delete影响的行数
            }
            else // error
            {
                std::cout << "Get result error: " << mysql_error(mysql);
                return false;
            }
        }
    }

    return true;
}
