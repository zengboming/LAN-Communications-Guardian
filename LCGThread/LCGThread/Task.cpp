#include "Task.h"
#include <Windows.h>

CTask::CTask(int id, char* recvBuff,SOCKET s)
	: m_ID(id), serConn(s)
{
	memcpy(m_recv,recvBuff ,200);
	//send(serConn, "CTask", sizeof("CTask") + 1, NULL);
}
CTask::~CTask(void)
{
}

int CTask::getID()
{
	return m_ID;
}
