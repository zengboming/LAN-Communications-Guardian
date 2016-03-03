#include "Task.h"
#include "windows.h"
CTask::CTask(int id,char key)
{
	m_ID=id;
	m_Key = key;

}
CTask::~CTask(void)
{
}

int CTask::getID()
{
	return m_ID;
}
