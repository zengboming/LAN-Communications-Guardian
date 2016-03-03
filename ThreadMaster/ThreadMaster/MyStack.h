#pragma once
#include<stack>
#include "MyMutex.h"
class CMyThread ;
//�����̶߳�ջ�����Դ洢���еĹ����̡߳�
/*CMyStack�����Դ洢�����̡߳��ڲ�����stackʵ�֡�֮���Բ���ջ���洢�߳������
����Ϊ����һ���߳�ִ��������������ʱ�������û�������񣬸��߳̾ͱ�ѹ�뵽�����߳�ջ��
�˺�����������ʱ��ջ��Ԫ�أ�Ҳ���Ǹոձ�ѹ����̻߳ᱻ����ִ��������
���ڸ��߳�������ű�ѹ�룬���Ӧ�ڴ�ռ�λ���ڴ��еĸ��ʱ������̵߳ĸ���Ҫ��
����һ���̶��Ͽ��Խ�ʡ��ϵͳҳ�����ļ������������ڴ�Ŀ�����*/
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

