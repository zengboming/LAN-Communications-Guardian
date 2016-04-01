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
	char recvBuff[100];	//���ܵ��ַ���
	char sendBuff[10];	//���͵��ַ���
	char command;		//����
	int id;				//�˺�ID
	int amount;		    //���
	int money;			//���ȡ��Ǯ
	string time;		//ʱ��
	char password[6];	//����
	string infor;		//����������Ǯ
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

		//�ָ�socket, "id,command,time,money";
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
		case 'l'://��¼
			memcpy(password, infor.c_str(),sizeof(infor.c_str()));
			msg=db->login(id,password);
			cout << "msg:" << msg << endl;
			if(msg < 0){ send(serConn, "-1\n", sizeof("-1\n"), NULL); }
			else	   { send(serConn, "1\n", sizeof("1\n"), NULL); }
			break;
		case 'd'://��Ǯ
			money = atoi(infor.c_str());
			//cout << "money" << money << endl;
			msg = db->deposit(id, money);
			cout << msg << endl;
			if (msg < 0)  { send(serConn, "-1\n", sizeof("-1\n"), NULL); }
			else		  { send(serConn, "1\n", sizeof("1\n"), NULL); }
			break;
		case 'w'://ȡǮ
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
		case 'c'://��ѯ��� 
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
	//��ʼ��socket��Դ
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
	{
		return 0;   //����ʧ��
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

	//HANDLE hThrd;
	HANDLE listener = CreateThread(NULL, 0, startListen, &serSocket, 0, NULL);
	while (1) {}

    return 0;
}

