// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include <winsock2.h>
#include <Windows.h>
using namespace std;

DWORD WINAPI startListen(LPVOID ipParam)
{
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

