#pragma once
#include<deque>
#include"MyMutex.h"
class CTask;
//������С����Դ洢Ҫִ�е�����
/*CMyQueue���Դ洢Ҫִ�е������ڲ�����˫�����ʵ�֡�
���м򵥵����ȼ����ƻ��ơ�����ͨ�����ȼ�������ʱ����������ӡ�
�������ȼ�������ʱ����뵽���ס��̳߳��ڵ���ʱ��򵥵ĴӶ���ȡ������ִ�С�*/
class CMyQueue
{
public:
	CMyQueue(void);
	~CMyQueue(void);
public:
	CTask*pop();
	bool push(CTask*t);
	bool pushFront(CTask*t);//�嵽���ס�
	bool isEmpty();
	bool clear();
private:
	std::deque<CTask*>m_TaskQueue;
	CMyMutex m_mutex;
};

