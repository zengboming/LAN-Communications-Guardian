#pragma once
#include "stdafx.h"
#include "string.h"
#include "db.h"
#include "winsock.h"
#include <Windows.h>
#pragma comment( lib, "ws2_32.lib" )
#include "iostream"
using namespace std;

DWORD WINAPI startListen(LPVOID ipParam)
{
	SOCKET socket = *((SOCKET*)ipParam);
	SOCKADDR_IN client;
	int len = sizeof(SOCKADDR_IN);

	DateBase *db = new DateBase();
	char recvBuff[100];	//接受的字符串
	char sendBuff[10];	//发送的字符串
	char command;		//命令
	int id;				//账号ID
	int amount;		    //余额
	int money;			//存或取的钱
	string time;		//时间
	char password[6];	//密码
	string infor;		//存放密码或者钱
	memset(recvBuff, 0x00, 100);
	memset(sendBuff, 0x00, 10);
	memset(password, 0x00, 6);

	while (1)
	{
		SOCKET serConn = accept(socket,(SOCKADDR*)&client,&len);
		recv(serConn, recvBuff, sizeof(recvBuff) + 1, NULL);
		for (int i = 0; i < sizeof(recvBuff); i++) {
			cout << recvBuff[i];
		}
		cout << endl;

		//分割socket, "id,command,time,money";
		const char * split = ",";
		char *p;
		p = strtok(recvBuff, split);
		id = atoi(p);
		cout << "id=" << id<<"	";

		p = strtok(NULL, split);
		command = p[0];
		cout << "command=" << command <<"	";

		p = strtok(NULL, split);
		time = p;
		cout << "time=" << time.c_str() << "	";

		p = strtok(NULL, split);
		infor = p;
		cout << "infor=" << infor.c_str() << endl;


		int msg=-1;
		int i = 0;
		switch (command)
		{
		case 'l'://登录
			memcpy(password, infor.c_str(),sizeof(infor.c_str()));
			msg=db->login(id,password);
			cout << "msg:" << msg << endl;
			if(msg < 0){ send(serConn, "-1\n", sizeof("-1\n"), NULL); }
			else	   { send(serConn, "1\n", sizeof("1\n"), NULL); }
			break;
		case 'd'://存钱
			money = atoi(infor.c_str());
			//cout << "money" << money << endl;
			msg = db->deposit(id, money);
			cout << msg << endl;
			if (msg < 0)  { send(serConn, "-1\n", sizeof("-1\n"), NULL); }
			else		  { send(serConn, "1\n", sizeof("1\n"), NULL); }
			break;
		case 'w'://取钱
			amount = db->check(id);
			money = atoi(infor.c_str());
			if (amount >= money)
			{
				msg = db->withdrawal(id, money);
				cout << "msg:" << msg << endl;
				if (msg < 0) { send(serConn, "-1\n", sizeof("-1\n"), NULL); }
				else         { send(serConn, "1\n", sizeof("1\n"), NULL); }
			}
			else
			{
				send(serConn, "-1\n", sizeof("-1\n") , NULL);
			}
			break;
		case 'c'://查询余额 
			amount = db->check(id);
			cout <<"amount"<< amount << endl;
			sprintf(sendBuff, "%d\n", amount);
			if (amount < 0) { send(serConn, "-1\n", sizeof("-1\n") , NULL); }
			else			{ send(serConn, sendBuff, sizeof(sendBuff)+1, NULL);}
			break;
		default:
			cout << "wrong command";
			break;
		}

		cout << "-----------------------------------------------" << endl;
		memset(recvBuff, 0, 200);
		//closesocket(serConn);
	}

	return 0;
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

	//HANDLE hThrd;
	HANDLE listener = CreateThread(NULL, 0, startListen, &serSocket, 0, NULL);
	while (1) {}

    return 0;
}

