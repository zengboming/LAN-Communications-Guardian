#pragma once
#include <list>
#include "MyMutex.h"
class CMyThread;
//��̶߳��С����Դ洢Ŀǰ����ִ��������̡߳�
/*CMyList�����Դ洢����ִ��������̡߳��ڲ�����listʵ�֡�
��߳���ִ��������󣬿��Ա���ʱ�ӻ������ɾ����
֮����ʹ����������Ϊ��������ɾ��ĳһԪ�صĿ�����С��*/
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

