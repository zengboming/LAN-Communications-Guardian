#pragma once
#include <Windows.h>

class CTask
{
public:
	CTask(int id, char* recvBuff,SOCKET s);
	~CTask(void);
public:
	virtual void taskProc() = 0;
	int getID();
	char sendBuff[2003];
protected:
	char m_recv[200];
	SOCKET serConn;
private:
	int m_ID;
};
