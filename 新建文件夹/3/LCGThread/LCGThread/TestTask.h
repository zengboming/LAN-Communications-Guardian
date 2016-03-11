#pragma once
#include "Task.h"

class CTestTask :
	public CTask
{
public:
	CTestTask(int id, char* recvBuff,SOCKET s);
	~CTestTask(void);
public:
	virtual void taskProc();
};
typedef struct
{
	char mac[40];
	char info[200];
} MailInfo;
