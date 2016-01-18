#include <windows.h>
#include "stdio.h"
#include "stdlib.h"
#include "winsock.h"
#include "mysql.h"
#include <string>
#include <string.h>
#include "struct.h"
#include <iostream>
using namespace std;

class DB_Help {

	private:
		//连接数据库信息
		const char user[30]		= "root";
		const char password[30] = "zbm123";
		const char host[30]		= "localhost";
		const char dbname[30]	= "clg_db";
		unsigned int port		= 3306;
		
		//从数据库获得的信息
		MYSQL	    *mysql; //= mysql_init((MYSQL*) 0); 
		MYSQL_RES   *result;
		MYSQL_ROW   row;
		MYSQL_FIELD *fd;
	
		Computer computer, *com;
		Senstive senstive, *sen;
		Forbidweb forbidweb, *fob;
		History history, *his;
		Customer customer;

	public:
		//构造函数，连接数据库
		DB_Help() {
			mysql= mysql_init((MYSQL*)0);
			if (mysql_real_connect(mysql, host, user, password, dbname, port, NULL, 0)) {
				if (!mysql_select_db(mysql, dbname)) {
					cout << "succeeful!" << endl;
				}
				else {
					cout << "failure" << endl;
				}
			}
			else {
				cout << "failure" << endl;
			}
		}

		~DB_Help() {
			mysql_free_result(result);
			mysql_close(mysql);
		}
		

		//显示某表全部信息
		void* sql_all(int k) {
			if (k < 1 || k>5) {
				cout << "参数错误，参数范围1-5！" << endl;
				return NULL;
			}

			//char column[32][32];
			char *sql;

			switch (k)
			{
			case COMPUTER_TABLE:  sql = "select * from computer";  break;
			//case CUSTOMER_TABLE:  sql = "select * from customer";  break;
			case SENSTIVE_TABLE:  sql = "select * from senstive";  break;
			case FORBIDWEB_TABLE: sql = "select * from forbidweb"; break;
			case HISTORY_TABLE:   sql = "select * from history";   break;
			default:sql = "select * from computer";
				break;
			}
			//cout << sql <<":"<< endl;
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql,sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					
					int i, j,x=0;
					/*
					for (i = 0; fd = mysql_fetch_field(result); i++) {//获得列名
						strcpy_s(column[i], fd->name);
					}*/
					//j = mysql_num_fields(result);//列数
					j = mysql_num_rows(result);//行数
					
					switch (k)
					{
					case COMPUTER_TABLE:  com = new Computer[j];  break;
					case SENSTIVE_TABLE:  sen = new Senstive[j];  break;
					case FORBIDWEB_TABLE: fob = new Forbidweb[j]; break;
					case HISTORY_TABLE:   his = new History[j];   break;
					}
					
					while (row = mysql_fetch_row(result)) {//获取每行具体数据
						
						if (row != NULL) {

							switch (k)
							{
							case COMPUTER_TABLE:
								com[x].num = j;
								com[x].ip = row[0];
								com[x].online = row[1];
								break;
								//case CUSTOMER_TABLE:
								//	break;
							case SENSTIVE_TABLE:
								sen[x].num = j;
								sen[x].ip = row[2];
								sen[x].word = row[1];
								break;
							case FORBIDWEB_TABLE:
								fob[x].num = j;
								fob[x].ip = row[2];
								fob[x].web = row[1];
								break;
							case HISTORY_TABLE:
								his[x].num = j;
								his[x].ip = row[1];
								his[x].address = row[2];
								if (row[3] == NULL) { his[x].time = "unknow"; }
								else{ his[x].time = row[3]; }
								break;
							}
							x++;
						}
					}

					switch (k)
					{
					case COMPUTER_TABLE:  return com; break;
					case SENSTIVE_TABLE:  return sen; break;
					case FORBIDWEB_TABLE: return fob; break;
					case HISTORY_TABLE:	  return his; break;
					default:return NULL;
					}
				}
				else {
					return NULL;
				}
			}
			else {
				return NULL;
			}
		}

		//通过ip查询计算机信息
		struct Computer select_computer(char *ip) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql,100, "select online from computer where ip = '%s'", ip);
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					row = mysql_fetch_row(result);
					int i = mysql_num_rows(result);
					if (i == 0) {
						computer.ip = "0";
						computer.online = 0;
						return computer;
					}
					//cout << row[0] << "	" << row[1] << "	"<<row[2]<<endl;
					computer.ip = ip;
					computer.online = row[0];
					//cout << computer.up_speed << "	"<< computer.online <<endl;
					return computer;
				}
				else { 
					computer.ip = "0"; 
					computer.online = 0; 
					return computer; 
				}
			}
			else { 
				computer.ip = "0"; 
				computer.online = 0; 
				return computer; 
			}
		}

		//查询某电脑历史记录
		struct History* select_history(char *ip) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select address,time from history where ip = '%s'", ip);
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					int i = mysql_num_rows(result);
					his = new History[i];
					if (i == 0) {
						his[0].ip = "0";
						return his;
					}
					else {
						int j = 0;
						while (row = mysql_fetch_row(result)) {//获取每行具体数据
							his[j].ip = ip;
							his[j].address = row[0];
							if (row[1]== NULL) { his[j].time = "unknow"; }
							else { his[j].time = row[1]; }
							j++;
						}
						return his;
					}
				}
				else {
					his[0].ip = "0";
					return his;
				}
			}
			else {
				his[0].ip = "0";
				return his;
			}
		}

		//查询某台电脑禁止访问的网站
		struct Forbidweb * select_forbidweb(char* ip) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select ip,web from forbidweb where ip = '0.0.0.0' or ip = '%s'",ip);
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res,res1;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					int i = mysql_num_rows(result);
					fob = new Forbidweb[i];
					if (i == 0) {
						fob[0].ip = "0";
						return fob;
					}
					else {
						int j = 0;
						while (row = mysql_fetch_row(result)) {//获取每行具体数据
							fob[j].ip = row[0];
							fob[j].web = row[1];
							j++;
						}
						return fob;
					}
				}
				else {
					fob[0].ip = "0";
					return fob;
				}
			}
			else {
				fob[0].ip = "0";
				return fob;
			}
		}

		//查询登录用户
		struct Customer login(char* name,char* password) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select email from customer where name='%s' and password='%s'", name,password);
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					row = mysql_fetch_row(result);
					int i = mysql_num_rows(result);
					if (i == 0) {
						customer.name = "0";
						return customer;
					}
					//cout << row[0] << "	" << row[1] << "	"<<row[2]<<endl;
					customer.name = name;
					customer.password = password;
					customer.email = row[0];
					//cout << computer.up_speed << "	"<< computer.online <<endl;
					return customer;
				}
				else {
					customer.name = "0";
					return customer;
				}
			}
			else {
				customer.name = "0";
				return customer;
			}
		}

		//删除某一计算机
		bool delete_computer(char *ip) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "delete from computer where ip = '%s'", ip);
			//char *sql = "select up_speed,down_speed,online from computer where ip='192.168.70.70'";
			//cout << sql << endl;
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "failed" << endl;
				return false;
			}
			else {
				cout << "success!" << endl;
				return true;
			}
		} 

		//删除某个禁止访问的网址
		bool delete_forbidweb(char* ip, char* web) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "delete from forbidweb where ip = '%s' and web = '%s'", ip,web);
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "failed" << endl;
				return false;
			}
			else {
				int i = mysql_affected_rows(mysql);
				if (i == 0) { cout << "failed" << endl; return false; }
				else {
					cout << "success!" << endl;
					return true;
				}
			}
		}
		//删除某个铭感词
		bool delete_senstive(char* ip, char* word) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "delete from senstive where ip = '%s' and word = '%s'", ip,word);
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "failed" << endl;
				return false;
			}
			else {
				int i = mysql_affected_rows(mysql);
				if (i == 0) { cout << "failed" << endl; return false; }
				else {
					cout << "success!" << endl;
					return true;
				}
			}
		}
		//删除某计算机的历史
		bool delete_history(char* ip) {
			char *sql = (char*)malloc(100);
			if (ip == "0.0.0.0") {
				sql="delete from history";
			}
			else {
				sprintf_s(sql, 100, "delete from history where ip = '%s'", ip);
			}
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "failed" << endl;
				return false;
			}
			else {
				int i = mysql_affected_rows(mysql);
				if (i == 0) { cout << "failed" << endl; return false; }
				else {
					cout << "success!" << endl;
					return true;
				}
			}
		}

		//插入到forbidweb表
		bool insert_forbidweb(Forbidweb fb) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select * from forbidweb where ip='%s' and web='%s'", fb.ip.c_str(), fb.web.c_str());
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					//row = mysql_fetch_row(result);
					int i = mysql_num_rows(result);
					if (i != 0) {
						return false;
					}
				}
			}
			sprintf_s(sql, 100, "insert into forbidweb (ip,web) values('%s','%s')",fb.ip.c_str(),fb.web.c_str());
			//c_str()将string转为char*
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "faild" << endl;
				return false;
			}
			else {
				cout << "succeed" << endl;
				return true;
			}
		}

		//插入到senstive表
		bool insert_senstive(Senstive st) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select * from senstive where ip='%s' and word='%s'", st.ip.c_str(), st.word.c_str());
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					int i = mysql_num_rows(result);
					if (i != 0) {
						return false;
					}
				}
			}
			sprintf_s(sql, 100, "insert into senstive (ip,word) values('%s','%s')", st.ip.c_str(), st.word.c_str());
			//c_str()将string转为char*
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "faild" << endl;
				return false;
			}
			else {
				cout << "succeed" << endl;
				return true;
			}
		}

		//插入到computer表
		bool insert_computer(Computer cp) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select * from computer where ip='%s'", cp.ip.c_str());
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					int i = mysql_num_rows(result);
					if (i != 0) {
						return false;
					}
				}
			}
			sprintf_s(sql, 100, "insert into computer (ip,online) values('%s','%d')", cp.ip.c_str(), cp.online);
			//c_str()将string转为char*
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "faild" << endl;
				return false;
			}
			else {
				cout << "succeed" << endl;
				return true;
			}
		}

		//注册管理员
		bool insert_customer(Customer ct) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select * from customer where name='%s'",ct.name.c_str());
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					int i = mysql_num_rows(result);
					if (i != 0) {
						return false;
					}
				}
			}
			sprintf_s(sql, 100, "insert into customer (name,password,email) values('%s','%s','%s')",
				ct.name.c_str(), ct.password.c_str(),ct.email.c_str());
			//c_str()将string转为char*
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "faild" << endl;
				return false;
			}
			else {
				cout << "succeed" << endl;
				return true;
			}
		}

		//插入到history表
		bool insert_history(History ht) {
			char *sql = (char*)malloc(100);
			sprintf_s(sql, 100, "select * from history where ip='%s' and address='%s'", ht.ip.c_str(), ht.address.c_str());
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			int res;
			res = mysql_query(mysql, sql);
			if (!res) {
				result = mysql_store_result(mysql);
				if (result) {
					//row = mysql_fetch_row(result);
					int i = mysql_num_rows(result);
					if (i != 0) {
						return false;
					}
				}
			}
			sprintf_s(sql, 100, "insert into history (ip,address,time) values('%s','%s','%s')", ht.ip.c_str(), ht.address.c_str(),ht.time.c_str());
			//c_str()将string转为char*
			mysql_query(mysql, "SET NAMES GBK");//设置编码格式
			res = mysql_query(mysql, sql);
			if (res) {
				cout << "faild" << endl;
				return false;
			}
			else {
				cout << "succeed" << endl;
				return true;
			}
		}
};