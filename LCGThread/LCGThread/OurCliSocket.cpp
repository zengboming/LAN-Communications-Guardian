#include "OurCliSocket.h"

OurCliSocket::OurCliSocket()
{


};

OurCliSocket::~OurCliSocket()
{
	closesocket(sMySocket);
	WSACleanup();
};

bool OurCliSocket::Connect(int Type, const char*const IP, int PORT)//��TypeĬ��Ϊ0������163����������ʼ��Socket���ʼ��ã�
{
	WSADATA wsa;
	/*��ʼ��socket��Դ*/
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
	{
		return 0;   //����ʧ��
	}
	sMySocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	hostent* pHost = gethostbyname(IP);
	char ip[32] = { 0 };
	sprintf(ip, "%d.%d.%d.%d",
		(pHost->h_addr_list[0][0] & 0x00ff),
		(pHost->h_addr_list[0][1] & 0x00ff),
		(pHost->h_addr_list[0][2] & 0x00ff),
		(pHost->h_addr_list[0][3] & 0x00ff));
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	if (-1 == connect(sMySocket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
	{
		return 0;
	}

	return 1;
}

bool OurCliSocket::Connect(const char *const IP, int PORT)//���أ����ӷ���������ʼ��Socket
{
	WSADATA wsa;
	/*��ʼ��socket��Դ*/
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
	{
		return 0;   //����ʧ��
	}
	sMySocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(IP);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	if (-1 == connect(sMySocket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
	{
		return 0;
	}

	return 1;
}

bool OurCliSocket::Send(const string SendData)//������Ϣ�������� 
{

	if (0 < send(sMySocket, SendData.c_str(), SendData.length(), 0))
	{
		return 1;
	}
	else {
		return 0;
	}
}

int OurCliSocket::Recv(char *sRecData)//������Ϣ
{
	char cData[BUFFSIZE] = { 0 };
	int result = recv(sMySocket, cData, BUFFSIZE, 0);
	if (0 < result)
	{
		cout << cData << endl;
		strcpy(sRecData, cData);
		return result;
	}
	else {
		cout << "Recv Error" << endl;
		return -1;
	}
}
//*********************************************************************88
DealMessage::DealMessage() {};
DealMessage::~DealMessage() {};

bool DealMessage::JudgeMessage(char data)//����data���д���
{
	switch (data)
	{
	case 'd'://�������д�

		break;

	default:
		break;
	}
	return 1;
}


void DealMessage::Convert(const char* strIn, char *strOut, int sourceCodepage, int targetCodepage)
{
	int len = strlen(strIn);
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strIn, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage, 0, strIn, -1, (LPWSTR)pUnicode, unicodeLen);
	BYTE * pTargetData = NULL;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, 0, NULL, NULL);
	pTargetData = new BYTE[targetLen + 1];
	memset(pTargetData, 0, targetLen + 1);
	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, targetLen, NULL, NULL);
	strcpy(strOut, (char*)pTargetData);
	delete pUnicode;
	delete pTargetData;
}

UINT  DealMessage::SendMail(LPVOID lpParameter)//�����ʼ�
{
	Mail* mail = (Mail*)lpParameter;
	char  sRecString[200];
	OurCliSocket ourClisocket;
	if (0 == ourClisocket.Connect(0, "smtp.163.com", 25))
	{
		cout << "Email create fail" << endl;
		return 0;
	}
	ourClisocket.Recv(sRecString);


	string sEnd = "\r\n";
	ourClisocket.Send("HELO Jhon" + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send("auth login" + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send(Base64Encode(mail->Sender.c_str()) + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send(Base64Encode(mail->PassWord.c_str()) + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send("mail from: <" + mail->Sender + "> " + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send("rcpt to:<" + mail->Addressee + ">" + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send("data" + sEnd);
	ourClisocket.Recv(sRecString);
	//��ʼ��������
	string sData;
	sData = "from: " + mail->Sender + sEnd
		+ "to: " + mail->Addressee + sEnd
		+ "SubJect: " + mail->Subject + sEnd
		+ sEnd
		//����
		+ mail->Content + sEnd
		+ "." + sEnd;
	char data[200];
	Convert(sData.c_str(), data, CP_ACP, CP_UTF8);
	ourClisocket.Send(string(data) + sEnd);
	ourClisocket.Recv(sRecString);
	ourClisocket.Send("quit" + sEnd);
	ourClisocket.Recv(sRecString);

	delete mail;
	return 1;
}

bool DealMessage::DownLoadFile(const char*const IP, int PORT, int Type)//Type��ʶ���͵��ǽ�ֹIP�������д�
{
	string cPath;
	switch (Type)
	{
	case 1:cPath = "minganci.txt";
		break;
	case 2:cPath = "wangzhi.txt";
		break;
	default:
		break;
	}

	OurCliSocket ourClisocket;
	if (0 == ourClisocket.Connect(IP, PORT))
	{
		cout << "FileSocket create fail" << endl;
		return 0;
	}

	char cData[DATASIZE] = { 0 };
	long lFileSize = 0;
	long cCur = 0;

	ofstream WriteStream;//���ļ�
	WriteStream.open(cPath, ios::binary);


	ourClisocket.Recv(cData);
	CharToLong(cData, DATASIZE, lFileSize);

	while (cCur < lFileSize)
	{
		memset(cData, 0, DATASIZE);
		int m = ourClisocket.Recv(cData);
		WriteStream.write(cData, m);
		cCur = WriteStream.tellp();
	}
	WriteStream.close();
	return 1;
}

const bool DealMessage::CharToLong(const char cSize[], int cMaxSize, long& lSize)
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

string DealMessage::Base64Encode(const char* lpszSrc)//base64ת�루�ʼ��ã�
{
	//Base64�����
	const char BASE64_ENCODE_TABLE[64] = {
		65, 66, 67, 68, 69, 70, 71, 72, // 00 - 07
		73, 74, 75, 76, 77, 78, 79, 80, // 08 - 15
		81, 82, 83, 84, 85, 86, 87, 88, // 16 - 23
		89, 90, 97, 98, 99, 100, 101, 102, // 24 - 31
		103, 104, 105, 106, 107, 108, 109, 110, // 32 - 39
		111, 112, 113, 114, 115, 116, 117, 118, // 40 - 47
		119, 120, 121, 122, 48, 49, 50, 51, // 48 - 55
		52, 53, 54, 55, 56, 57, 43, 47 };// 56 - 63

	unsigned int iTest;

	const char* pInBuffer = lpszSrc;

	int nSize = (int)strlen(lpszSrc);
	char* pOutBuffer = new char[nSize / 3 * 4 + 5];
	memset(pOutBuffer, 0, nSize / 3 * 4 + 5);

	//3���ֽ�Ϊ��λ ȡ6λ����ǰ�油������0�γ��µ�8λ���� 3*8=4*6
	for (unsigned int i = 0; i < strlen(lpszSrc) / 3; i++)
	{
		iTest = (unsigned char)*pInBuffer++;
		iTest = iTest << 8;

		iTest = iTest | (unsigned char)*pInBuffer++;
		iTest = iTest << 8;

		iTest = iTest | (unsigned char)*pInBuffer++;

		//��4 byte����д���������
		pOutBuffer[3] = BASE64_ENCODE_TABLE[iTest & 0x3F];
		iTest = iTest >> 6;
		pOutBuffer[2] = BASE64_ENCODE_TABLE[iTest & 0x3F];
		iTest = iTest >> 6;
		pOutBuffer[1] = BASE64_ENCODE_TABLE[iTest & 0x3F];
		iTest = iTest >> 6;
		pOutBuffer[0] = BASE64_ENCODE_TABLE[iTest];
		pOutBuffer += 4;
	}

	//����β��
	switch (strlen(lpszSrc) % 3)
	{
	case 0:
		break;
	case 1:
		iTest = (unsigned char)*pInBuffer;
		iTest = iTest << 4;
		pOutBuffer[1] = BASE64_ENCODE_TABLE[iTest & 0x3F];
		iTest = iTest >> 6;
		pOutBuffer[0] = BASE64_ENCODE_TABLE[iTest];
		pOutBuffer[2] = '='; //��'='Ҳ����64�����ʣ�ಿ��
		pOutBuffer[3] = '=';
		break;
	case 2:
		iTest = (unsigned char)*pInBuffer++;
		iTest = iTest << 8;
		iTest = iTest | (unsigned char)*pInBuffer;
		iTest = iTest << 2;
		pOutBuffer[2] = BASE64_ENCODE_TABLE[iTest & 0x3F];
		iTest = iTest >> 6;
		pOutBuffer[1] = BASE64_ENCODE_TABLE[iTest & 0x3F];
		iTest = iTest >> 6;
		pOutBuffer[0] = BASE64_ENCODE_TABLE[iTest];
		pOutBuffer[3] = '='; // Fill remaining byte.
		break;
	}
	pOutBuffer -= nSize / 3 * 4;
	string strEncode = pOutBuffer;
	delete[] pOutBuffer;
	pOutBuffer = NULL;
	return strEncode;
}
