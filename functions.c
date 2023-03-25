#define _CRT_SECURE_NO_WARNINGS 1
#include"struct_file.h"
extern int iSave;
//主菜单
void Menu()
{
	puts("**********************************************************************");
	puts("****** Welcome to the airplane tickets booking system");
	puts("----------------------------------------------------------------------");
	puts("                    choose the follow operation(0-9)                 *");
	puts("--------------------------------------------------------------------- ");
	puts("***********      1 Insert  flights              2 Search  flights     ");
	puts("**********       3 Book tickets                 4 Modify  fligts  date");
	puts("**********       5 Show flights                 6 Recommend flights   ");
	puts("************     7 Refund tickets               8 Show current time   ");
	puts("***********      9 Save to files                0 quit                ");
	puts("**********************************************************************");
}
//打印函数
void PrintHead()
{
	printf(HEAD1);
	printf(HEAD2);
	printf(HEAD3);
}
void PrintDate(PPlaneNode stLP)
{
	PPlaneNode pst = stLP;
	printf(FORMET, DATA);

}
//销毁函数  防止内存泄漏
void Destroy(PPlaneNode pstPlaneNodeHead, PManNode pstManNodeHead)
{
	assert(pstManNodeHead != NULL);
	assert(pstPlaneNodeHead != NULL);
	PPlaneNode p = pstPlaneNodeHead->pstNext;
	PManNode q = pstManNodeHead->pstNext;
	while (p != NULL)
	{
		PPlaneNode tmp = p;
		p = p->pstNext;
		free(tmp);
	}
	while (q != NULL)
	{
		PManNode tmp = q;
		q = q->pstNext;
		free(tmp);
	}

}
// 初始化
int Init(struct PlaneNode* pstPlaneNodeHead, struct ManNode* pstManNodeHead)
{
	//先加载飞机机票信息
	FILE* pfPlane; //定义飞机机票信息文件指针
	struct PlaneNode* pstPlaneNodeTemp, * pstPlaneNodeCur;
	pstPlaneNodeCur = pstPlaneNodeHead;
	pstPlaneNodeTemp = NULL;
	pfPlane = fopen("plane.txt", "ab+");
	if (pfPlane == NULL)
	{
		printf("can't  open plane.txt!\n");
		return -1;
	}
	else
	{
		//把文件数据读入到链表中
		while (!feof(pfPlane)) //读到文件最后一个数据
		{
			pstPlaneNodeTemp = (struct PlaneNode*)malloc(sizeof(struct PlaneNode));
			if (fread(pstPlaneNodeTemp, sizeof(struct PlaneNode), 1, pfPlane) != 0)
			{
				pstPlaneNodeTemp->pstNext = NULL;
				pstPlaneNodeCur->pstNext = pstPlaneNodeTemp;
				pstPlaneNodeCur = pstPlaneNodeTemp;
			}
		}
		free(pstPlaneNodeTemp);  //此时，释放的是文件读完后最后一次申请的指针
		fclose(pfPlane);
	}
	//加载订票人信息
	FILE* pfMan;  // 定义订票人信息文件指针
	struct ManNode* pstManNodeTemp, * pstManNodeCur;
	pstManNodeCur = pstManNodeHead;
	pstManNodeTemp = NULL;
	pfMan = fopen("man.txt", "ab+");
	if (pfMan == NULL)
	{
		printf("can't open  man.txt!\n");
		return -1;
	}
	else
	{
		while (!feof(pfMan))
		{
			pstManNodeTemp = (struct ManNode*)malloc(sizeof(struct ManNode));
			if (fread(pstManNodeTemp, sizeof(struct ManNode), 1, pfMan) == 1)
			{
				pstManNodeTemp->pstNext = NULL;
				pstManNodeCur->pstNext = pstManNodeTemp;
				pstManNodeCur = pstManNodeTemp;
			}
		}
		free(pstManNodeTemp);
		fclose(pfMan);
	}
	return 0;
}
//添加机票
void Insert(struct PlaneNode* pstPlaneNodeHead)
{
	assert(pstPlaneNodeHead != NULL);
	if (pstPlaneNodeHead == NULL)
	{
		return;
	}
	struct PlaneNode* pstNode, * pstHead, * pstTail, * pstCur, * pstNew;
	char acFlight[20];  //保存航班号
	pstHead = pstTail = pstPlaneNodeHead;

	//让pstTail指向最后一个节点
	while (pstTail->pstNext != NULL)
	{
		pstTail = pstTail->pstNext;

	}
	while (1)
	{
		printf("Input the flight number (-1 to end):");
		scanf_s("%s", acFlight, 20);
		getchar();
		if (strcmp(acFlight, "-1") == 0)
		{
			break;
		}
		//航班号唯一
		pstCur = pstPlaneNodeHead->pstNext;

		while (pstCur != NULL)
		{
			if (strcmp(acFlight, pstCur->stDate.acFlight) == 0)
			{
				printf("this flight %s esists!\n", acFlight);
				return;
			}
			pstCur = pstCur->pstNext;
		}
		//如果航班号没有和现有记录航班号重复 ，则重新建一个链表节点
		pstNew = (struct PlaneNode*)malloc(sizeof(struct PlaneNode));
		strcpy_s(pstNew->stDate.acFlight, 20, acFlight);

		printf("Input the Start City:\n");
		scanf_s("%s", pstNew->stDate.acOrigin, 10);
		printf("Input the Dest City:\n");
		scanf_s("%s", pstNew->stDate.acDest, 20);
		printf("Input the Departure time(Format 00:00):\n");
		scanf_s("%s", pstNew->stDate.acTakeOffTime, 10);
		printf("Input the Arrival time(Format 00:00):\n");
		scanf_s("%s", pstNew->stDate.acReverceTime, 10);
		printf("Input the Price of ticket:\n ");
		scanf_s("%f", &pstNew->stDate.fPrice);
		printf("Input the discount(Fromat(0.0):\n");
		scanf_s("%s", pstNew->stDate.acDisscount, 4);
		printf("Input the number of the tickets:\n");
		scanf_s("%d", &pstNew->stDate.iNum);

		pstNew->pstNext = NULL;
		pstTail->pstNext = pstNew;
		pstTail = pstNew;

		//如果有新的航班信息，保存标准置为1，若退出需要提示是否保存信息（见主函数）
		iSave = 1;
	}
}
//查询机票信息
void Search(PPlaneNode pstPlaneNodeHead)
{
	assert(pstPlaneNodeHead != NULL);
	if (pstPlaneNodeHead == NULL)
	{
		return;
	}
	system("cls");
	int iSel = 0;
	int icount = 0;
	PPlaneNode pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	if (pstPlaneNodeCur == NULL)
	{
		printf("No flight record");
		return;
	}
	printf("Choose one way according to:\n 1.flight  2.Dest:\n");
	scanf_s("%d", &iSel);
	if (iSel == 1)
	{
		char acFlight[20];
		printf("请输入要查询的航班号:\n");
		scanf_s("%s", &acFlight, 20);
		getchar();
		//打开订票信息文件
		for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
		{
			if (strcmp(pstPlaneNodeCur->stDate.acFlight, acFlight) == 0)
			{

				PrintHead();
				PrintDate(pstPlaneNodeCur);

				break; //航班号唯一，查到就退出
			}
		}
	}
	else if (iSel == 2)
	{
		char acDest;
		printf("Input the Dest City:\n");
		scanf_s("%s", &acDest, 20);
		PrintHead();
		for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
		{
			if (strcmp(pstPlaneNodeCur->stDate.acDest, &acDest) == 0)
			{


				PrintDate(pstPlaneNodeCur);
				icount++;  //同一个目的地可能有多个数据

			}
		}
		if (icount == 0)  //遍历完一遍，记录数为0，则没有记录：
		{

			printf("Sorry ,no record!\n");
		}
	}
	else
	{
		printf("sorry please input right number1-2");
	}

}
//修改机票信息
void Mod_menu()
{
	puts("**********************************************************************");
	puts("----------------------------------------------------------------------");
	puts("                    choose the follow operation(0-8)                  ");
	puts("--------------------------------------------------------------------- ");
	puts("*******************       1   flights          ********************   ");
	puts("*******************       2   Origin           ********************   ");
	puts("*******************       3   Destination      ********************   ");
	puts("*******************       4   Take off time    ********************   ");
	puts("*******************       5   Reverce time     ********************   ");
	puts("*******************       6   Prices           ********************   ");
	puts("*******************       7   Disscount        ********************   ");
	puts("*******************       8   ticket number    ********************   ");
	puts("*******************       0   quits            ********************   ");
	puts("**********************************************************************");
}
void Modify(PPlaneNode pstPlaneNodeHead)
{
	assert(pstPlaneNodeHead != NULL);
	if (pstPlaneNodeHead == NULL)
	{
		return;
	}
	char acFlight[20];
	PPlaneNode pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	if (pstPlaneNodeCur == NULL)
	{
		printf("No flight to modifty!\n");
		return;
	}
	else
	{
		printf("Input the flight number you want to modify:\n");
		scanf_s("%s", acFlight, 20);
		for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
		{
			if (strcmp(pstPlaneNodeCur->stDate.acFlight, acFlight) == 0)
			{
				break;
			}

		}
		if (pstPlaneNodeCur)
		{
			//子菜单

			int isel = 0;
			system("cls");
			Mod_menu();
			printf("please Input 0-8: ");
			scanf_s("%d", &isel);
			getchar();
			switch (isel)
			{
			case 1:
				printf("Input new flights!\n");
				scanf("%s", pstPlaneNodeCur->stDate.acFlight);
				break;
			case 2:
				printf("Input new Origin!\n");
				scanf("%s", pstPlaneNodeCur->stDate.acOrigin);
				break;
			case 3:
				printf("Input new Destination!\n");
				scanf("%s", pstPlaneNodeCur->stDate.acDest);
				break;
			case 4:
				printf("Input new Take off time!\n");
				scanf("%s", pstPlaneNodeCur->stDate.acTakeOffTime);
				break;
			case 5:
				printf("Input new Reverce time!\n");
				scanf("%s", pstPlaneNodeCur->stDate.acReverceTime);
				break;
			case 6:
				printf("Input new Prices!\n");
				scanf("%f", &pstPlaneNodeCur->stDate.fPrice);
				break;
			case 7:
				printf("Input new Disscount!\n");
				scanf("%s", pstPlaneNodeCur->stDate.acDisscount);
				break;
			case 8:
				printf("Input new ticket number!\n");
				scanf("%d", &pstPlaneNodeCur->stDate.iNum);
				break;
			case 0:
				printf("quit!\n");
				break;
			}
			printf("End Modifying information!\n");
		}
		else
		{
			printf("flights number not exist!\n");
		}

	}

}
//显示机票信息
void Show(PPlaneNode pstPlaneNodeHead)
{
	assert(pstPlaneNodeHead != NULL);
	PPlaneNode pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	PrintHead();
	if (pstPlaneNodeHead->pstNext == NULL)
	{
		printf("no flight ticket!\n");

	}
	else
	{
		while (pstPlaneNodeCur != NULL)
		{
			PrintDate(pstPlaneNodeCur);
			pstPlaneNodeCur = pstPlaneNodeCur->pstNext;
		}
	}
}
//推荐机票信息
struct ManNode* FindMan(PManNode pstManNodeHead, char acId[20])

{
	PManNode pstManNodeCur = pstManNodeHead->pstNext;
	for (pstManNodeCur; pstManNodeCur != NULL; pstManNodeCur = pstManNodeCur->pstNext)
	{
		if (strcmp(pstManNodeCur->stDate.acID, acId) == 0) // 知道到id号相同的订票人的
		{
			return pstManNodeCur;
		}
	}
	return NULL;
}
PPlaneNode FindPlane(PPlaneNode pstPlaneNodeHead, char* acBookFlight)
{
	PPlaneNode pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
	{
		if (strcmp(pstPlaneNodeCur->stDate.acFlight, acBookFlight) == 0) // 知道到id号相同的订票人的
		{
			return pstPlaneNodeCur;
		}
	}
	return NULL;
}
//推荐给用用户合适的机票
//时间 地点
void Recommend(PPlaneNode pstPlaneNodeHead)
{
	PPlaneNode pstPlaneNodeCur;
	char acDest[20];
	char acTime[10];
	int iNum = 0;
	pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	printf("Input your destination");
	scanf_s("%s", acDest, 20);
	printf("Input the earlist time you can take:");
	scanf_s("%s", acTime, 10);
	PrintHead();
	for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
	{
		if (strcmp(pstPlaneNodeCur->stDate.acDest, acDest) == 0)
		{
			if (strcmp(acTime, pstPlaneNodeCur->stDate.acTakeOffTime) < 0)
			{
				PrintDate(pstPlaneNodeCur);
				iNum++;
			}
		}
	}

}
//订票
void Book(PPlaneNode pstPlaneNodeHead, PManNode pstManNodeHead)
{

	//接收订票人头指针
	PPlaneNode pstPlaneNodeCur, astPlaneNode[10];
	PManNode pstManNodeCur, astManNodeTemp = NULL;
	char acDest[20];
	char acId[20];
	char acName[20];
	char acSex[10];
	char acDecision[2];
	char  acFlight[20];
	int iNum = 0;
	int iRecord = 0;
	int k = 0;
	char iFlag = 0;

	pstManNodeCur = pstManNodeHead;
	for (pstManNodeCur; pstManNodeCur->pstNext != NULL; pstManNodeCur = pstManNodeCur->pstNext);

	//将订票人结构体指向尾巴
 //输入目的地
	printf("please Input Dest City:\n");
	scanf_s("%s", &acDest, 20);
	getchar();
	//查找目的地 存入结构体数组中
	pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
	{
		if (strcmp(pstPlaneNodeCur->stDate.acDest, acDest) == 0)
		{
			astPlaneNode[iRecord] = pstPlaneNodeCur;
			iRecord++;
		}

	}
	printf("\n there are %d flight you can choose! \n", iRecord);
	PrintHead();
	for (k = 0; k < iRecord; k++)
	{
		PrintDate(astPlaneNode[k]);

	}
	if (iRecord == 0)
	{
		printf("sorry ,No flights you can book ! \n");

	}
	else
	{
		printf("do you want to book it?(y(Y)/n(N))");
		scanf_s("%s", acDecision, 2);
		getchar();
		if (strcmp(acDecision, "y") == 0 || strcmp(acDecision, "Y") == 0)
		{
			printf("Input your information ! \n");
			astManNodeTemp = (PManNode)malloc(sizeof(ManNode));
			//assert
			printf("Input your Name :\n");
			scanf_s("%s", acName, 20);
			strcpy(astManNodeTemp->stDate.acName, acName);

			printf("Input your Id: \n");
			scanf_s("%s", acId, 20);
			strcpy(astManNodeTemp->stDate.acID, acId);

			printf("Input your sex（M/F) : \n");
			scanf_s("%s", acSex, 10);
			strcpy(astManNodeTemp->stDate.acSex, acSex);

			printf("Input your Flights :\n");
			scanf_s("%s", acFlight, 20);
			strcpy(astManNodeTemp->stDate.acBookFilght, acFlight);

			for (k = 0; k < iRecord; k++)
			{
				if (strcmp(astPlaneNode[k]->stDate.acFlight, acFlight) == 0)
				{
					if (astPlaneNode[k]->stDate.iNum < 1)
					{
						printf("No tickets!");
						return;
					}
					printf("return %d tickets!\n", astPlaneNode[k]->stDate.iNum);
					iFlag = 1;
					break;
				}
			}
			if (iFlag == 0)
			{
				printf("error");
				return;
			}
			printf("Input the book number: \n"); //订购几张票
			scanf_s("%d", &iNum);
			astPlaneNode[k]->stDate.iNum = astPlaneNode[k]->stDate.iNum - iNum;  //还剩下的票数
			astManNodeTemp->stDate.iBookNum = iNum;  //订购票数

			pstManNodeCur->pstNext = astManNodeTemp;  //链接链表
			astManNodeTemp->pstNext = NULL;

			pstManNodeCur = astManNodeTemp;   //移动当前链表指针位置
			printf("Finish Book！\n");
		}
	}
}
//退票
void Refund(PPlaneNode pstPlaneNodeHead, PManNode pstManNodeHead)
{
	PManNode pstManNodeCur, pstManNodeFind = NULL;
	PPlaneNode pstPlaneNodeFind = NULL;
	char acId[20];
	char acDecision[2];
	int iNum = 0; //剩余票数
	int iBookNum;  //
	//找到订票人的结构体
	printf("Input your Id!\n");
	scanf_s("%s", acId, 20);

	pstManNodeFind = FindMan(pstManNodeHead, acId);
	if (pstManNodeFind == NULL)
	{
		printf("can;t find!\n");
	}
	else//退票
	{
		printf("this is your tickets:\n");
		printf("id number:%s\n", pstManNodeFind->stDate.acID);
		printf("nmae:%s\n", pstManNodeFind->stDate.acName);
		printf("sex:%s\n", pstManNodeFind->stDate.acSex);
		printf("book flight:%s\n", pstManNodeFind->stDate.acBookFilght);
		printf("book number:%d\n", pstManNodeFind->stDate.iBookNum);

		printf("do you want to cancel it ?(y/n)");
		scanf_s("%s", acDecision, 2);
		getchar();
		if (strcmp(acDecision, "y") == 0)
		{
			//找到前驱
			for (pstManNodeCur = pstManNodeHead; pstManNodeCur->pstNext != pstManNodeFind; pstManNodeCur = pstManNodeCur->pstNext);
			//找到该名订购人的航班记录
			pstPlaneNodeFind = FindPlane(pstPlaneNodeHead, pstManNodeFind->stDate.acBookFilght);
			//退票
			if (pstPlaneNodeFind != NULL)
			{
				iNum = pstPlaneNodeFind->stDate.iNum;//机票剩余票数
				iBookNum = pstManNodeFind->stDate.iBookNum;  //订购人订购票数
				pstPlaneNodeFind->stDate.iNum = iNum + iBookNum;
			}
			//删除订票人节点
			pstManNodeCur->pstNext = pstManNodeFind->pstNext;
			printf("successful!\n"); //成功退订 

			iSave = 1;
			free(pstManNodeFind);
		}

	}

}
//保存机票信息
void SavePlane(struct PlaneNode* pstPlaneNodeHead)
{
	FILE* pfPlane;  // 机票的文件指针
	struct PlaneNode* pstPlaneNodeCur;
	int count = 0; //保存信息个数
	int iFlag = 1;
	int error = 0;
	//pfPlane = fopen("plane.txt", "wb");
	error = fopen_s(&pfPlane, "plane.txt", "wb");

	if (error != 0)
	{
		printf("the file can't be opened!\n");
		return;
	}

	//写入信息
	pstPlaneNodeCur = pstPlaneNodeHead->pstNext;
	while (pstPlaneNodeCur != NULL)
	{
		if (fwrite(pstPlaneNodeCur, sizeof(struct PlaneNode), 1, pfPlane) == 1)
		{
			pstPlaneNodeCur = pstPlaneNodeCur->pstNext;
			count++;
		}
		else
		{
			iFlag = 0;
			break;
		}
	}

	//提示保存信息数目  ISave置为0
	if (iFlag)
	{
		printf("you have save %d flights\n", &count);
		iSave = 0;
	}
	//关闭文件
	fclose(pfPlane);
}
//保存订票人信息
void SaveMan(struct ManNode* pstManNodeHead)
{
	assert(pstManNodeHead != NULL);
	if (pstManNodeHead == NULL)
	{
		return;
	}
	FILE* pfMan;
	struct ManNode* pstManNodeCur;
	int count = 0;
	int iFlag = 1;
	int error = 0;
	//pfMan = fopen("man.txt", "wb");
	error = fopen_s(&pfMan, "man.txt", "wb");
	if (error != 0)
	{
		printf("the file can't be opened!\n");
	}
	//写入信息
	pstManNodeCur = pstManNodeHead->pstNext;
	while (pstManNodeCur != NULL)
	{
		if (fwrite(pstManNodeCur, sizeof(struct ManNode), 1, pfMan) == 1)
		{
			pstManNodeCur = pstManNodeCur->pstNext;
			count++;
		}
		else
		{
			iFlag = 0;
			break;
		}

		if (iFlag)
		{
			printf("you have save %d man", count);
			iSave = 0;
		}
		fclose(pfMan);

	}
}
//显示当前时间
void NowTime()
{
	time_t curtime;
	curtime = time(NULL);
	printf("现在的时间是：%s", ctime(&curtime));
}
