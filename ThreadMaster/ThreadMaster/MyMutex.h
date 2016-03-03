#pragma once
#include "windows.h"
//互斥类。用于实现线程互斥访问。CMyStack，CMyList和CMyQueue内部都使用了CMyMutex类。它们是线程安全的。
/*CMyMutex类用于控制线程互斥访问。内部采用CRITICAL_SECTION实现 。
在对活动线程链表、空闲线程堆栈、任务队列进行访问时都需要进行互斥访问控制。防止多线程同时访问导致的状态不一致的情况出现。*/
class CMyMutex
{
public:
	CMyMutex(void);
	~CMyMutex(void);
public:
	bool Lock();
	bool Unlock();
private:
	CRITICAL_SECTION m_cs;
};

