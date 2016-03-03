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

//线程池类，用以创建并管理线程池，同时实现对线程池内线程的调度。

/*任务队列、活动线程链表、空闲线程队列都作为线程池的成员变量，由线程池维护。*/
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
	//priority为优先级。高优先级的任务将被插入到队首。
	bool addTask(CTask*t,PRIORITY priority);
	bool start();//开始调度。
	bool destroyThreadPool();
private:
	int m_nThreadNum;
	bool m_bIsExit;
	
	//空闲线程堆栈，用以存储空闲的工作线程
	CMyStack m_IdleThreadStack;
	//活动线程队列。用以存储目前正在执行任务的线程。
	CMyList m_ActiveThreadList;
	//任务队列。用以存储要执行的任务。
	CMyQueue m_TaskQueue;
};

