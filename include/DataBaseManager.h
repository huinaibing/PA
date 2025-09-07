#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <iostream>
#include "BaseManager.h"
class DataBaseManager
{
protected:
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;

public:
    DataBaseManager()
    {
        mysql = mysql_init(NULL);
        if (mysql == NULL)
        {
            std::cout << "Error when connecting to mysql:" << mysql_error(mysql) << " at function DataBaseManager()" << std::endl;
            exit(1);
        }
    }

    ~DataBaseManager()
    {
        if (mysql != NULL) // 关闭数据连接
        {
            mysql_close(mysql);
        }
    }

    /**
     * @brief 连接数据库，密码直接告诉你了，但是我的sql只接受本地连接哈哈
     *
     * @param db_name database名字
     * @param host
     * @param user
     * @param passwd
     * @return true
     * @return false
     */
    bool init(std::string db_name, std::string host = "localhost", std::string user = "root", std::string passwd = "7355608");

    /**
     * @brief 执行sql语句，十分简单的一个函数，updateselectdelete都能干
     *
     * @param sql
     * @return true
     * @return false
     */
    virtual bool simpleGetResultFromSQL(std::string sql);

    MYSQL_RES* getResult(std::string sql);
};

#endif
