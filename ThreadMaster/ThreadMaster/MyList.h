#pragma once
#include <list>
#include "MyMutex.h"
class CMyThread;
//活动线程队列。用以存储目前正在执行任务的线程。
/*CMyList类用以存储正在执行任务的线程。内部采用list实现。
活动线程在执行完任务后，可以被随时从活动链表中删除。
之所以使用链表是因为在链表中删除某一元素的开销很小。*/
class CMyList
{
public:
	CMyList(void);
	~CMyList(void);
public:
	bool addThread(CMyThread*t);
	bool removeThread(CMyThread*t);
	int getSize();
	bool isEmpty();
	bool clear();

private:
	std::list<CMyThread*>m_list;
	CMyMutex m_mutex;
};

