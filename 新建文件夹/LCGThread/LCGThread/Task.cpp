#include "Task.h"
//#include <windows.h>
CTask::CTask(int id,char* recvBuff )
{
	m_ID=id;
	memcpy(m_recv, recvBuff, 200);
	//serConn = s;
}
CTask::~CTask(void)
{
}

int CTask::getID()
{
	return m_ID;
}
