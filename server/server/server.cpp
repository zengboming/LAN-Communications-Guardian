#include <stdio.h>
#include <fstream>
#include <string>
#include <Winsock2.h>
#include "struct.h"
#include <iostream>
#pragma comment( lib, "ws2_32.lib" )// 链接Winsock2.h的静态库文件 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

/*struct Test {
	char ip[30];
	char name[30];
};
struct Test1 {
	string ip;
	string name;
};*/


void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	
	/*Test cp;
	memset(&cp, 0x00, sizeof(Test));
	memcpy(cp.ip,"192.168.0.1",sizeof("192.168.0.1"));
	memcpy(cp.name, "hello", sizeof("hello"));
	char com[100] = { 0 };
	char t[99] ;
	memset(t, 0, 99);
	memcpy(t, &cp, sizeof(cp));//如果设置1024，会因为栈过大而程序崩溃，可通过配置属性->c/c++->代码生成->基本运行时检查 设置为默认值解决
	com[0] = 'a';
	memcpy(com + 1, t, sizeof(t));
	for (int i = 0; i < sizeof(com); i++) {
		cout << com[i];
	}
	//发送字符串，第一位是命令，后面是结构体
	send(sockClient, com, sizeof(com)+1, NULL);
	//直接发送结构体
	//send(sockClient, (char*)(&cp), sizeof(Test),NULL);
	//send(sockClient, "hello", strlen("hello") + 1, 0);
	char recvBuf[50];
	//recv(sockClient, recvBuf, 50, 0);
	//printf("%s\n", recvBuf);
	*/

	closesocket(sockClient);
	WSACleanup();
}