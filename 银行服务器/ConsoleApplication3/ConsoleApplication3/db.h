#pragma once
#include "windows.h"
#include "winsock.h"
#include "mysql.h"

class DateBase
{
private:
	//�������ݿ���Ϣ
	const char user[30] = "root";
	const char password[30] = "zbm123";
	const char host[30] = "localhost";
	const char dbname[30] = "bank_db";
	unsigned int port = 3306;

	//�����ݿ��õ���Ϣ
	MYSQL	    *mysql; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES   *result;
	MYSQL_ROW   row;
	MYSQL_FIELD *fd;
public:
	DateBase();
	~DateBase();
	int login(int id,char* password);    //��¼     L
	int deposit(int id,int money);		 //��Ǯ     D
	int withdrawal(int id,int money);	 //ȡǮ     W
	int check(int id);                   //��ѯ��� C
};