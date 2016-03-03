#pragma once
#include "Task.h"
//#include <winsock2.h>
class CTestTask :
	public CTask
{
public:
	CTestTask(int id,char* recvBuff);
	~CTestTask(void);
public:
	virtual void taskProc();
};

