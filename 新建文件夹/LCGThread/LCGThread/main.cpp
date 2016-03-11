#pragma once
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <fstream>
#include "stdlib.h"
#pragma comment( lib, "ws2_32.lib" )

#include "MyThreadPool.h"
#include "MyThread.h"
#include "TestTask.h"
#include "db_help.cpp"
#include "struct.h"
using namespace std;

CTestTask*p = NULL;
CMyThreadPool threadpool(10);


DWORD WINAPI startListen(LPVOID ipParam)
{
	SOCKET socket = *((SOCKET*)ipParam);

	SOCKADDR_IN clientsocket;
	int len = sizeof(SOCKADDR_IN);
	char recvBuff[200];	//接受的字符串
	memset(recvBuff, 0, 200);  
	while (1)  
	{ 
		SOCKET serConn = accept(socket, (SOCKADDR*)&clientsocket, &len);

		recv(serConn, recvBuff, sizeof(recvBuff), NULL);
		for (int i = 0; i < sizeof(recvBuff); i++) { 
			cout << recvBuff[i];
		} 
		cout << endl;  

		int thread_id = 0;
		p = new CTestTask(thread_id, recvBuff, serConn);
		threadpool.addTask(p, PRIORITY::NORMAL);
		Sleep(500);
		cout << "get sendBuff:"<<p->sendBuff << endl;

	
		if(recvBuff[0]=='a'|| recvBuff[0] == 'c'|| recvBuff[0] == 'd')
		{
			char cnum[2];
			cnum[0] = p->sendBuff[0];
			cnum[1] = p->sendBuff[1];
			int num = atoi(cnum);
			cout << "数量:" << num << endl;

			char send2[200];
			memset(send2, 0, 200);
			Senstive1 sent1;
			memset(&sent1, 0x00, sizeof(Senstive1));

			send(serConn, cnum, sizeof(cnum) + 1, NULL);//发送数量
			cout << "发送数量:" << cnum << endl;
			for (int i = 0; i < num; i++)
			{
				memcpy(send2, p->sendBuff + 2 + i * 200, 200);
				send(serConn, send2, sizeof(send2) + 1, NULL);//发送数量
				//cout << "发送内容:" ;
				//sent1 = *(Senstive1*)send2;
				//cout << "ip:" << sent1.ip << "word:" << sent1.word << endl;
				//Sleep(100);
			}
		}
		else 
		{
			send(serConn, p->sendBuff, 200, NULL);
		}

		cout << "-----------------------------------------------" << endl;
		memset(recvBuff, 0, 200);
		closesocket(serConn);
	}
	return 0;
}


int main(int argc,char**argv)
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
	HANDLE listener = CreateThread(NULL,0,startListen,&serSocket,0,NULL);
	while (1) {}

	return 1;
}