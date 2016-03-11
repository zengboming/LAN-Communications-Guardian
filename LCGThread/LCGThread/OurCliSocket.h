#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#pragma comment( lib, "ws2_32.lib" )// ����Winsock2.h�ľ�̬���ļ� 
using namespace std;
class OurCliSocket 
{
public:
	OurCliSocket();
	~OurCliSocket();
	bool Connect(int Type, const char *const IP, int PORT);//��TypeĬ��Ϊ0������163����������ʼ��Socket���ʼ��ã�
	bool Connect(const char *const IP, int PORT);//���أ����ӷ���������ʼ��Socket
	bool Send(const string SendData);//������Ϣ�������� 
	int Recv(char *sRecData);//������Ϣ

private:
	SOCKET sMySocket;
	//bool IPnameToAddr(const string IPname, string IPAddr);//ת����ַ��IP��ַ���ʼ��ã�
	const static int BUFFSIZE = 1024;
};

struct Mail {//�ʼ��ṹ��
	string Sender;//������
	string PassWord;//����
	string Addressee;//�ռ���
	string Subject;//����
	string Content;//���ݣ����д�뷢���ʼ�ʱ�䣬������iP����Ϣ��
};


class DealMessage {
public:
	DealMessage();
	~DealMessage();
	bool JudgeMessage(char data);//����data���д���
	static bool SendMail_pthead( Mail* mail);//���������ʼ��߳�
	bool DownLoadFile(const char*const IP, int PORT, int Type);//Type��ʶ���͵��ǽ�ֹIP�������д�
	static UINT SendMail(LPVOID lpParameter);//�����ʼ�
	static void Convert(const char* strIn, char *strOut, int sourceCodepage, int targetCodepage);
private:
	static string Base64Encode(const char* lpszSrc);//base64ת�루�ʼ��ã�
	const bool CharToLong(const char cSize[], int cMaxSize, long& lSize);//�ļ�����ת��long
	const static int DATASIZE = 1024;

};