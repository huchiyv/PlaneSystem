#define _CRT_SECURE_NO_WARNINGS 1
#include"struct_file.h"
extern int iSave;
//���˵�
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
//��ӡ����
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
//���ٺ���  ��ֹ�ڴ�й©
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
// ��ʼ��
int Init(struct PlaneNode* pstPlaneNodeHead, struct ManNode* pstManNodeHead)
{
	//�ȼ��طɻ���Ʊ��Ϣ
	FILE* pfPlane; //����ɻ���Ʊ��Ϣ�ļ�ָ��
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
		//���ļ����ݶ��뵽������
		while (!feof(pfPlane)) //�����ļ����һ������
		{
			pstPlaneNodeTemp = (struct PlaneNode*)malloc(sizeof(struct PlaneNode));
			if (fread(pstPlaneNodeTemp, sizeof(struct PlaneNode), 1, pfPlane) != 0)
			{
				pstPlaneNodeTemp->pstNext = NULL;
				pstPlaneNodeCur->pstNext = pstPlaneNodeTemp;
				pstPlaneNodeCur = pstPlaneNodeTemp;
			}
		}
		free(pstPlaneNodeTemp);  //��ʱ���ͷŵ����ļ���������һ�������ָ��
		fclose(pfPlane);
	}
	//���ض�Ʊ����Ϣ
	FILE* pfMan;  // ���嶩Ʊ����Ϣ�ļ�ָ��
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
//��ӻ�Ʊ
void Insert(struct PlaneNode* pstPlaneNodeHead)
{
	assert(pstPlaneNodeHead != NULL);
	if (pstPlaneNodeHead == NULL)
	{
		return;
	}
	struct PlaneNode* pstNode, * pstHead, * pstTail, * pstCur, * pstNew;
	char acFlight[20];  //���溽���
	pstHead = pstTail = pstPlaneNodeHead;

	//��pstTailָ�����һ���ڵ�
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
		//�����Ψһ
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
		//��������û�к����м�¼������ظ� �������½�һ������ڵ�
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

		//������µĺ�����Ϣ�������׼��Ϊ1�����˳���Ҫ��ʾ�Ƿ񱣴���Ϣ������������
		iSave = 1;
	}
}
//��ѯ��Ʊ��Ϣ
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
		printf("������Ҫ��ѯ�ĺ����:\n");
		scanf_s("%s", &acFlight, 20);
		getchar();
		//�򿪶�Ʊ��Ϣ�ļ�
		for (pstPlaneNodeCur; pstPlaneNodeCur != NULL; pstPlaneNodeCur = pstPlaneNodeCur->pstNext)
		{
			if (strcmp(pstPlaneNodeCur->stDate.acFlight, acFlight) == 0)
			{

				PrintHead();
				PrintDate(pstPlaneNodeCur);

				break; //�����Ψһ���鵽���˳�
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
				icount++;  //ͬһ��Ŀ�ĵؿ����ж������

			}
		}
		if (icount == 0)  //������һ�飬��¼��Ϊ0����û�м�¼��
		{

			printf("Sorry ,no record!\n");
		}
	}
	else
	{
		printf("sorry please input right number1-2");
	}

}
//�޸Ļ�Ʊ��Ϣ
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
			//�Ӳ˵�

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
//��ʾ��Ʊ��Ϣ
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
//�Ƽ���Ʊ��Ϣ
struct ManNode* FindMan(PManNode pstManNodeHead, char acId[20])

{
	PManNode pstManNodeCur = pstManNodeHead->pstNext;
	for (pstManNodeCur; pstManNodeCur != NULL; pstManNodeCur = pstManNodeCur->pstNext)
	{
		if (strcmp(pstManNodeCur->stDate.acID, acId) == 0) // ֪����id����ͬ�Ķ�Ʊ�˵�
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
		if (strcmp(pstPlaneNodeCur->stDate.acFlight, acBookFlight) == 0) // ֪����id����ͬ�Ķ�Ʊ�˵�
		{
			return pstPlaneNodeCur;
		}
	}
	return NULL;
}
//�Ƽ������û����ʵĻ�Ʊ
//ʱ�� �ص�
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
//��Ʊ
void Book(PPlaneNode pstPlaneNodeHead, PManNode pstManNodeHead)
{

	//���ն�Ʊ��ͷָ��
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

	//����Ʊ�˽ṹ��ָ��β��
 //����Ŀ�ĵ�
	printf("please Input Dest City:\n");
	scanf_s("%s", &acDest, 20);
	getchar();
	//����Ŀ�ĵ� ����ṹ��������
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

			printf("Input your sex��M/F) : \n");
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
			printf("Input the book number: \n"); //��������Ʊ
			scanf_s("%d", &iNum);
			astPlaneNode[k]->stDate.iNum = astPlaneNode[k]->stDate.iNum - iNum;  //��ʣ�µ�Ʊ��
			astManNodeTemp->stDate.iBookNum = iNum;  //����Ʊ��

			pstManNodeCur->pstNext = astManNodeTemp;  //��������
			astManNodeTemp->pstNext = NULL;

			pstManNodeCur = astManNodeTemp;   //�ƶ���ǰ����ָ��λ��
			printf("Finish Book��\n");
		}
	}
}
//��Ʊ
void Refund(PPlaneNode pstPlaneNodeHead, PManNode pstManNodeHead)
{
	PManNode pstManNodeCur, pstManNodeFind = NULL;
	PPlaneNode pstPlaneNodeFind = NULL;
	char acId[20];
	char acDecision[2];
	int iNum = 0; //ʣ��Ʊ��
	int iBookNum;  //
	//�ҵ���Ʊ�˵Ľṹ��
	printf("Input your Id!\n");
	scanf_s("%s", acId, 20);

	pstManNodeFind = FindMan(pstManNodeHead, acId);
	if (pstManNodeFind == NULL)
	{
		printf("can;t find!\n");
	}
	else//��Ʊ
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
			//�ҵ�ǰ��
			for (pstManNodeCur = pstManNodeHead; pstManNodeCur->pstNext != pstManNodeFind; pstManNodeCur = pstManNodeCur->pstNext);
			//�ҵ����������˵ĺ����¼
			pstPlaneNodeFind = FindPlane(pstPlaneNodeHead, pstManNodeFind->stDate.acBookFilght);
			//��Ʊ
			if (pstPlaneNodeFind != NULL)
			{
				iNum = pstPlaneNodeFind->stDate.iNum;//��Ʊʣ��Ʊ��
				iBookNum = pstManNodeFind->stDate.iBookNum;  //�����˶���Ʊ��
				pstPlaneNodeFind->stDate.iNum = iNum + iBookNum;
			}
			//ɾ����Ʊ�˽ڵ�
			pstManNodeCur->pstNext = pstManNodeFind->pstNext;
			printf("successful!\n"); //�ɹ��˶� 

			iSave = 1;
			free(pstManNodeFind);
		}

	}

}
//�����Ʊ��Ϣ
void SavePlane(struct PlaneNode* pstPlaneNodeHead)
{
	FILE* pfPlane;  // ��Ʊ���ļ�ָ��
	struct PlaneNode* pstPlaneNodeCur;
	int count = 0; //������Ϣ����
	int iFlag = 1;
	int error = 0;
	//pfPlane = fopen("plane.txt", "wb");
	error = fopen_s(&pfPlane, "plane.txt", "wb");

	if (error != 0)
	{
		printf("the file can't be opened!\n");
		return;
	}

	//д����Ϣ
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

	//��ʾ������Ϣ��Ŀ  ISave��Ϊ0
	if (iFlag)
	{
		printf("you have save %d flights\n", &count);
		iSave = 0;
	}
	//�ر��ļ�
	fclose(pfPlane);
}
//���涩Ʊ����Ϣ
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
	//д����Ϣ
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
//��ʾ��ǰʱ��
void NowTime()
{
	time_t curtime;
	curtime = time(NULL);
	printf("���ڵ�ʱ���ǣ�%s", ctime(&curtime));
}
