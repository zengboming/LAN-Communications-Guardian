#pragma once
#include "windows.h"
#include "winsock.h"
#include "mysql.h"

class DateBase
{
private:
	//连接数据库信息
	const char user[30] = "root";
	const char password[30] = "zbm123";
	const char host[30] = "localhost";
	const char dbname[30] = "bank_db";
	unsigned int port = 3306;

	//从数据库获得的信息
	MYSQL	    *mysql; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES   *result;
	MYSQL_ROW   row;
	MYSQL_FIELD *fd;
public:
	DateBase();
	~DateBase();
	int login(int id,char* password);    //登录     L
	int deposit(int id,int money);		 //存钱     D
	int withdrawal(int id,int money);	 //取钱     W
	int check(int id);                   //查询余额 C
};