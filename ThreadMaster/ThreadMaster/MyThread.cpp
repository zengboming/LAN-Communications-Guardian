#include "MyThread.h"
#include"task.h"
#include "MyThreadPool.h"
#include<cassert>
#define WAIT_TIME 20
//工作线程类
CMyThread::CMyThread(CBaseThreadPool*threadPool)
{
	m_pTask=NULL;
	//m_bIsActive=false;
	m_pThreadPool=threadPool;
	m_hEvent=CreateEvent(NULL,false,false,NULL);
	m_bIsExit=false;
}

//bool CMyThread::m_bIsActive=false;
CMyThread::~CMyThread(void)
{
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);
}

bool CMyThread::startThread()
{
	m_hThread=CreateThread(0,0,threadProc,this,0,&m_threadID);
	if(m_hThread==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}
bool CMyThread::suspendThread()
{
	ResetEvent(m_hEvent);
	return true;
}
//有任务到来，通知线程继续执行。
bool CMyThread::resumeThread()
{
	SetEvent(m_hEvent);
	return true;
}
//startThread用于创建入口函数为threadProc的线程。在该线程内部会循环等待一个事件对象。
//当没有任务到来时，线程就会在该事件对象上挂起。当新任务到来，
//线程池会将该线程对应的事件对象触发，然后执行其对应的任务。
DWORD WINAPI CMyThread::threadProc( LPVOID pParam )
{
	CMyThread *pThread=(CMyThread*)pParam;
	while(!pThread->m_bIsExit)
	{
 		DWORD ret=WaitForSingleObject(pThread->m_hEvent,INFINITE);
		if(ret==WAIT_OBJECT_0)
		{
			if(pThread->m_pTask)
			{
				pThread->m_pTask->taskProc();//执行任务。
				//delete pThread->m_pTask;//用户传入的空间交由用户处理，内部不处理。如从CTask从堆栈分配，此处会有问题。
				pThread->m_pTask=NULL;
				//当任务执行完之后，线程内部会调用线程池的SwitchActiveThread成员函数，
				//该函数用以将线程从活动状态转变为空闲态。也就是从活动线程链表转移到空闲线程栈中。
				//同时线程继续等待事件对象触发。
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
	}
	return 0;
}
//将任务关联到线程类。
bool CMyThread::assignTask( CTask*pTask )
{
	assert(pTask);
	if(!pTask)
		return false;
	m_pTask=pTask;
	
	return true;
}
//开始执行任务。
bool CMyThread::startTask()
{
	resumeThread();
	return true;
}
