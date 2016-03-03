#pragma once
//#define WIN32_LEAN_AND_MEAN
//#include <winsock2.h>
#include <Windows.h>


class CTask
{
public:
	CTask(int id,char* recvBuff);
	~CTask(void);
public:
	virtual void taskProc()=0;
	int getID();
protected:
	char m_recv[200];
	//SOCKET serConn;
private:
	int m_ID;
};

