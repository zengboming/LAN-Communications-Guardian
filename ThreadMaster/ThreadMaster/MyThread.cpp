#include "MyThread.h"
#include"task.h"
#include "MyThreadPool.h"
#include<cassert>
#define WAIT_TIME 20
//�����߳���
CMyThread::CMyThread(CBaseThreadPool*threadPool)
{
	m_pTask=NULL;
	//m_bIsActive=false;
	m_pThreadPool=threadPool;
	m_hEvent=CreateEvent(NULL,false,false,NULL);
	m_bIsExit=false;
}

//bool CMyThread::m_bIsActive=false;
CMyThread::~CMyThread(void)
{
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);
}

bool CMyThread::startThread()
{
	m_hThread=CreateThread(0,0,threadProc,this,0,&m_threadID);
	if(m_hThread==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}
bool CMyThread::suspendThread()
{
	ResetEvent(m_hEvent);
	return true;
}
//����������֪ͨ�̼߳���ִ�С�
bool CMyThread::resumeThread()
{
	SetEvent(m_hEvent);
	return true;
}
//startThread���ڴ�����ں���ΪthreadProc���̡߳��ڸ��߳��ڲ���ѭ���ȴ�һ���¼�����
//��û��������ʱ���߳̾ͻ��ڸ��¼������Ϲ��𡣵�����������
//�̳߳ػὫ���̶߳�Ӧ���¼����󴥷���Ȼ��ִ�����Ӧ������
DWORD WINAPI CMyThread::threadProc( LPVOID pParam )
{
	CMyThread *pThread=(CMyThread*)pParam;
	while(!pThread->m_bIsExit)
	{
 		DWORD ret=WaitForSingleObject(pThread->m_hEvent,INFINITE);
		if(ret==WAIT_OBJECT_0)
		{
			if(pThread->m_pTask)
			{
				pThread->m_pTask->taskProc();//ִ������
				//delete pThread->m_pTask;//�û�����Ŀռ佻���û������ڲ����������CTask�Ӷ�ջ���䣬�˴��������⡣
				pThread->m_pTask=NULL;
				//������ִ����֮���߳��ڲ�������̳߳ص�SwitchActiveThread��Ա������
				//�ú������Խ��̴߳ӻ״̬ת��Ϊ����̬��Ҳ���Ǵӻ�߳�����ת�Ƶ������߳�ջ�С�
				//ͬʱ�̼߳����ȴ��¼����󴥷���
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
	}
	return 0;
}
//������������߳��ࡣ
bool CMyThread::assignTask( CTask*pTask )
{
	assert(pTask);
	if(!pTask)
		return false;
	m_pTask=pTask;
	
	return true;
}
//��ʼִ������
bool CMyThread::startTask()
{
	resumeThread();
	return true;
}
