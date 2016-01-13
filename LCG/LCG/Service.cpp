// Service.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment( lib, "ws2_32.lib" )// 链接Winsock2.h的静态库文件 

using namespace std;
static const int DATASIZE = 255;


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
	char cData[DATASIZE];
	long lFileSize = 0;
	long cCur = 0;

	ifstream ReadStream;//打开文件
	ReadStream.open(cPath, ios::binary);

	ReadStream.seekg(0, ios::end);//获取文件大小
	lFileSize = ReadStream.tellg();

	sprintf(cData, "%d", lFileSize);//获传输文件大小
	send(sSendSocket, cData, DATASIZE, 0);
	while (cCur<lFileSize)
	{
		ReadStream.seekg(cCur);
		ReadStream.read(cData, DATASIZE);
		int i = send(sSendSocket, cData, DATASIZE, 0);

		cCur += DATASIZE;
	}

	ReadStream.close();
	return true;
}




int main()
{//创建套接字
    WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (!err) {
		printf("已打开套接字\n");
	}
	else {
		printf("ERROR:嵌套字未打开!");
		return 1;
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

		SendFile(serConn, "hello.txt");

		closesocket(serConn);//关闭
		closesocket(serSocket);//关闭
		
		WSACleanup();//释放资源的操作
		return 0;
	}
	return 1;
}

