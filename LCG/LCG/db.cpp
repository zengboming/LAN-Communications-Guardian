#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "db_help.cpp"
#include "struct.h"
using namespace std;
 

/*int main() {

	DB_Help *db_help=new DB_Help(); 
	Computer co, *com1;
	Senstive se, *sen1;
	Forbidweb fo, *fob1;
	History hi, *his1; 
	Customer cu;    

	/*com1=(struct Computer *)db_help->sql_all(COMPUTER_TABLE);  
	cout << "com" << com1[0].ip << "	" << com1[0].online << endl;
	//db_help->sql_all(CUSTOMER_TABLE);
	sen1 = (struct Senstive *)db_help->sql_all(SENSTIVE_TABLE);
	cout << "sen" << sen1[0].ip << "	" << sen1[0].word << endl;

	fob1 = (struct Forbidweb*)db_help->sql_all(FORBIDWEB_TABLE);
	cout << "fob" << fob1[0].ip << "	" << fob1[0].web << endl;
	cout << "fob" << fob1[1].ip << "	" << fob1[1].web << endl;
	cout << "fob" << fob1[2].ip << "	" << fob1[2].web << endl;
	cout << "fob" << fob1[3].ip << "	" << fob1[3].web << endl;
	cout << "fob" << fob1[4].ip << "	" << fob1[4].web << endl;*/

	//his1 = (struct History  *)db_help->sql_all(HISTORY_TABLE);
	//cout << "his" <<his1[0].ip << "	" << his1[0].address << "	"<<his1[0].time<<endl;   
	
	/*co=db_help->select_computer("192.168.60.60");   
	if (co.ip=="0") {    
		cout << "no"<< endl;   
	}
	else {
		cout << "succeed!" << endl;
	}*/
	
	//bool b=db_help->delect_computer("192.168.60.60");
	//cout << b<< endl; 

	/*his1=db_help->select_history("192.168.80.80"); 
	if (his1[0].ip == "0") {
		cout << "no" << endl; 
	}
	else {
		cout << "his:" << his1[0].ip << "	" << his1[0].address <<"	"<<his1[0].time<< endl; 
	}
	*/
	/*
	fob1 = db_help->select_forbidweb("192.168.90.90");  
	if (fob1[0].ip == "0") {
		cout << "no" << endl;  
	}
	else {
		cout << "fob:" << fob1[0].ip << "	" << fob1[0].web << endl;
		cout << "fob:" << fob1[1].ip << "	" << fob1[1].web << endl;
		cout << "fob:" << fob1[2].ip << "	" << fob1[2].web << endl;
	}
	*/
	
	/*bool b = db_help->delete_forbidweb("0.0.0.0","www.csdn.com");   
	cout << b << endl; 
	
	fob1 = (struct Forbidweb*)db_help->sql_all(FORBIDWEB_TABLE);
	cout << "fob" << fob1[0].ip << "	" << fob1[0].web << endl;
	cout << "fob" << fob1[1].ip << "	" << fob1[1].web << endl;
	cout << "fob" << fob1[2].ip << "	" << fob1[2].web << endl;
	cout << "fob" << fob1[3].ip << "	" << fob1[3].web << endl;*/
	
	/*bool b = db_help->delete_history("0.0.0.0");
	cout << b << endl;*/ 
	
	/*cu = db_help->login("zbm","zbm123");
	cout << "cus:" << cu.name << "	" << cu.password << "	"<<cu.email<< endl;*/

	/*Forbidweb fb;
	fb.ip = "192.168.60.60";
	fb.web = "www.taobao.com";
	bool b = db_help->insert_forbidweb(fb);   
	cout << b;*/

	/*Senstive st;
	st.ip = "192.168.90.90";
	st.word = "nima";
	bool b = db_help->insert_senstive(st);
	cout << b;*/

	/*Computer cp;
	cp.ip = "192.168.60.60";
	cp.online = 1;
	bool b = db_help->insert_computer(cp);
	cout << b;*/

	/*Customer ct ;
	ct.name = "hust";
	ct.password = "hust2015";
	bool b = db_help->insert_customer(ct);
	cout << b;*/

	/*History h;
	h.ip = "192.168.0.1";
	h.address = "www.tianmao.com";
	h.time = "2016.1.1,12:34";
	bool b = db_help->insert_history(h);
	cout << b;*/

	/*
	//��ʾ���ű���ĳ��ȫ����Ϣ                             Command:
	void* sql_all(int k)									  a
	//��ѯĳ������Ϣ
	struct Computer select_computer(char *ip)                 b
	//��ѯĳ������ʷ��¼
	struct History* select_history(char *ip)                  c
	//��ѯĳ���Խ�ֹ���ʵ���վ
	struct Forbidweb * select_forbidweb(char* ip)             d
	//��ѯ��¼�û�
	struct Customer login(char* name, char* password)         e
	//ɾ��ĳһ�����
	bool delete_computer(char *ip)                            f
	//ɾ��ĳ����ֹ���ʵ���ַ
	bool delete_forbidweb(char* ip, char* web)                g
	//ɾ��ĳ�����д�
	bool delete_senstive(char* ip, char* word)                h
	//ɾ��ĳ���������ʷ
	bool delete_history(char* ip)                             i
	//���뵽forbidweb��
	bool insert_forbidweb(Forbidweb fb)                       j
	//���뵽senstive��
	bool insert_senstive(Senstive st)                         k
	//���뵽computer��
	bool insert_computer(Computer cp)                         l
	//���뵽history��
	bool insert_history(History ht)                           m
	//ע�����Ա
	bool insert_customer(Customer ct)                         n
	*/

	/*
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
	*/
	//if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306/*TCP IP�˿�*/, NULL/*Unix Socket ��������*/, 0/*���г�ODBC���ݿ��־*/))
	/*{
		if (!mysql_select_db(con, dbname))
		{
			printf("Select successfully the database!\n");
			mysql_query(con, "SET NAMES GBK");//���ñ����ʽ��������cmd���޷���ʾ����
			res = mysql_query(con, sql);
			if (!res) {
				result = mysql_store_result(con);
				if (result) {
					cout << "number of result:" << (unsigned long)mysql_num_rows(result)<<endl;
					int i, j;
					for (i = 0;fd=mysql_fetch_field(result) ; i++) {//�������
						strcpy_s(column[i] ,fd->name);
					}
					j = mysql_num_fields(result);
					for (i = 0; i < j; i++) {
						cout << "	" << column[i];
					}
					cout << endl;
					while (row = mysql_fetch_row(result)) {//��ȡ��������
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
	else{
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}
	if (result != NULL) mysql_free_result(result);
	mysql_close(con);
	*/
	/*return 0;
}*/