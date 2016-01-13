// Service.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment( lib, "ws2_32.lib" )// ����Winsock2.h�ľ�̬���ļ� 

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

	ofstream WriteStream;//���ļ�
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

	ifstream ReadStream;//���ļ�
	ReadStream.open(cPath, ios::binary);

	ReadStream.seekg(0, ios::end);//��ȡ�ļ���С
	lFileSize = ReadStream.tellg();

	sprintf(cData, "%d", lFileSize);//�����ļ���С
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
{//�����׽���
    WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (!err) {
		printf("�Ѵ��׽���\n");
	}
	else {
		printf("ERROR:Ƕ����δ��!");
		return 1;
	}
	//��һ�����׽���
	SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);//�����˿�ʶ���׽���

													   //��Ҫ�󶨵Ĳ���
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip��ַ
	addr.sin_port = htons(6000);//�󶨶˿�

	bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//�����
	listen(serSocket, 5);//���еڶ������������ܹ����յ�����������

						 //////////////////////////////////////////////////////////////////////////
						 //��ʼ���м���
						 //////////////////////////////////////////////////////////////////////////
	SOCKADDR_IN clientsocket;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���

		SendFile(serConn, "hello.txt");

		closesocket(serConn);//�ر�
		closesocket(serSocket);//�ر�
		
		WSACleanup();//�ͷ���Դ�Ĳ���
		return 0;
	}
	return 1;
}

