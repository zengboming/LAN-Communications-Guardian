#pragma once
#include "windows.h"
class CTask;
class CBaseThreadPool;
//工作线程类。每个类管理一个线程。同时关联一个任务类对象。
/*CMyThread类用于管理一个线程。该类内部有一个CTask*成员和一个事件对象。
CTask*成员为与该线程关联的任务。调用assignTask可以为该线程设置对应的任务。*/
class CMyThread
{
public:
	CMyThread(CBaseThreadPool*threadPool);
	~CMyThread(void);
public:
	bool startThread();
	bool suspendThread();
	bool resumeThread();
	bool assignTask(CTask*pTask);
	bool startTask();
	static DWORD WINAPI threadProc(LPVOID pParam);
	DWORD m_threadID;
	HANDLE m_hThread;
	bool m_bIsExit;
private:
	
	HANDLE m_hEvent;
	CTask*m_pTask;
	CBaseThreadPool*m_pThreadPool;	
};
