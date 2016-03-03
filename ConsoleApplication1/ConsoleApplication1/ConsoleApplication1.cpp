// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

DWORD WINAPI ThreadFunc(LPVOID);
void AnotherFunc(void);

int main()
{

	HANDLE hThred;
	DWORD exitCode = 0;
	DWORD threadId;

	hThred = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)1,
		0,
		&threadId);
	if (hThred)
		printf("thread launched\n");
	for (;;) 
	{
		BOOL rc;
		rc = GetExitCodeThread(hThred,&exitCode);
		if (rc&&exitCode != STILL_ACTIVE) break;
	}
	CloseHandle(hThred);
	printf("thread returned %d\n", exitCode);

	system("pause");
	return EXIT_SUCCESS;


	/*HANDLE hThrd1;
	HANDLE hThrd2;
	DWORD exitCode1 = 0;
	DWORD exitCode2 = 0;
	DWORD threadId;

	hThrd1 = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)1,
		0,
		&threadId);

	if (hThrd1) 
		printf("thread 1 launched\n");

	hThrd2 = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)2,
		0,
		&threadId);
	
	if (hThrd2)
		printf("thread 2 launched\n");

	for (;;) 
	{
		printf("press any key to exit...\n");
		_getch();
		GetExitCodeThread(hThrd1, &exitCode1);
		GetExitCodeThread(hThrd2, &exitCode2);
		if (exitCode1 == STILL_ACTIVE)
			puts("thread 1 is still running!");
		if (exitCode2 == STILL_ACTIVE)
			puts("thread 2 is still running!");
		if (exitCode1 != STILL_ACTIVE&&exitCode2 != STILL_ACTIVE)
			break;
	}

	CloseHandle(hThrd1);
	CloseHandle(hThrd2);

	printf("thread 1 returned %d\n", exitCode1);
	printf("thread 2 returned %d\n", exitCode2);
	
	system("pause");
	return EXIT_SUCCESS;*/

	//int i;

	/*for (i = 0; i < 5; i++)
	{
		hThrd = CreateThread(NULL,
			0,
			ThreadFunc,
			(LPVOID)i,
			0,
			&threadId);
		if (hThrd) 
		{
			printf("Thread launched %d\n", i);
			CloseHandle(hThrd);
		}
	}



	Sleep(10000);
	system("pause");

	return EXIT_SUCCESS;*/


}

DWORD WINAPI ThreadFunc(LPVOID n) 
{
	printf("thread running\n");
	AnotherFunc();
	return 0;

	/*Sleep((DWORD)n * 1000 * 2);
	return (DWORD)n * 10;*/

	/*int i;
	for (i = 0; i < 10; i++) 
	{
		printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
	}
	return 0;*/
}

void AnotherFunc() 
{
	printf("about to exit thread\n");
	ExitThread(4);
	printf("this will never print\n");
}

