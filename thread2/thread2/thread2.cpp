// thread2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

DWORD WINAPI ThreadFunc(LPVOID);

#define THREAD_POOL_SIZE 3
#define MAX_THREAD_INDEX THREAD_POOL_SIZE-1
#define NUM_TASKS 6


int main()
{
	HANDLE hThreds[THREAD_POOL_SIZE];
	int slot = 0;
	//DWORD exitCode;
	DWORD threadId;
	int i;
	DWORD rc;

	for (i = 1; i <= NUM_TASKS; i++)
	{
		if (i > THREAD_POOL_SIZE)
		{
			rc = WaitForMultipleObjects(THREAD_POOL_SIZE, hThreds, FALSE, INFINITE);
			slot = rc - WAIT_OBJECT_0;//哪一个被激发
			printf("slot %d determinated\n", slot);
			CloseHandle(hThreds[slot]);
			/*WaitForSingleObject(hThreds[slot], INFINITE);
			GetExitCodeThread(hThreds[slot], &exitCode);
			printf("slot %d determinated\n",exitCode);
			CloseHandle(hThreds[slot]);*/
		}

		hThreds[slot++] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)slot, 0, &threadId);
		printf("launched thread #%d (slot %d)\n", i, slot);
		/*hThreds[slot] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)slot, 0, &threadId);
		printf("launched thread #%d (slot %d)\n", i, slot);
		if (++slot > MAX_THREAD_INDEX)
			slot = 0;*/
	}
	//等待全部线程完成
	rc = WaitForMultipleObjects(THREAD_POOL_SIZE, hThreds, TRUE, INFINITE);
	for (slot = 0; slot < THREAD_POOL_SIZE; slot++)
		CloseHandle(hThreds[slot]);


	/*for (slot = 0; slot < THREAD_POOL_SIZE; slot++)
	{
		WaitForSingleObject(hThreds[slot], INFINITE);
		CloseHandle(hThreds[slot]);
	}*/
	printf("all slots determinated\n");


	/*HANDLE hThred;
	DWORD exitCode = 0;
	DWORD threadId;
	DWORD begin;
	DWORD elapsed;

	puts("timing normal function call...");
	begin = GetTickCount();//返回从操作系统启动到当前所经过的毫秒数，常常用来判断某个方法执行的时间
	ThreadFunc(0);
	elapsed = GetTickCount() - begin;
	printf("function call took: %d.%.03d seconds\n\n",elapsed/1000,elapsed%1000);
	puts("timing thread+busy loop...");
	begin = GetTickCount();
	hThred = CreateThread(NULL, 0, ThreadFunc, (LPVOID)1, 0, &threadId);
	for (;;)
	{
		GetExitCodeThread(hThred, &exitCode);
		if (exitCode != STILL_ACTIVE)
			break;
	}
	elapsed = GetTickCount() - begin;
	printf("thread+busy loop took: %d.%.03d seconds\n\n", elapsed / 1000, elapsed % 1000);
	CloseHandle(hThred);*/

	system("pause");
	return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
	srand(GetTickCount());
	Sleep(rand() % 8 * 500 + 500);
	printf("slot %d idle\n", n);
	return (DWORD)n;



	/*int i;
	int inside = 0;
	double val;

	UNREFERENCED_PARAMETER(n);//消除编译报告
	srand((unsigned)time(NULL));//随机数发生器的初始化函数 rand()产生随机数
	for (i = 0; i < 1000000; i++)
	{
		double x = (double)(rand()) / RAND_MAX;
		double y = (double)(rand()) / RAND_MAX;
		if ((x*x + y*y) <= 1.0)
			inside++;
	}

	val = (double)inside / i;
	printf("PI=%.4g\n",val*4);
	return 0;*/
}
