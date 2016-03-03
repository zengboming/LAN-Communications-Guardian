#pragma once
#include "task.h"
//具体的任务类，并实现taskProc函数。在该函数实现需要线程池执行的任务。
class CTestTask :
	public CTask
{
public:
	CTestTask(int id,char key);
	~CTestTask(void);
public:
	virtual void taskProc();
};

