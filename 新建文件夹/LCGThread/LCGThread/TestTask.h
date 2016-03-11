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

