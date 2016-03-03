#pragma once
#include<stack>
#include "MyMutex.h"
class CMyThread ;
//空闲线程堆栈，用以存储空闲的工作线程。
/*CMyStack类用以存储空闲线程。内部采用stack实现。之所以采用栈来存储线程类对象，
是因为：当一个线程执行完任务后，如果此时任务队列没有新任务，该线程就被压入到空闲线程栈。
此后当有新任务到来时，栈顶元素，也就是刚刚被压入的线程会被弹出执行新任务。
由于该线程是最近才被压入，其对应内存空间位于内存中的概率比其他线程的概率要大。
这在一定程度上可以节省从系统页交换文件交换到物理内存的开销。*/
class CMyStack
{
public:
	CMyStack(void);
	~CMyStack(void);
public:
	CMyThread* pop();
	bool push(CMyThread*);
	int getSize();
	bool isEmpty();
	bool clear();
private:
	std::stack<CMyThread*> m_stack;
	CMyMutex m_mutext;
};

