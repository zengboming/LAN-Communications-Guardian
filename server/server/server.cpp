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

	//发送的信息
	char sendBuff[200] ;	//接受的字符串
	char buff[199];		//由结构体强转的字符串
	Customer1  cus1;
	Computer1  com1;
	History1   his1,*hi1;
	Senstive1  sen1;
	Forbidweb1 fob1;
	
	//初始化清空
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
		//a 显示五张表中某表全部信息    
		send(sockClient, "a3", strlen("a3") + 1, NULL);
		break;
	case 'b':
		//b 查询某电脑信息
		send(sockClient, "b192.168.100.100",strlen("b192.168.100.100")+1,NULL);
		break;
	case 'c':
		//c 查询某电脑历史记录
		send(sockClient, "c192.168.80.80", strlen("c192.168.80.80") + 1, NULL);
		break;
	case 'd':
		//d 查询某电脑禁止访问的网站
		send(sockClient, "d192.168.90.90", strlen("d192.168.90.90") + 1, NULL);
		break;
	case 'e':
		//e 查询登录用户
		memcpy(cus1.name, "admin", sizeof("admin"));
		memcpy(cus1.password, "admin", sizeof("admin"));
		memcpy(buff, &cus1, sizeof(cus1));
		sendBuff[0] = 'e';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'f':
		//f 删除某一计算机
		send(sockClient, "f192.168.60.60", strlen("f192.168.60.60") + 1, NULL);
		break;
	case 'g':
		//g 删除某个禁止访问的网址
		memcpy(fob1.ip, "192.168.90.90", sizeof("192.168.100.100"));
		memcpy(fob1.web, "www.github.com", sizeof("www.github.com"));
		memcpy(buff, &fob1, sizeof(fob1));
		sendBuff[0] = 'g';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'h':
		//h 删除某个铭感词
		memcpy(sen1.ip, "192.168.90.90", sizeof("192.169.90.90"));
		memcpy(sen1.word, "doubi", sizeof("doubi"));
		memcpy(buff, &sen1, sizeof(sen1));
		sendBuff[0] = 'h';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'i':
		//i 删除某计算机的历史
		send(sockClient, "i192.168.80.80", strlen("i192.168.80.80") + 1, NULL);
		break;
	case 'j': 
		//j 插入到forbidweb表
		memcpy(fob1.ip, "192.168.90.90", sizeof("192.168.90.90"));
		memcpy(fob1.web, "www.github.com", sizeof("www.github.com"));
		memcpy(buff, &fob1, sizeof(fob1));
		sendBuff[0] = 'j';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'k':
		//k 插入到senstive表
		memcpy(sen1.ip, "192.168.90.90", sizeof("192.168.90.90"));
		memcpy(sen1.word, "doubi", sizeof("doubi"));
		memcpy(buff, &sen1, sizeof(sen1));
		sendBuff[0] = 'k';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'l':
		//l 插入到computer表
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
		//m 插入到history表
		memcpy(his1.ip, "192.168.80.80", sizeof("192.168.80.80"));
		memcpy(his1.address, "www.github.com", sizeof("www.github.com"));
		memcpy(his1.time, "2016.1.18,6:00", sizeof("2016.1.18,6:00"));
		memcpy(buff, &his1, sizeof(his1));
		sendBuff[0] = 'm';
		memcpy(sendBuff + 1, buff, sizeof(buff));
		send(sockClient, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'n':
		//n 注册管理员
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
		cout << "接收服务器返回的消息recvBuff:";
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
	memcpy(t, &fob1, sizeof(fob1));//如果设置1024，会因为栈过大而程序崩溃，可通过配置属性->c/c++->代码生成->基本运行时检查 设置为默认值解决
	com[0] = 'a';
	memcpy(com + 1, t, sizeof(t));
	for (int i = 0; i < sizeof(com); i++) {
		cout << com[i];
	}*/
	//发送字符串，第一位是命令，后面是结构体
	//send(sockClient, com, sizeof(com)+1, NULL);
	//直接发送结构体
	//send(sockClient, (char*)(&cp), sizeof(Test),NULL);
	//send(sockClient, "hello", strlen("hello") + 1, 0);
	//char recvBuf[50];
	//recv(sockClient, recvBuf, 50, 0);
	//printf("%s\n", recvBuf);
	

	closesocket(sockClient);
	WSACleanup();
}