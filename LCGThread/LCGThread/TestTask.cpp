#include "TestTask.h"
#include "db_help.cpp"
#include "iostream"
using namespace std;

CTestTask::CTestTask(int id,char* recvBuff,SOCKET s)
	:CTask(id,recvBuff,s)
{
	memset(sendBuff, 0, 200);
	cout << "生成任务：" <<m_recv<< endl;
	//send(serConn, "CTestTask", sizeof("CTestTask") + 1, NULL);
	//cout <<"构造函数:"<< serConn << endl;
}

CTestTask::~CTestTask(void)
{
}

void CTestTask::taskProc()
{
	char command;		//命令
	char buff[199];		//由结构体强转的字符串
	int k;				//sql_all参数
	int b;				//返回成功与否
						//数据库中使用的结构体
	Customer  cus;
	Computer  com, *co;
	History   his, *hi;
	Senstive  sen, *se;
	Forbidweb fob, *fo;
	//socket中使用的结构体
	Customer1  cus1;
	Computer1  com1;
	History1   his1;
	Senstive1  sen1;
	Forbidweb1 fob1;
	//操作数据库的对象
	DB_Help *db_help = new DB_Help();
	//清空
	memset(buff, 0, 199);
	memset(sendBuff, 0, 200);
	//memset(m_send, 0, 200);
	//memset(&cus, 0x00, sizeof(Customer));
	memset(&com, 0x00, sizeof(Computer));
	memset(&his, 0x00, sizeof(History));
	memset(&sen, 0x00, sizeof(Senstive));
	memset(&fob, 0x00, sizeof(Forbidweb));

	memset(&cus1, 0x00, sizeof(Customer1));
	memset(&com1, 0x00, sizeof(Computer1));
	memset(&his1, 0x00, sizeof(History1));
	memset(&sen1, 0x00, sizeof(Senstive1));
	memset(&fob1, 0x00, sizeof(Forbidweb1));

	cout << "recvBuff happened:" << endl;
	for (int i = 0; i < sizeof(m_recv); i++) {
		cout << m_recv[i];
	}
	cout << endl;

	command = m_recv[0];
	cout << "command:" << command << endl;
	memcpy(buff, m_recv + 1, sizeof(m_recv) - 1);

	int j = 0;//数组大小
	int i;
	switch (command)
	{
	case 'a':
		//查询某表全部信息
		k = (int)(m_recv[1] - '0');
		cout << "表：" << k << endl;
		switch (k)
		{
		case COMPUTER_TABLE:
			co = (Computer*)db_help->sql_all(&k);  //引用参数 返回数组大小
												   //j = co[0].num;
			j = k;
			cout << "数量j：" << j << endl;
			//_itoa(j, sendBuff, 10);//int 转 char*
			//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			memcpy(sendBuff, _itoa(j, sendBuff, 10), 2);//sendBuff：前两位是条数，后面每200位是一个结构体
			if (j != 0) {
				for (i = 0; i < j; i++) {
					memcpy(com1.ip, co[i].ip.c_str(), sizeof(co[i].ip));//Computer转Computer1
					com1.online = co[i].online;
					com1.up_speed = co[i].up_speed;
					com1.down_speed = co[i].down_speed;
					memcpy(sendBuff+2+i*200, &com1, sizeof(com1));
					//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
					cout << "sendbuff: " << sendBuff << endl;
				}
			}
			break;
		case SENSTIVE_TABLE:
			se = (Senstive*)db_help->sql_all(&k);
			//j = se[0].num;
			j = k;
			cout << "j=" << j << endl;
			//_itoa(j, sendBuff, 10);
			memcpy(sendBuff, _itoa(j, sendBuff, 10), 2);
			//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			if (j != 0) {
				for (i = 0; i < j; i++) {
					memcpy(sen1.ip, se[i].ip.c_str(), sizeof(se[i].ip));
					memcpy(sen1.word, se[i].word.c_str(), sizeof(se[i].word));
					memcpy(sendBuff + 2 + i * 200, &sen1, sizeof(sen1));
					//memcpy(sendBuff, &sen1, sizeof(sen1));
					//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
					cout << "sendbuff: " << sendBuff << endl;
				}
			}
			break;
		case FORBIDWEB_TABLE:
			fo = (Forbidweb*)db_help->sql_all(&k);
			//j = fo[0].num;
			j = k;
			cout << "j=" << j << endl;
			//_itoa(j, sendBuff, 10);
			memcpy(sendBuff, _itoa(j, sendBuff, 10), 2);
			//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			if (j != 0) {
				for (i = 0; i < j; i++) {
					memcpy(fob1.ip, fo[i].ip.c_str(), sizeof(fo[i].ip));
					memcpy(fob1.web, fo[i].web.c_str(), sizeof(fo[i].web));
					memcpy(sendBuff + 2 + i * 200, &fob1, sizeof(fob1));
					//memcpy(sendBuff, &fob1, sizeof(fob1));
					//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
					cout << "sendbuff: " << sendBuff << endl;
				}
			}
			break;
		case HISTORY_TABLE:
			hi = (History*)db_help->sql_all(&k);
			//j = hi[0].num;
			j = k;
			cout << "j=" << j << endl;
			//_itoa(j, sendBuff, 10);
			memcpy(sendBuff, _itoa(j, sendBuff, 10), 2);
			//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			if (j != 0) {
				for (i = 0; i < j; i++) {
					memcpy(his1.ip, hi[i].ip.c_str(), sizeof(hi[i].ip));
					memcpy(his1.address, hi[i].address.c_str(), sizeof(hi[i].address));
					memcpy(his1.time, hi[i].time.c_str(), sizeof(hi[i].time));
					memcpy(sendBuff + 2 + i * 200, &his1, sizeof(his1));
					//memcpy(sendBuff, &his1, sizeof(his1));
					//(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
					cout << "sendbuff: " << sendBuff << endl;
				}
			}
			break;
		}
		break;
	case 'b':
		//通过ip查询某电脑
		com = db_help->select_computer(buff);
		cout << "com:" << com.ip << "	" << com.online << endl;
		memcpy(com1.ip, com.ip.c_str(), sizeof(com.ip));//Computer转Computer1
		com1.online = com.online;
		com1.up_speed = com.up_speed;
		com1.down_speed = com.down_speed;
		memcpy(sendBuff, &com1, sizeof(com1));
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'c':
		//通过ip查询某电脑历史记录 
		hi = db_help->select_history(buff);
		k = atoi(buff);
		cout << "k=" << k << endl;
		//_itoa(k, sendBuff, 10);
		memcpy(sendBuff, _itoa(k, sendBuff, 10), 2);
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);//发送数组大小
		for (int i = 0; i < k; i++)
		{
			cout << "hi:" << hi[i].ip << "	" << hi[i].address << endl;
			memcpy(his1.ip, hi[i].ip.c_str(), sizeof(hi[i].ip));     //his转his1
			memcpy(his1.address, hi[i].address.c_str(), sizeof(hi[i].address));
			memcpy(his1.time, hi[i].time.c_str(), sizeof(hi[i].time));
			memcpy(sendBuff + 2 + i * 200, &his1, sizeof(his1));
			//memcpy(sendBuff, &his1, sizeof(his1));
			//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		}
		break;
	case 'd':
		//通过ip查询某电脑禁止访问网址 
		fo = db_help->select_forbidweb(buff);
		k = atoi(buff);
		//_itoa(k, sendBuff, 10);
		memcpy(sendBuff, _itoa(k, sendBuff, 10), 2);
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);//发送数组大小
		for (int i = 0; i < k; i++)
		{
			cout << "fo" << fo[i].ip << "	" << fo[i].web << endl;
			memcpy(fob1.ip, fo[i].ip.c_str(), sizeof(fo[i].ip));
			memcpy(fob1.web, fo[i].web.c_str(), sizeof(fo[i].web));
			memcpy(sendBuff + 2 + i * 200, &fob1, sizeof(fob1));
			//memcpy(sendBuff, &fob1, sizeof(fob1));
			//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
			//cout << "sendBUFF:" << sendBuff << endl;
		}
		break;
	case 'e':
		//查询登录用户
		cus1 = *(Customer1*)buff;                        //接受的Customer1
		b = db_help->login(cus1.name, cus1.password);	 //返回的bool
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		cout << "sendbuff: " << sendBuff << endl;
		break;
	case 'f':
		//删除某一计算机
		b = db_help->delete_computer(buff);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'g':
		//删除某个禁止访问的网址
		fob1 = *(Forbidweb1*)buff;
		b = db_help->delete_forbidweb(fob1.ip, fob1.web);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'h':
		//删除某个敏感词
		sen1 = *(Senstive1*)buff;
		b = db_help->delete_senstive(sen1.ip, sen1.word);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'i':
		//删除某计算机历史记录
		b = db_help->delete_history(buff);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'j':
		//插入到禁止访问网址表
		fob1 = *(Forbidweb1*)buff;
		fob.ip = fob1.ip;
		fob.web = fob1.web;
		b = db_help->insert_forbidweb(fob);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'k':
		//插入到敏感词表
		sen1 = *(Senstive1*)buff;
		sen.ip = sen1.ip;
		sen.word = sen1.word;
		b = db_help->insert_senstive(sen);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'l':
		//插入到计算机表
		com1 = *(Computer1*)buff;
		com.ip = com1.ip;
		com.online = com1.online;
		com.up_speed = com1.up_speed;
		com.down_speed = com1.down_speed;
		cout << com1.ip << "	" << com1.up_speed << "	" << com1.down_speed << "	" << com1.online << endl;
		b = db_help->insert_computer(com);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'n':
		//注册管理员
		cus1 = *(Customer1*)buff;
		cus.name = cus1.name;
		cus.password = cus1.password;
		cus.email = cus1.email;
		b = db_help->insert_customer(cus);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'm':
		//插入到历史记录表
		his1 = *(History1*)buff;
		his.ip = his1.ip;
		his.address = his1.address;
		his.time = his1.time;
		b = db_help->insert_history(his);
		cout << "b:" << b << endl;
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	case 'o':
		//修改计算机表
		com1 = *(Computer1*)buff;
		com.ip = com1.ip;
		cout << "ip:" << com.ip << endl;
		com.online = com1.online;
		cout << "online:" << com.online << endl;
		b = db_help->update_computer(com);
		if (b) { memcpy(sendBuff, "1", sizeof("1")); }
		else { memcpy(sendBuff, "0", sizeof("0")); }
		//send(serConn, sendBuff, sizeof(sendBuff) + 1, NULL);
		break;
	default:
		cout << "wrong command" << endl;
		break;
	}
}