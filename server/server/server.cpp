#include <stdio.h>
#include <fstream>
#include <string>
#include <Winsock2.h>
#include "struct.h"
#include <iostream>
#pragma comment( lib, "ws2_32.lib" )// ����Winsock2.h�ľ�̬���ļ� 
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
	memcpy(t, &cp, sizeof(cp));//�������1024������Ϊջ����������������ͨ����������->c/c++->��������->��������ʱ��� ����ΪĬ��ֵ���
	com[0] = 'a';
	memcpy(com + 1, t, sizeof(t));
	for (int i = 0; i < sizeof(com); i++) {
		cout << com[i];
	}
	//�����ַ�������һλ����������ǽṹ��
	send(sockClient, com, sizeof(com)+1, NULL);
	//ֱ�ӷ��ͽṹ��
	//send(sockClient, (char*)(&cp), sizeof(Test),NULL);
	//send(sockClient, "hello", strlen("hello") + 1, 0);
	char recvBuf[50];
	//recv(sockClient, recvBuf, 50, 0);
	//printf("%s\n", recvBuf);
	*/

	closesocket(sockClient);
	WSACleanup();
}