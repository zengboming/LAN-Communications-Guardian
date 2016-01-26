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
		//char sendBuf[50];
		//sprintf(sendBuf, "Welcome %s to here!", inet_ntoa(clientsocket.sin_addr));
		//send(serConn, sendBuf, strlen(sendBuf) + 1, 0);

		//���յ���Ϣ
		char recvBuff[200];	//���ܵ��ַ���
		char buff[199];		//�ɽṹ��ǿת���ַ���
		void *table;
		int k;				//sql_all����
		bool b;				//���سɹ����
		char command;		//����
		//���͵���Ϣ
		char sendBuff[200];
		//���ݿ���ʹ�õĽṹ��
		Customer  cus,*cu;
		Computer  com,*co;
		History   his,*hi;
		Senstive  sen,*se;
		Forbidweb fob,*fo;
		//socket��ʹ�õĽṹ��
		Customer1  cus1,*cu1;
		Computer1  com1,*co1;
		History1   his1,*hi1;
		Senstive1  sen1,*se1;
		Forbidweb1 fob1,*fo1;
		//�������ݿ�Ķ���
		DB_Help *db_help = new DB_Help();
		//��ʼ�����
		memset(recvBuff, 0, 200);
		memset(buff, 0, 199);
		memset(sendBuff, 0, 200);

		memset(&cus, 0x00, sizeof(Customer));
		memset(&com, 0x00, sizeof(Computer));
		memset(&his, 0x00, sizeof(History));
		memset(&sen, 0x00, sizeof(Senstive));
		memset(&fob, 0x00, sizeof(Forbidweb));

		memset(&cus1, 0x00, sizeof(Customer1));
		memset(&com1, 0x00, sizeof(Computer1));
		memset(&his1, 0x00, sizeof(History1));
		memset(&sen1, 0x00, sizeof(Senstive1));
		memset(&fob1, 0x00, sizeof(Forbidweb1));

		
		//���ղ�����
		recv(serConn, recvBuff, sizeof(recvBuff), NULL);
		cout << "recvBuff:" ;
		for (int i = 0; i < sizeof(recvBuff); i++) {
			cout << recvBuff[i];
		}
		cout << endl;
		command = recvBuff[0];
		cout << "command:" << command << endl;
		memcpy(buff,recvBuff+1,sizeof(recvBuff)-1);
		//��Ҫ��struct�е�char[]ת��string
		int j = 0;//�����С
		int i ;
		switch (command)
		{
		case 'a':                     //�����
			//��ѯĳ��ȫ����Ϣ
			k = (int)(recvBuff[1]-'0');
			cout << "k=" << k << endl;
			cout << "j=" << j << endl;
			switch (k)
			{
			case COMPUTER_TABLE:
				co = (Computer*)db_help->sql_all(k);
				j = co[0].num;
				cout << "j=" << j << endl;
				_itoa(j, sendBuff, 10);
				send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
				if (j != 0) {
					for (i = 0; i < j; i++) {
						memcpy(com1.ip, co[i].ip.c_str(), sizeof(co[i].ip));//ComputerתComputer1
						com1.online = co[i].online;
						com1.up_speed = co[i].up_speed;
						com1.down_speed = co[i].down_speed;
						memcpy(sendBuff, &com1, sizeof(com1));
						send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
						cout << "sendbuff: " << sendBuff << endl;
					}
				}
				break; 
			case SENSTIVE_TABLE:
				se = (Senstive*)db_help->sql_all(k);
				j = se[0].num;
				cout << "j=" << j << endl;
				_itoa(j, sendBuff, 10);
				send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
				if (j != 0) {
					for (i = 0; i < j; i++) {
						memcpy(sen1.ip, se[i].ip.c_str(), sizeof(se[i].ip));
						memcpy(sen1.word, se[i].word.c_str(), sizeof(se[i].word));
						memcpy(sendBuff, &sen1, sizeof(sen1));
						send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
						cout << "sendbuff: " << sendBuff << endl;
					}
				}
				break;
			case FORBIDWEB_TABLE:
				fo = (Forbidweb*)db_help->sql_all(k);
				j = fo[0].num;
				cout << "j=" << j << endl;
				_itoa(j, sendBuff, 10);
				send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
				if (j != 0) {
					for (i = 0; i < j; i++) {
						memcpy(fob1.ip, fo[i].ip.c_str(), sizeof(fo[i].ip));
						memcpy(fob1.web, fo[i].web.c_str(), sizeof(fo[i].web));
						memcpy(sendBuff, &fob1, sizeof(fob1));
						send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
						cout << "sendbuff: " << sendBuff << endl;
					}
				}
				break;
			case HISTORY_TABLE:
				hi = (History*)db_help->sql_all(k);
				j = hi[0].num;
				cout << "j=" << j << endl;
				_itoa(j, sendBuff, 10);
				send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
				if (j != 0) {
					for (i = 0; i < j; i++) {
						memcpy(his1.ip, hi[i].ip.c_str(), sizeof(hi[i].ip));
						memcpy(his1.address, hi[i].address.c_str(), sizeof(hi[i].address));
						memcpy(his1.time, hi[i].time.c_str(), sizeof(hi[i].time));
						memcpy(sendBuff, &his1, sizeof(his1));
						send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
						cout << "sendbuff: " << sendBuff << endl;
					}
				}
				break;
			}
			break;
		case 'b':
			//ͨ��ip��ѯĳ����
			com = db_help->select_computer(buff);
			cout << "com:" << com.ip << "	" << com.online << endl;
			memcpy(com1.ip,com.ip.c_str(),sizeof(com.ip));//ComputerתComputer1
			com1.online = com.online;
			com1.up_speed = com.up_speed;
			com1.down_speed = com.down_speed;
			memcpy(sendBuff, &com1, sizeof(com1));
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'c':                     //�����
			//ͨ��ip��ѯĳ������ʷ��¼ 
			hi = db_help->select_history(buff);
			cout << "hi:" << hi[0].ip << "	" << hi[0].address << endl;
			memcpy(sendBuff, &hi, sizeof(hi));
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'd':                     //�����
			//ͨ��ip��ѯĳ���Խ�ֹ������ַ 
			fo = db_help->select_forbidweb(buff);
			cout << "fo" << fo[0].ip << "	" << fo[0].web << endl;
			cout << "fo" << fo[1].ip << "	" << fo[1].web << endl;
			cout << "fo" << fo[2].ip << "	" << fo[2].web << endl;
			memcpy(sendBuff, &fo, sizeof(fo));
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'e':
			//��ѯ��¼�û�
			cus1 = *(Customer1*)buff;                        //���ܵ�Customer1
			cus = db_help->login(cus1.name, cus1.password);	 //���ص�Customer
			cout << "cus:" << cus.name << "	" << cus.password << "	" << cus.email << endl;
			memcpy(sendBuff, &cus, sizeof(cus));
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'f':
			//ɾ��ĳһ�����
			b = db_help->delete_computer(buff);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'g':
			//ɾ��ĳ����ֹ���ʵ���ַ
			fob1 = *(Forbidweb1*)buff;
			b = db_help->delete_forbidweb(fob1.ip, fob1.web);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'h':
			//ɾ��ĳ�����д�
			sen1 = *(Senstive1*)buff;
			b = db_help->delete_senstive(sen1.ip, sen1.word);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'i':
			//ɾ��ĳ�������ʷ��¼
			b = db_help->delete_history(buff);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'j':
			//���뵽��ֹ������ַ��
			fob1 = *(Forbidweb1*)buff;
			fob.ip = fob1.ip;
			fob.web = fob1.web;
			b = db_help->insert_forbidweb(fob);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'k':
			//���뵽���дʱ�
			sen1 = *(Senstive1*)buff;
			sen.ip = sen1.ip;
			sen.word = sen1.word;
			b = db_help->insert_senstive(sen);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'l':
			//���뵽�������
			com1 = *(Computer1*)buff;
			com.ip = com1.ip;
			com.online = com1.online;
			com.up_speed = com1.up_speed;
			com.down_speed = com1.down_speed;
			cout << com1.ip << "	" << com1.up_speed << "	" << com1.down_speed << "	" << com1.online << endl;
			b = db_help->insert_computer(com);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'n':
			//ע�����Ա
			cus1 = *(Customer1*)buff;
			cus.name = cus1.name;
			cus.password = cus1.password;
			cus.email = cus1.email;
			b = db_help->insert_customer(cus);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		case 'm':
			//���뵽��ʷ��¼��
			his1 = *(History1*)buff;
			his.ip = his1.ip;
			his.address = his1.address;
			his.time = his1.time;
			b = db_help->insert_history(his);
			cout << "b:" << b << endl;
			if (b) { memcpy(sendBuff, "1", sizeof("1")); }
			else { memcpy(sendBuff, "0", sizeof("0")); }
			send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			break;
		default:
			cout << "wrong command" << endl;
			break;
		}
		
		/*cout << "sendBuff:";
		for (int i = 0; i < sizeof(sendBuff); i++) {
			cout << sendBuff[i];
		}
		cout << endl;*/

		//char recvBuf[100];
		//recv(serConn, recvBuf, 50, 0);
		//printf("%s\n", recvBuf);

		//Test te;
		//char buff[100];
		//memset(buff, 0, 100);
		//memset(&te, 0x00, sizeof(Test));

		//ֱ�ӽ��սṹ��
		//recv(serConn, (char*)(&te), sizeof(Test), NULL);
		
		//�ڴ濽�����������(��Ϊջ������������,�����100����)
		//memcpy(&te, buff, sizeof(buff));
		
		//����char*��Ȼ��ת�ɽṹ��
		//recv(serConn,buff, sizeof(buff), NULL);
		//te = *(Test*)buff;
		//printf("ip=%s,name=%s\n", te.ip,te.name);

		//�����ַ�������һλ����������ǽṹ��
		/*recv(serConn, recvBuff, sizeof(recvBuff), NULL);
		for (int i = 0; i < sizeof(recvBuff); i++) {
			cout << recvBuff[i];
		}
		//char command ;
		command=recvBuff[0];
		//char newbuff[199];
		memcpy(buff, recvBuff + 1, sizeof(recvBuff)-1);
		//te = *(Test*)newbuff;
		//printf("ip=%s,name=%s\n", te.ip, te.name);
		fob1 = *(Forbidweb1*)buff;
		printf("ip=%s,web=%s", fob1.ip, fob1.web);*/


		closesocket(serConn);//�ر�
		closesocket(serSocket);//�ر�
		
		WSACleanup();//�ͷ���Դ�Ĳ���
		return 0;
	}
	return 1;
}

