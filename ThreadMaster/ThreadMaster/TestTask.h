#pragma once
#include "task.h"
//����������࣬��ʵ��taskProc�������ڸú���ʵ����Ҫ�̳߳�ִ�е�����
class CTestTask :
	public CTask
{
public:
	CTestTask(int id,char key);
	~CTestTask(void);
public:
	virtual void taskProc();
};

