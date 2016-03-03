#pragma once
#include<list>
#include "MyMutex.h"
#include "MyStack.h"
#include "MyList.h"
#include"MyQueue.h"
class CMyThread;
class CTask;
enum PRIORITY
{
	NORMAL,
	HIGH
};

class CBaseThreadPool
{
public:
	virtual bool SwitchActiveThread(CMyThread*)=0;
};

//�̳߳��࣬���Դ����������̳߳أ�ͬʱʵ�ֶ��̳߳����̵߳ĵ��ȡ�

/*������С���߳����������̶߳��ж���Ϊ�̳߳صĳ�Ա���������̳߳�ά����*/
class CMyThreadPool:public CBaseThreadPool
{
public:
	CMyThreadPool(int num);
	~CMyThreadPool(void);
public:
	virtual CMyThread* PopIdleThread();
	virtual bool SwitchActiveThread(CMyThread*);
	virtual CTask*GetNewTask();
public:
	//priorityΪ���ȼ��������ȼ������񽫱����뵽���ס�
	bool addTask(CTask*t,PRIORITY priority);
	bool start();//��ʼ���ȡ�
	bool destroyThreadPool();
private:
	int m_nThreadNum;
	bool m_bIsExit;
	
	//�����̶߳�ջ�����Դ洢���еĹ����߳�
	CMyStack m_IdleThreadStack;
	//��̶߳��С����Դ洢Ŀǰ����ִ��������̡߳�
	CMyList m_ActiveThreadList;
	//������С����Դ洢Ҫִ�е�����
	CMyQueue m_TaskQueue;
};

