#include "MyThreadPool.h"
#include "MyThread.h"
#include "Task.h"
#include<cassert>
#include<iostream>
#include "MyQueue.h"
CMyThreadPool::CMyThreadPool(int num)
{
	m_bIsExit=false;
	for(int i=0;i<num;i++)
	{
		CMyThread*p=new CMyThread(this);
		m_IdleThreadStack.push(p);
		p->startThread();
	}
}
CMyThreadPool::~CMyThreadPool(void)
{
}
CMyThread* CMyThreadPool::PopIdleThread()
{
	CMyThread *pThread=m_IdleThreadStack.pop();
	//pThread->m_bIsActive=true;
	return pThread;
}
//���̴߳ӻ����ȡ������������߳�ջ�С���ȡ֮ǰ�жϴ�ʱ��������Ƿ����������������Ϊ��ʱ�Ź��𡣷�����������ȡ�������ִ�С�
bool CMyThreadPool::SwitchActiveThread( CMyThread*t)
{
	if(!m_TaskQueue.isEmpty())//������в�Ϊ�գ�����ȡ����ִ�С�
	{
		CTask *pTask=NULL;
		pTask=m_TaskQueue.pop();
		std::cout<<"�̣߳�"<<t->m_threadID<<"   ִ��   "<<pTask->getID()<<std::endl;
	
		t->assignTask(pTask);
		t->startTask();	
	}
 	else//�������Ϊ�գ����̹߳���
	{
		m_ActiveThreadList.removeThread(t);
		m_IdleThreadStack.push(t);
	}
	return true;
}
bool CMyThreadPool::addTask( CTask*t,PRIORITY priority )
{
	assert(t);
	if(!t||m_bIsExit)
		return false;	
	CTask *task=NULL;
	std::cout<<"                                                   ["<<t->getID()<<"]��ӣ�"<<std::endl;
	if(priority==PRIORITY::NORMAL)
	{
		m_TaskQueue.push(t);//����������С�
	}
	else if(PRIORITY::HIGH)
	{
		m_TaskQueue.pushFront(t);//�����ȼ�����
	}

	if(!m_IdleThreadStack.isEmpty())//���ڿ����̡߳����ÿ����̴߳�������
	{
			task=m_TaskQueue.pop();//ȡ����ͷ����
			if(task==NULL)
			{
				std::cout<<"����ȡ������"<<std::endl;
				return 0;
			}
			CMyThread*pThread=PopIdleThread();
			std::cout<<"��"<<pThread->m_threadID<<"�� ִ��   ��"<<task->getID()<<"��"<<std::endl;
			m_ActiveThreadList.addThread(pThread);
			pThread->assignTask(task);
			pThread->startTask();	
	}
	
}
bool CMyThreadPool::start()
{
	return 0;
}
CTask* CMyThreadPool::GetNewTask()
{
	if(m_TaskQueue.isEmpty())
	{
		return NULL;
	}
	CTask *task=m_TaskQueue.pop();//ȡ����ͷ����
	if(task==NULL)
	{
		std::cout<<"����ȡ������"<<std::endl;
		return 0;
	}
	return task;
}
bool CMyThreadPool::destroyThreadPool()
{
	
	m_bIsExit=true;
	m_TaskQueue.clear();
	m_IdleThreadStack.clear();
	m_ActiveThreadList.clear();
	return true;
}
