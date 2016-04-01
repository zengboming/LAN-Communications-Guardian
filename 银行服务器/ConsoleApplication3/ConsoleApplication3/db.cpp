#pragma once
#include "db.h"
#include "windows.h"
#include "winsock.h"
#include "mysql.h"
#include <iostream>
using namespace std;

DateBase::DateBase()
{
	mysql = mysql_init((MYSQL*)0);
	if (mysql_real_connect(mysql, host, user, password, dbname, port, NULL, 0)) {
		if (!mysql_select_db(mysql, dbname)) {
			cout << "server:succeeful!" << endl;

		}
		else {
			cout << "failure" << endl;

		}
	}
	else {
		cout << "failure" << endl;

	}
}

DateBase::~DateBase()
{
	mysql_free_result(result);
	mysql_close(mysql);
}

//登录
int DateBase::login(int id,char* password)
{
	char *sql = (char*)malloc(150);
	sprintf_s(sql, 150, "select amount from bankaccount where number=%d and password='%s'", id, password);
	cout << sql << endl;
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式
	int res;
	res = mysql_query(mysql, sql);
	if (!res) {
		result = mysql_store_result(mysql);
		if (result) {
			row = mysql_fetch_row(result);
			int i = mysql_num_rows(result);
			if (i == 0) {
				return -1;
			}
			return 1;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

//存钱
int DateBase::deposit(int id,int money)
{
	char *sql = (char*)malloc(150);
	sprintf_s(sql, 150, "update bankaccount set amount=amount+%d where number=%d",money ,id );
	cout << sql << endl;
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式
	int res;
	res = mysql_query(mysql, sql);
	if (res) {
		cout << "failed" << endl;
		return -1;
	}
	else {
		cout << "success!" << endl;
		return 1;
	}
}

//取钱
int DateBase::withdrawal(int id,int money)
{
	char *sql = (char*)malloc(150);
	sprintf_s(sql, 150, "update bankaccount set amount=amount-%d where number=%d", money, id);
	cout << sql << endl;
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式
	int res;
	res = mysql_query(mysql, sql);
	if (res) {
		cout << "failed" << endl;
		return -1;
	}
	else {
		cout << "success!" << endl;
		return 1;
	}
}

//查询余额
int DateBase::check(int id)
{
	int amount=0;
	char *sql = (char*)malloc(100);
	sprintf_s(sql, 100, "select amount from bankaccount where number=%d", id);
	cout << sql << endl;
	mysql_query(mysql, "SET NAMES GBK");//设置编码格式
	int res;
	res = mysql_query(mysql, sql);
	if (!res) {
		result = mysql_store_result(mysql);
		if (result) {
			row = mysql_fetch_row(result);
			int i = mysql_num_rows(result);
			if (i == 0) {
				return -1;
			}
			//cout<<row[0]<<"	"<<row[1]<<" "<<row[2]<<" "<<row[3]<<" "<<row[]
			amount = atoi(row[0]);
			return amount;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}
