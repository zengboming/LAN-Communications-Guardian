#pragma once
#include "windows.h"
//�����ࡣ����ʵ���̻߳�����ʡ�CMyStack��CMyList��CMyQueue�ڲ���ʹ����CMyMutex�ࡣ�������̰߳�ȫ�ġ�
/*CMyMutex�����ڿ����̻߳�����ʡ��ڲ�����CRITICAL_SECTIONʵ�� ��
�ڶԻ�߳����������̶߳�ջ��������н��з���ʱ����Ҫ���л�����ʿ��ơ���ֹ���߳�ͬʱ���ʵ��µ�״̬��һ�µ�������֡�*/
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

