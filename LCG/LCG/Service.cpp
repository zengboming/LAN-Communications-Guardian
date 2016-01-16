#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <string>
#include "db_help.cpp"
#include "struct.h"
#pragma comment( lib, "ws2_32.lib" )// ����Winsock2.h�ľ�̬���ļ� 
using namespace std;

static const int DATASIZE = 255;
/*struct Test {
	char ip[30];
	char name[30];
};*/


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
	char cData[DATASIZE] = { 0 };
	long lFileSize = 0;
	long cCur = 0;

	ifstream ReadStream;//���ļ�
	ReadStream.open(cPath, ios::binary);

	ReadStream.seekg(0, ios::end);//��ȡ�ļ���С
	lFileSize = ReadStream.tellg();

	sprintf(cData, "%d", lFileSize);//�����ļ���С
	send(sSendSocket, cData, 100, 0);
	while (cCur<lFileSize)
	{
		ReadStream.seekg(cCur);
		if (ReadStream.read(cData, DATASIZE))//δ����
		{
			send(sSendSocket, cData, DATASIZE, 0);
		}
		else
		{
			send(sSendSocket, cData, lFileSize - cCur, 0);
		}
		cCur += DATASIZE;
	}
	ReadStream.close();
	return true;
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

//////////////////////////////////////////////////////////////////////////
//��ʼ���м���
//////////////////////////////////////////////////////////////////////////
	SOCKADDR_IN clientsocket;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���

		//SendFile(serConn, "hello.JPG");
		char sendBuf[50];
		sprintf(sendBuf, "Welcome %s to here!", inet_ntoa(clientsocket.sin_addr));
		send(serConn, sendBuf, strlen(sendBuf) + 1, 0);

		//���յ���Ϣ
		char recvBuff[100];
		char buff[99];
		void* table;
		int k;
		bool b;
		char command;
		Customer  cus,*cu;
		Computer  com,*co;
		History   his,*hi;
		Senstive  sen,*se;
		Forbidweb fob,*fo;
		DB_Help *db_help = new DB_Help();
		//��ʼ�����
		memset(recvBuff, 0, 100);
		memset(buff, 0, 99);
		memset(&cus, 0x00, sizeof(Customer));
		memset(&com, 0x00, sizeof(Computer));
		memset(&his, 0x00, sizeof(History));
		memset(&sen, 0x00, sizeof(Senstive));
		memset(&fob, 0x00, sizeof(Forbidweb));
		//���ղ�����
		recv(serConn, recvBuff, sizeof(recvBuff), NULL);
		command = recvBuff[0];
		memcpy(buff,recvBuff+1,sizeof(recvBuff)-1);
		//��Ҫ��struct�е�char[]ת��string
		switch (command)
		{
		case 'a':
			//��ѯĳ��ȫ����Ϣ
			k = (int)(recvBuff[1]-'0');
			cout << "k=" << k;
			co=(Computer*)db_help->sql_all(k);
			cout << "co:" << co[0].ip << "	" << co[0].online << endl;
			cout << "co:" << co[1].ip << "	" << co[1].online << endl;
			break;
		case 'b':
			//ͨ��ip��ѯĳ����
			com = db_help->select_computer(buff);
			cout << "com:" << com.ip << "	" << com.online << endl;
			break;
		case 'c':
			//ͨ��ip��ѯĳ������ʷ��¼
			hi = db_help->select_history(buff);
			cout << "hi:" << hi[0].ip << "	" << hi[0].address << "	" << hi[0].time << endl;
			cout << "hi:" << hi[1].ip << "	" << hi[1].address << "	" << hi[1].time << endl;
			break;
		case 'd':
			//ͨ��ip��ѯĳ���Խ�ֹ������ַ
			fo = db_help->select_forbidweb(buff);
			cout << "fo" << fo[0].ip << "	" << fo[0].web << endl;
			cout << "fo" << fo[1].ip << "	" << fo[1].web << endl;
			break;
		case 'e':
			//��ѯ��¼�û�
			cus = *(Customer*)buff;
			cus = db_help->login(cus.name, cus.password);
			cout << "cus:" << cus.name << "	" << cus.password << "	" << cus.email << endl;
			break;
		case 'f':
			//ɾ��ĳһ�����
			b = db_help->delete_computer(buff);
			cout << "b:" << b << endl;
			break;
		case 'g':
			//ɾ��ĳ����ֹ���ʵ���ַ
			fob = *(Forbidweb*)buff;
			b = db_help->delete_forbidweb(fob.ip, fob.web);
			cout << "b:" << b << endl;
			break;
		case 'h':
			//ɾ��ĳ�����д�
			sen = *(Senstive*)buff;
			b = db_help->delete_senstive(sen.ip, sen.word);
			cout << "b:" << b << endl;
			break;
		case 'i':
			//ɾ��ĳ����ʷ��¼
			his = *(History*)buff;
			b = db_help->delete_history(his.ip, his.address);
			cout << "b:" << b << endl;
			break;
		case 'j':
			//���뵽��ֹ������ַ��
			fob = *(Forbidweb*)buff;
			b = db_help->insert_forbidweb(fob);
			cout << "b:" << b << endl;
			break;
		case 'k':
			//���뵽���дʱ�
			sen = *(Senstive*)buff;
			b = db_help->insert_senstive(sen);
			cout << "b:" << b << endl;
			break;
		case 'l':
			//���뵽�������
			com = *(Computer*)buff;
			b = db_help->insert_computer(com);
			cout << "b:" << b << endl;
			break;
		case 'm':
			//ע�����Ա
			cus = *(Customer*)buff;
			b = db_help->insert_customer(cus);
			cout << "b:" << b << endl;
			break;
		case 'n':
			//���뵽��ʷ��¼��
			his = *(History*)buff;
			b = db_help->insert_history(his);
			cout << "b:" << b << endl;
			break;
		default:
			cout << "wrong command" << endl;
			break;
		}











		//char recvBuf[100];
		//recv(serConn, recvBuf, 50, 0);
		//printf("%s\n", recvBuf);

		/*Test te;
		char buff[100];
		memset(buff, 0, 100);
		memset(&te, 0x00, sizeof(Test));*/

		//ֱ�ӽ��սṹ��
		//recv(serConn, (char*)(&te), sizeof(Test), NULL);
		
		//�ڴ濽�����������(��Ϊջ������������,�����100����)
		//memcpy(&te, buff, sizeof(buff));
		
		//����char*��Ȼ��ת�ɽṹ��
		//recv(serConn,buff, sizeof(buff), NULL);
		//te = *(Test*)buff;
		//printf("ip=%s,name=%s\n", te.ip,te.name);

		//�����ַ�������һλ����������ǽṹ��
		/*recv(serConn, buff, sizeof(buff), NULL);
		char command ;
		command=buff[0];
		char newbuff[99];
		memcpy(newbuff, buff + 1, sizeof(buff)-1);
		te = *(Test*)newbuff;
		printf("ip=%s,name=%s\n", te.ip, te.name);*/

		closesocket(serConn);//�ر�
		closesocket(serSocket);//�ر�
		
		//WSACleanup();//�ͷ���Դ�Ĳ���
		return 0;
	}
	return 1;
}

