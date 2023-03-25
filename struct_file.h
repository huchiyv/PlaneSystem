#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
#include<Windows.h>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include <time.h>

#define HEAD1 "*******************************************************************\n"
#define HEAD2 "|Flight|StartCity|DestCity|DepertureTime|Arrival|  price   |number|\n"
#define HEAD3 "|------|---------|--------|-------------|-------|----------|------|\n"
#define FORMET  "%-9s%-9s%-10s%-14s%-10s%-2.2f%6d\n"
#define DATA  pst->stDate.acFlight,pst->stDate.acOrigin,pst->stDate.acDest,pst->stDate.acTakeOffTime,pst->stDate.acReverceTime,pst->stDate.fPrice,pst->stDate.iNum

//机票结构体
typedef struct AirPlane
{
	char acFlight[20];//航班号
	char acOrigin[10]; //出发地
	char acDest[20];  //目的地
	char acTakeOffTime[10]; //起飞时间
	char acReverceTime[10]; //降落时间
	float fPrice;  //票价
	char acDisscount[4];  //折扣
	int iNum;  //剩余票数
}AirPlane, * PAirPlane;

//定义机票信息节点的结构体
typedef struct PlaneNode
{
	struct AirPlane stDate;
	struct PlaneNode* pstNext;

}PlaneNode, * PPlaneNode;

//客户信息结构体
typedef struct Man
{
	char acName[20];  //姓名
	char acID[20];   //身份证号码
	char acSex[10];   //性别 
	int  iBookNum;   //购票数量
	char acBookFilght[10];  //订购航班号
}Man, * PMan;

//订票人信息节点的结构体
typedef struct ManNode
{
	struct Man stDate;
	struct ManNode* pstNext;
}ManNode, * PManNode;
