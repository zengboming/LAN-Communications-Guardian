#include "TestTask.h"
#include<iostream>
CTestTask::CTestTask(int id,char key)
	:CTask(id,key)
{
}
CTestTask::~CTestTask(void)
{
}
void CTestTask::taskProc()
{
	/*for(int i=0;i<10000;i++)
	{
		for(int j=0;j<10000;j++)
		{
			int temp=1;
			temp++;
		}
	}*/
}
