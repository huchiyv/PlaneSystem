#define _CRT_SECURE_NO_WARNINGS 1
#include"struct_file.h"

//��Ϊ���ݸĶ��ı�־
int iSave = 0;


int main()
{
	struct PlaneNode pstPlaneNodeHead;  //��Ʊ��Ϣͷ���
	pstPlaneNodeHead.pstNext = NULL;
	struct ManNode pstManNodeHead;    //��Ʊ��Ϣͷ���
	pstManNodeHead.pstNext = NULL;

	Init(&pstPlaneNodeHead, &pstManNodeHead);  // ���ļ������ݼ��ص��ڴ���

	int iSel = 0; //���ڽ����û��Թ��ܵ�ѡ��


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
			printf("������ӻ�Ʊҳ��\n");
			Insert(&pstPlaneNodeHead); // ��ӻ�Ʊ��Ϣ
			break;
		case 2:
			Search(&pstPlaneNodeHead);   //��ѯ��Ʊ��Ϣ
			break;
		case 3:
			Book(&pstPlaneNodeHead, &pstManNodeHead);//��Ʊ
			break;
		case 4:
			Modify(&pstPlaneNodeHead);    //�޸Ļ�Ʊ��Ϣ
			break;
		case 5:
			Show(&pstPlaneNodeHead);   //��ʾ��Ʊ��Ϣ  
			break;
		case 6:
			Recommend(&pstPlaneNodeHead);  //�Ƽ���Ʊ��Ϣ
			break;
		case 7:
			Refund(&pstPlaneNodeHead, &pstManNodeHead);//��Ʊ��Ϣ
			break;
		case 8:
			NowTime();//��ʾ��ǰʱ��
			break;
		case 9:
			SaveMan(&pstManNodeHead);     //���ݱ���
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
					SaveMan(&pstManNodeHead);     //���涩Ʊ�˵���Ϣ
					SavePlane(&pstPlaneNodeHead);    // �����Ʊ��Ϣ

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
