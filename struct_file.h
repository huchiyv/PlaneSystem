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

//��Ʊ�ṹ��
typedef struct AirPlane
{
	char acFlight[20];//�����
	char acOrigin[10]; //������
	char acDest[20];  //Ŀ�ĵ�
	char acTakeOffTime[10]; //���ʱ��
	char acReverceTime[10]; //����ʱ��
	float fPrice;  //Ʊ��
	char acDisscount[4];  //�ۿ�
	int iNum;  //ʣ��Ʊ��
}AirPlane, * PAirPlane;

//�����Ʊ��Ϣ�ڵ�Ľṹ��
typedef struct PlaneNode
{
	struct AirPlane stDate;
	struct PlaneNode* pstNext;

}PlaneNode, * PPlaneNode;

//�ͻ���Ϣ�ṹ��
typedef struct Man
{
	char acName[20];  //����
	char acID[20];   //���֤����
	char acSex[10];   //�Ա� 
	int  iBookNum;   //��Ʊ����
	char acBookFilght[10];  //���������
}Man, * PMan;

//��Ʊ����Ϣ�ڵ�Ľṹ��
typedef struct ManNode
{
	struct Man stDate;
	struct ManNode* pstNext;
}ManNode, * PManNode;
