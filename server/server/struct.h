#pragma once
#include <iostream>
#include <string>
using namespace std;

#define COMPUTER_TABLE  1
#define CUSTOMER_TABLE  2
#define SENSTIVE_TABLE  3
#define FORBIDWEB_TABLE 4
#define HISTORY_TABLE   5

//computer�ṹ��
struct Computer {
	string  ip;
	double up_speed;
	double down_speed;
	bool   online;
};

//senstive�ṹ��
struct  Senstive
{
	string ip;
	string word;
};

//forbidweb�ṹ��
struct  Forbidweb
{
	string ip;
	string web;
};

//history�ṹ��
struct  History
{
	string ip;
	string address;
	string time;
};

struct Customer {
	string name;
	string password;
	string email;
};

//socket��ʹ�õĽṹ��
//computer�ṹ��
struct Computer1 {
	char  ip[45];
	double up_speed;
	double down_speed;
	bool   online;
};

//senstive�ṹ��
struct  Senstive1
{
	char ip[45];
	char word[45];
};

//forbidweb�ṹ��
struct  Forbidweb1
{
	char ip[45];
	char web[100];
};

//history�ṹ��
struct  History1
{
	char ip[45];
	char address[100];
	char time[45];
};

struct Customer1
{
	char name[45];
	char password[45];
	char email[45];
};