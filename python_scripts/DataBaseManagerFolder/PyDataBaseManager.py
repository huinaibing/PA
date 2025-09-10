import mysql.connector


class DataBaseManager:
    def __init__(self, database):
        self.connection = mysql.connector.connect(
            host="localhost",        # 主机地址
            user="root",         # 用户名
            password="7355608", # 密码
            database=database,       # 数据库名（可选，也可后续指定）
            port=3306,               # 默认端口
            charset="utf8mb4",       # 字符集（支持 emoji）
            autocommit=True          # 自动提交事务
        )
        self.cursor = self.connection.cursor()

    def close(self):
        self.connection.close()

    def excute(self, sql):
        self.cursor.execute(sql)
        return self.cursor.fetchall()
