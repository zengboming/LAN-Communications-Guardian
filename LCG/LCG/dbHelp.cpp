#include <windows.h>
#include "stdio.h"
#include "winsock.h"
#include "mysql.h"
#include <string.h>
#include <iostream>
using namespace std;
//#pragma comment(lib,"wsock32.lib")
//#pragma comment(lib,"libmysql.lib")

int main() {

	MYSQL * con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *fd;

	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "zbm123";
	char dbip[30] = "localhost";
	char dbname[50] = "clg_db";
	char tablename[50] = "compter";
	char *query = NULL;
	//char *sql = "select * from history";
	//char *sql = "select * from customer";
	char *sql = "select * from computer";
	//char *sql = "select * from senstive";
	//char *sql = "select * from forbidweb";

	int res;//return value
	char column[32][32];
	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
	{
		if (!mysql_select_db(con, dbname))
		{
			printf("Select successfully the database!\n");
			mysql_query(con, "SET NAMES GBK");//设置编码格式，否则在cmd下无法显示中文
			res = mysql_query(con, sql);
			if (!res) {
				result = mysql_store_result(con);
				if (result) {
					cout << "number of result:" << (unsigned long)mysql_num_rows(result) << endl;
					int i, j;
					for (i = 0; fd = mysql_fetch_field(result); i++) {//获得列名
						strcpy_s(column[i], fd->name);
					}
					j = mysql_num_fields(result);
					for (i = 0; i < j; i++) {
						cout << "	" << column[i];
					}
					cout << endl;
					while (row = mysql_fetch_row(result)) {//获取具体数据
						for (i = 0; i < j; i++) {
							if (row[i] == NULL) cout << "	" << "NULL";
							else cout << "	" << row[i];
						}
						cout << endl;
					}
				}
			}
			else {
				cout << "query sql failed!" << endl;
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}
	if (result != NULL) mysql_free_result(result);
	mysql_close(con);

	return 0;
}