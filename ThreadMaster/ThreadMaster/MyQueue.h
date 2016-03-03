#pragma once
#include<deque>
#include"MyMutex.h"
class CTask;
//任务队列。用以存储要执行的任务。
/*CMyQueue用以存储要执行的任务。内部采用双向队列实现。
具有简单的优先级控制机制。当普通的优先级任务到来时，会正常入队。
当高优先级任务到来时会插入到对首。线程池在调度时会简单的从队首取出任务并执行。*/
class CMyQueue
{
public:
	CMyQueue(void);
	~CMyQueue(void);
public:
	CTask*pop();
	bool push(CTask*t);
	bool pushFront(CTask*t);//插到队首。
	bool isEmpty();
	bool clear();
private:
	std::deque<CTask*>m_TaskQueue;
	CMyMutex m_mutex;
};

