#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#pragma comment( lib, "ws2_32.lib" )// 链接Winsock2.h的静态库文件 
using namespace std;
class OurCliSocket 
{
public:
	OurCliSocket();
	~OurCliSocket();
	bool Connect(int Type, const char *const IP, int PORT);//（Type默认为0）连接163服务器，初始化Socket（邮件用）
	bool Connect(const char *const IP, int PORT);//重载，连接服务器，初始化Socket
	bool Send(const string SendData);//发送信息到服务器 
	int Recv(char *sRecData);//接收信息

private:
	SOCKET sMySocket;
	//bool IPnameToAddr(const string IPname, string IPAddr);//转换网址到IP地址（邮件用）
	const static int BUFFSIZE = 1024;
};

struct Mail {//邮件结构体
	string Sender;//发件人
	string PassWord;//密码
	string Addressee;//收件人
	string Subject;//标题
	string Content;//内容（最好写入发送邮件时间，发送人iP等信息）
};


class DealMessage {
public:
	DealMessage();
	~DealMessage();
	bool JudgeMessage(char data);//解析data进行处理
	static bool SendMail_pthead( Mail* mail);//创建发送邮件线程
	bool DownLoadFile(const char*const IP, int PORT, int Type);//Type标识发送的是禁止IP还是敏感词
	static UINT SendMail(LPVOID lpParameter);//发送邮件
	static void Convert(const char* strIn, char *strOut, int sourceCodepage, int targetCodepage);
private:
	static string Base64Encode(const char* lpszSrc);//base64转码（邮件用）
	const bool CharToLong(const char cSize[], int cMaxSize, long& lSize);//文件长度转成long
	const static int DATASIZE = 1024;

};