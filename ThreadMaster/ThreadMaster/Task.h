#pragma once
//������ࡣÿ������Ӧ�̳��Դ��࣬��ʵ��taskProc��Ա������
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

