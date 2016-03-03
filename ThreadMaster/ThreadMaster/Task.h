#pragma once
//任务基类。每个任务应继承自此类，并实现taskProc成员函数。
class CTask
{
public:
	CTask(int id,char key);
	~CTask(void);
public:
	virtual void taskProc()=0;
	int getID();
private:
	int m_ID;
	char m_Key;
};

