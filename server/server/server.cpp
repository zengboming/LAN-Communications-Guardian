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

	//���͵���Ϣ
	char sendBuff[200] ;	//���ܵ��ַ���
	char buff[199];		//�ɽṹ��ǿת���ַ���
	Customer1  cus1;
	Computer1  com1;
	History1   his1,*hi1;
	Senstive1  sen1;
	Forbidweb1 fob1;
	
	//��ʼ�����
	memset(sendBuff, 0, 200);
	memset(buff, 0, 199);
	int k = 0;
	char command;
	memset(&cus1, 0x00, sizeof(Customer1));
	memset(&com1, 0x00, sizeof(Computer1));
	memset(&his1, 0x00, sizeof(History1));
	memset(&sen1, 0x00, sizeof(Senstive1));
	memset(&fob1, 0x00, sizeof(Forbidweb1));

	command = 'd';
	switch (command)
	{
	case 'a':
		//a ��ʾ���ű���ĳ��ȫ����Ϣ    
		send(sockClient, "a3", strlen("a3") + 1, NULL);
		break;
	case 'b':
		//b ��ѯĳ������Ϣ
		send(sockClient, "b192.168.100.100",strlen("b192.168.100.100")+1,NULL);
		break;
	case 'c':
		//c ��ѯĳ������ʷ��¼
		send(sockClient, "c192.168.80.80", strlen("c192.168.80.80") + 1, NULL);
		break;
	case 'd':
		//d ��ѯĳ���Խ�ֹ���ʵ���վ
		send(sockClient, "d192.168.90.90", strlen("d192.168.90.90") + 1, NULL);
		break;
	case 'e':
		//e ��ѯ��¼�û�
		memcpy(cus1.name, "admin", sizeof("admin"));
		memcpy(cus1.password, "admin", sizeof("admin"));
		memcpy(buff, &cus1, sizeof(cus1));
		sendBuff[0] = 'e';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'f':
		//f ɾ��ĳһ�����
		send(sockClient, "f192.168.60.60", strlen("f192.168.60.60") + 1, NULL);
		break;
	case 'g':
		//g ɾ��ĳ����ֹ���ʵ���ַ
		memcpy(fob1.ip, "192.168.90.90", sizeof("192.168.100.100"));
		memcpy(fob1.web, "www.github.com", sizeof("www.github.com"));
		memcpy(buff, &fob1, sizeof(fob1));
		sendBuff[0] = 'g';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'h':
		//h ɾ��ĳ�����д�
		memcpy(sen1.ip, "192.168.90.90", sizeof("192.169.90.90"));
		memcpy(sen1.word, "doubi", sizeof("doubi"));
		memcpy(buff, &sen1, sizeof(sen1));
		sendBuff[0] = 'h';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'i':
		//i ɾ��ĳ���������ʷ
		send(sockClient, "i192.168.80.80", strlen("i192.168.80.80") + 1, NULL);
		break;
	case 'j': 
		//j ���뵽forbidweb��
		memcpy(fob1.ip, "192.168.90.90", sizeof("192.168.90.90"));
		memcpy(fob1.web, "www.github.com", sizeof("www.github.com"));
		memcpy(buff, &fob1, sizeof(fob1));
		sendBuff[0] = 'j';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'k':
		//k ���뵽senstive��
		memcpy(sen1.ip, "192.168.90.90", sizeof("192.168.90.90"));
		memcpy(sen1.word, "doubi", sizeof("doubi"));
		memcpy(buff, &sen1, sizeof(sen1));
		sendBuff[0] = 'k';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'l':
		//l ���뵽computer��
		memcpy(com1.ip, "192.168.40.40", sizeof("192.168.40.40"));
		com1.online = 1;
		com1.up_speed = 50;
		com1.down_speed = 50;
		memcpy(buff, &com1, sizeof(com1));
		sendBuff[0] = 'l';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'm':
		//m ���뵽history��
		memcpy(his1.ip, "192.168.80.80", sizeof("192.168.80.80"));
		memcpy(his1.address, "www.github.com", sizeof("www.github.com"));
		memcpy(his1.time, "2016.1.18,6:00", sizeof("2016.1.18,6:00"));
		memcpy(buff, &his1, sizeof(his1));
		sendBuff[0] = 'm';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'n':
		//n ע�����Ա
		memcpy(cus1.name, "lufei", sizeof("lufei"));
		memcpy(cus1.password, "lufei123", sizeof("lufei123"));
		memcpy(cus1.email, "lufei@163.com", sizeof("lufei@163.com"));
		memcpy(buff, &cus1, sizeof(cus1));
		sendBuff[0] = 'n';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'o':
		memcpy(com1.ip, "192.168.50.50", sizeof("192.168.40.40"));
		com1.online = 1;
		memcpy(buff, &com1, sizeof(com1));
		sendBuff[0] = 'o';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	}
	//cout << "ok" << endl;

	for (int i = 0; i < 4; i++) {
		cout << "���շ��������ص���ϢrecvBuff:";
		char recvBuff[200];
		memset(recvBuff, 0, 200);
		recv(sockClient, recvBuff, 200, 0);
		for (int i = 0; i < sizeof(recvBuff); i++) {
			cout << recvBuff[i];
		}
		cout << endl;
	}

	/*memcpy(hi1[0].ip, "192.168", sizeof("192.168"));
	memcpy(hi1[0].address, "www.baidu.com", sizeof("www.baidu.com"));
	memcpy(hi1[0].time, "2016.1.18", sizeof("2016.1.18"));
	memcpy(hi1[1].ip, "192.168.1", sizeof("192.168.1"));
	memcpy(hi1[1].address, "www.taobao.com", sizeof("www.taobao.com"));
	memcpy(hi1[1].time, "2016.1.18", sizeof("2016.1.18"));
	memcpy(hi1[2].ip, "192.168.1.1", sizeof("192.168.1.1"));
	memcpy(hi1[2].address, "www.leshi.com", sizeof("www.leshi.com"));
	memcpy(hi1[2].time, "2016.1.18", sizeof("2016.1.18"));
	char newbuff[400];
	memset(newbuff, 0, sizeof(newbuff));
	memset(hi1->ip, 0, 45);
	memset(hi1->address, 0, 100);
	memset(hi1->time, 0, 45);
	memcpy(newbuff, hi1, sizeof(hi1));
	send(sockClient,newbuff, 400, NULL);
	for (int i = 0; i < sizeof(newbuff); i++) {
		cout << newbuff[i];
	}*/


	//Test cp;
	//memset(&cp, 0x00, sizeof(Test));
	//memcpy(cp.ip,"192.168.0.1",sizeof("192.168.0.1"));
	//memcpy(cp.name, "hello", sizeof("hello"));
	/*memcpy(fob1.ip, "192.168.0.1", sizeof("192.168.0.1"));
	memcpy(fob1.web, "www.github.com", sizeof("www.github.com"));
	char com[200] = { 0 };
	char t[199] = {0};
	memset(t, 0, 99);
	memcpy(t, &fob1, sizeof(fob1));//�������1024������Ϊջ����������������ͨ����������->c/c++->��������->��������ʱ��� ����ΪĬ��ֵ���
	com[0] = 'a';
	memcpy(com + 1, t, sizeof(t));
	for (int i = 0; i < sizeof(com); i++) {
		cout << com[i];
	}*/
	//�����ַ�������һλ����������ǽṹ��
	//send(sockClient, com, sizeof(com)+1, NULL);
	//ֱ�ӷ��ͽṹ��
	//send(sockClient, (char*)(&cp), sizeof(Test),NULL);
	//send(sockClient, "hello", strlen("hello") + 1, 0);
	//char recvBuf[50];
	//recv(sockClient, recvBuf, 50, 0);
	//printf("%s\n", recvBuf);
	

	closesocket(sockClient);
	WSACleanup();
}