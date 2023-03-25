#define _CRT_SECURE_NO_WARNINGS 1
#include"struct_file.h"

//作为数据改动的标志
int iSave = 0;


int main()
{
	struct PlaneNode pstPlaneNodeHead;  //机票信息头结点
	pstPlaneNodeHead.pstNext = NULL;
	struct ManNode pstManNodeHead;    //购票信息头结点
	pstManNodeHead.pstNext = NULL;

	Init(&pstPlaneNodeHead, &pstManNodeHead);  // 将文件的数据加载到内存中

	int iSel = 0; //用于接收用户对功能的选择


	char c1;
	while (1)
	{
		system("cls");
		Menu();
		printf("Input 0-9 operations:");
		scanf_s("%d", &iSel);
		getchar();
		switch (iSel)
		{
		case 1:
			printf("进入添加机票页面\n");
			Insert(&pstPlaneNodeHead); // 添加机票信息
			break;
		case 2:
			Search(&pstPlaneNodeHead);   //查询机票信息
			break;
		case 3:
			Book(&pstPlaneNodeHead, &pstManNodeHead);//订票
			break;
		case 4:
			Modify(&pstPlaneNodeHead);    //修改机票信息
			break;
		case 5:
			Show(&pstPlaneNodeHead);   //显示机票信息  
			break;
		case 6:
			Recommend(&pstPlaneNodeHead);  //推荐机票信息
			break;
		case 7:
			Refund(&pstPlaneNodeHead, &pstManNodeHead);//退票信息
			break;
		case 8:
			NowTime();//显示当前时间
			break;
		case 9:
			SaveMan(&pstManNodeHead);     //数据保存
			SavePlane(&pstPlaneNodeHead);
			break;
		case 0:
			if (iSave == 1)
			{
				printf("do you want to save (y/n)");
				scanf("%c", &c1);
				getchar();
				if (c1 == 'y' || c1 == 'Y')
				{
					SaveMan(&pstManNodeHead);     //保存订票人的信息
					SavePlane(&pstPlaneNodeHead);    // 保存机票信息

				}
			}
			Destroy(&pstPlaneNodeHead, &pstManNodeHead);
			return 0;
		}
		printf("\nplease press any key to continue...\n");
		_getch();
	}
	Destroy(&pstPlaneNodeHead, &pstManNodeHead);
	return 0;
}
