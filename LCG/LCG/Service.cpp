#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <string>
#include "db_help.cpp"
#include "struct.h"
#pragma comment( lib, "ws2_32.lib" )// 链接Winsock2.h的静态库文件 
using namespace std;

static const int DATASIZE = 255;
/*struct Test {
	char ip[30];
	char name[30];
};*/


const bool CharToLong(const char cSize[], int cMaxSize, long& lSize)
{
	long lNewSize = 0;
	for (int i = 0; i < cMaxSize; i++)
	{
		if ('\0' == cSize[i])
		{
			lSize = lNewSize;
			return 1;
		}
		lNewSize = lNewSize * 10 + (cSize[i] - '0');
	}
	return 0;
}


void RecvFile(const SOCKET& sRecvSocket, char* cPath)
{
	char cData[DATASIZE];
	long lFileSize = 0;
	long cCur = 0;

	ofstream WriteStream;//打开文件
	WriteStream.open(cPath, ios::binary);

	recv(sRecvSocket, cData, DATASIZE, 0);
	CharToLong(cData, DATASIZE, lFileSize);

	while (cCur<lFileSize)
	{
		recv(sRecvSocket, cData, DATASIZE, 0);
		WriteStream.write(cData, DATASIZE);

		cCur = WriteStream.tellp();
	}
	WriteStream.close();
}

bool SendFile(const SOCKET &sSendSocket, const char* const cPath)
{
	char cData[DATASIZE] = { 0 };
	long lFileSize = 0;
	long cCur = 0;

	ifstream ReadStream;//打开文件
	ReadStream.open(cPath, ios::binary);

	ReadStream.seekg(0, ios::end);//获取文件大小
	lFileSize = ReadStream.tellg();

	sprintf(cData, "%d", lFileSize);//获传输文件大小
	send(sSendSocket, cData, 100, 0);
	while (cCur<lFileSize)
	{
		ReadStream.seekg(cCur);
		if (ReadStream.read(cData, DATASIZE))//未读完
		{
			send(sSendSocket, cData, DATASIZE, 0);
		}
		else
		{
			send(sSendSocket, cData, lFileSize - cCur, 0);
		}
		cCur += DATASIZE;
	}
	ReadStream.close();
	return true;
}



int main()
{
	WSADATA wsa;
	//初始化socket资源
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
	{
		return 0;   //代表失败
	}
	//进一步绑定套接字
	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);//创建了可识别套接字

	//需要绑定的参数
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
	addr.sin_port = htons(6000);//绑定端口

	bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
	listen(serSocket, 5);//其中第二个参数代表能够接收的最多的连接数

//////////////////////////////////////////////////////////////////////////
//开始进行监听
//////////////////////////////////////////////////////////////////////////
	SOCKADDR_IN clientsocket;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);//如果这里不是accept而是conection的话。。就会不断的监听

		//SendFile(serConn, "hello.JPG");
		char sendBuf[50];
		sprintf(sendBuf, "Welcome %s to here!", inet_ntoa(clientsocket.sin_addr));
		send(serConn, sendBuf, strlen(sendBuf) + 1, 0);

		//接收的信息
		char recvBuff[100];	//接受的字符串
		char buff[99];		//由结构体强转的字符串
		void* table;		//
		int k;				//sql_all参数
		bool b;				//返回成功与否
		char command;		//命令
		//数据库中使用的结构体
		Customer  cus,*cu;
		Computer  com,*co;
		History   his,*hi;
		Senstive  sen,*se;
		Forbidweb fob,*fo;
		//socket中使用的结构体
		Customer1  cus1,*cu1;
		Computer1  com1,*co1;
		History1   his1,*hi1;
		Senstive1  sen1,*se1;
		Forbidweb1 fob1,*fo1;
		//操作数据库的对象
		DB_Help *db_help = new DB_Help();
		//初始化清空
		memset(recvBuff, 0, 100);
		memset(buff, 0, 99);

		memset(&cus, 0x00, sizeof(Customer));
		memset(&com, 0x00, sizeof(Computer));
		memset(&his, 0x00, sizeof(History));
		memset(&sen, 0x00, sizeof(Senstive));
		memset(&fob, 0x00, sizeof(Forbidweb));

		memset(&cus1, 0x00, sizeof(Customer1));
		memset(&com1, 0x00, sizeof(Computer1));
		memset(&his1, 0x00, sizeof(History1));
		memset(&sen1, 0x00, sizeof(Senstive1));
		memset(&fob1, 0x00, sizeof(Forbidweb1));


		//接收并处理
		recv(serConn, recvBuff, sizeof(recvBuff), NULL);
		command = recvBuff[0];
		memcpy(buff,recvBuff+1,sizeof(recvBuff)-1);
		//需要将struct中的char[]转成string
		switch (command)
		{
		case 'a':
			//查询某表全部信息
			k = (int)(recvBuff[1]-'0');
			cout << "k=" << k;
			co=(Computer*)db_help->sql_all(k);
			cout << "co:" << co[0].ip << "	" << co[0].online << endl;
			cout << "co:" << co[1].ip << "	" << co[1].online << endl;
			break;
		case 'b':
			//通过ip查询某电脑
			com = db_help->select_computer(buff);
			cout << "com:" << com.ip << "	" << com.online << endl;
			break;
		case 'c':
			//通过ip查询某电脑历史记录
			hi = db_help->select_history(buff);
			cout << "hi:" << hi[0].ip << "	" << hi[0].address << "	" << hi[0].time << endl;
			cout << "hi:" << hi[1].ip << "	" << hi[1].address << "	" << hi[1].time << endl;
			break;
		case 'd':
			//通过ip查询某电脑禁止访问网址
			fo = db_help->select_forbidweb(buff);
			cout << "fo" << fo[0].ip << "	" << fo[0].web << endl;
			cout << "fo" << fo[1].ip << "	" << fo[1].web << endl;
			break;
		case 'e':
			//查询登录用户
			cus1 = *(Customer1*)buff;                        //接受的Customer1
			cus = db_help->login(cus1.name, cus1.password);	 //返回的Customer
			cout << "cus:" << cus.name << "	" << cus.password << "	" << cus.email << endl;
			break;
		case 'f':
			//删除某一计算机
			b = db_help->delete_computer(buff);
			cout << "b:" << b << endl;
			break;
		case 'g':
			//删除某个禁止访问的网址
			fob1 = *(Forbidweb1*)buff;
			b = db_help->delete_forbidweb(fob1.ip, fob1.web);
			cout << "b:" << b << endl;
			break;
		case 'h':
			//删除某个敏感词
			sen1 = *(Senstive1*)buff;
			b = db_help->delete_senstive(sen1.ip, sen1.word);
			cout << "b:" << b << endl;
			break;
		case 'i':
			//删除某计算机历史记录
			b = db_help->delete_history(buff);
			cout << "b:" << b << endl;
			break;
		case 'j':
			//插入到禁止访问网址表
			fob1 = *(Forbidweb1*)buff;
			fob.ip = fob1.ip;
			fob.web = fob1.web;
			b = db_help->insert_forbidweb(fob);
			cout << "b:" << b << endl;
			break;
		case 'k':
			//插入到敏感词表
			sen1 = *(Senstive1*)buff;
			sen.ip = sen1.ip;
			sen.word = sen1.word;
			b = db_help->insert_senstive(sen);
			cout << "b:" << b << endl;
			break;
		case 'l':
			//插入到计算机表
			com1 = *(Computer1*)buff;
			com.ip = com1.ip;
			com.online = com1.online;
			b = db_help->insert_computer(com);
			cout << "b:" << b << endl;
			break;
		case 'm':
			//注册管理员
			cus1 = *(Customer1*)buff;
			cus.name = cus1.name;
			cus.password = cus1.password;
			cus.email = cus1.email;
			b = db_help->insert_customer(cus);
			cout << "b:" << b << endl;
			break;
		case 'n':
			//插入到历史记录表
			his1 = *(History1*)buff;
			his.ip = his1.ip;
			his.address = his1.address;
			his.time = his1.time;
			b = db_help->insert_history(his);
			cout << "b:" << b << endl;
			break;
		default:
			cout << "wrong command" << endl;
			break;
		}











		//char recvBuf[100];
		//recv(serConn, recvBuf, 50, 0);
		//printf("%s\n", recvBuf);

		/*Test te;
		char buff[100];
		memset(buff, 0, 100);
		memset(&te, 0x00, sizeof(Test));*/

		//直接接收结构体
		//recv(serConn, (char*)(&te), sizeof(Test), NULL);
		
		//内存拷贝，程序崩溃(因为栈过大而程序崩溃,数组改100可行)
		//memcpy(&te, buff, sizeof(buff));
		
		//接收char*，然后转成结构体
		//recv(serConn,buff, sizeof(buff), NULL);
		//te = *(Test*)buff;
		//printf("ip=%s,name=%s\n", te.ip,te.name);

		//接收字符串：第一位是命令，后面是结构体
		/*recv(serConn, buff, sizeof(buff), NULL);
		char command ;
		command=buff[0];
		char newbuff[99];
		memcpy(newbuff, buff + 1, sizeof(buff)-1);
		te = *(Test*)newbuff;
		printf("ip=%s,name=%s\n", te.ip, te.name);*/

		closesocket(serConn);//关闭
		closesocket(serSocket);//关闭
		
		//WSACleanup();//释放资源的操作
		return 0;
	}
	return 1;
}

