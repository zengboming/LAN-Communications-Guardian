#pragma once
#include <iostream>
#include <string>
using namespace std;

#define COMPUTER_TABLE  1
#define CUSTOMER_TABLE  2
#define SENSTIVE_TABLE  3
#define FORBIDWEB_TABLE 4
#define HISTORY_TABLE   5

//computer结构体
struct Computer {
	string  ip;
	double up_speed;
	double down_speed;
	bool   online;
};

//senstive结构体
struct  Senstive
{
	string ip;
	string word;
};

//forbidweb结构体
struct  Forbidweb
{
	string ip;
	string web;
};

//history结构体
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

//socket中使用的结构体
//computer结构体
struct Computer1 {
	char  ip[45];
	double up_speed;
	double down_speed;
	bool   online;
};

//senstive结构体
struct  Senstive1
{
	char ip[45];
	char word[45];
};

//forbidweb结构体
struct  Forbidweb1
{
	char ip[45];
	char web[100];
};

//history结构体
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