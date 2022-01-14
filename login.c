#include"login.h"
struct User User_Message = { "�ο�" };
bool login(void)
{
	
	while (1)
	{
		LoginMenuUI();//������ʾ
		int input = -1;
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
		{
			LoginUI(); //��¼
			scanf_s("%s", User_Message.name, sizeof(User_Message.name));
			SetCursorPosition(12, 60);
			scanf_s("%s", User_Message.key, sizeof(User_Message.key));
			if (Isright(&User_Message))
			{
				LoginSucessUI();//������ȷ
				return true;
			}
			else
			{
				LoginFailUI();
				//�������
			}
		}
			  break;
		case 2://ע��
		{
			RegisterUI();
			scanf_s("%s", User_Message.name, sizeof(User_Message.name));
			SetCursorPosition(12, 60);
			scanf_s("%s", User_Message.key, sizeof(User_Message.key));
			if (true == IsUserExit(&User_Message))
			{
				RegisterFailUI();
			}	//ע��ʧ��
			else
			{
				//ע��ɹ�
				RegisterSucessUI();
				Saveusr(&User_Message);
				return true;//1.
			};
			
		}
			break;
		case 3:
		{
			//�ο͵�¼
			VisterLoginUI();
			return true;
		}
			break;
		case 4:
		{
			//�˳�
			QuitLoginUI();
			return false;
		}
			break;
		default:
		{
			char t;
			while ((t = getchar()) != '\n' && t != EOF);
			OrderFailUI();
		}
		break;

		}
	}
	return false;
}
void LoginUI(void)//��¼����
{
	SetCursorPosition(11, 0);
	printf("\t\t\t\t\t*          ��¼�� :                *\n");
	printf("\t\t\t\t\t*        ��¼���� :                *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(11, 60);
};
void LoginMenuUI(void) 
{
	SetCursorPosition(2, 0);//���ù��λ��
	printf("\t\t\t\t\t************************************\n");//\t vs�°˸��ո�
	printf("\t\t\t\t\t*          ��ӭʹ�ñ�ϵͳ          *\n");
	printf("\t\t\t\t\t*   (��ز�����ֱ�������Ӧָ��)   *\n");
	printf("\t\t\t\t\t*           1: �û���¼            *\n");
	printf("\t\t\t\t\t*           2: �˺�ע��            *\n");
	printf("\t\t\t\t\t*           3: �ο͵�¼            *\n");
	printf("\t\t\t\t\t*           4: �˳�ϵͳ            *\n");
	printf("\t\t\t\t\t*     ������ָ��(1/2/3/4):         *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 66);
};
void SetCursorPosition(short y, short x)
{
	COORD CP = { x,y };
	//win32API��ͷ�ļ���windows.h�����ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CP);
}
void LoginFailUI(void)//����ʧ�ܽ���
{
	SetCursorPosition(14, 0);
	printf("\t\t\t\t\t*   ��¼ʧ�ܣ�����������ָ��!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 66);
}
void LoginSucessUI(void)
{
	SetCursorPosition(14, 0);//����ɹ�����
	printf("\t\t\t\t\t*      ��¼�ɹ���3 �����ת!!!     *\n");
	printf("\t\t\t\t\t************************************\n");
	Countdown(14, 56, 1000, 3);
	/*Sleep(1000);
	SetCursorPosition(14, 57);
	putchar('2');
	SetCursorPosition(14, 70);
	Sleep(1000);
	SetCursorPosition(14, 57);
	putchar('1');
	SetCursorPosition(14, 70);
	Sleep(1000);
	SetCursorPosition(14, 57);
	putchar('0');
	SetCursorPosition(14, 70);*/
}
void RegisterUI()
{
	SetCursorPosition(11, 0); //��10��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*          ע���� :                *\n");
	printf("\t\t\t\t\t*        ע������ :                *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(11, 60);//������¼������׼�������¼��
}
void RegisterFailUI()
{
	SetCursorPosition(14, 0);
	printf("\t\t\t\t\t*   ע��ʧ�ܣ�����������ָ��!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 67);//�������ִ������λ��
}
void RegisterSucessUI()
{
	SetCursorPosition(14, 0);
	printf("\t\t\t\t\t*    ע��ɹ���3 ���ֱ�ӵ�½!!!   *\n");
	printf("\t\t\t\t\t************************************\n");
	Countdown(14, 55, 1000, 3);
	//ʵ��3 2 1����
	/*Sleep(1000);
	SetCursorPosition(14, 55);
	putchar('2');
	Sleep(1000);
	SetCursorPosition(14, 55);
	putchar('1');
	Sleep(1000);
	SetCursorPosition(14, 55);
	putchar('0');
	Sleep(1000);*/
}
void Countdown(short y, short x, int time, int  start)
{
	for (int i = 1; i <= start ; i++)
	{
		Sleep(time);
		SetCursorPosition(y, x);
		printf("% d", start - i);
		SetCursorPosition(y, x+18);
	}
	Sleep(time);
}
void Saveusr(struct User* puser)
{
	if (puser == NULL)
		return;
	FILE* pfile=NULL;
	//���ļ�
	errno_t flag=fopen_s(&pfile, "user1.date", "a");
	if (flag!= 0||pfile==NULL)
		return;
	//д���ļ�
	fwrite(puser, sizeof(struct User), 1, pfile);//
	//�ر��ļ�
	fclose(pfile);
}
bool Isright(struct User*Puser)
{
	if (Puser == NULL)
		return false;
	FILE* pfile = NULL;
	//���ļ�
	errno_t flag = fopen_s(&pfile, "user1.date", "r");
	if (flag != 0||pfile == NULL)
		return false;
	//��ȡ�ļ�
	while (!feof(pfile))//���˽�βfeof������
	{
		struct User temp = {0};
		fread(&temp, sizeof(struct User), 1, pfile);
		if (strcmp(Puser->name, temp.name) == 0 && strcmp(Puser->key, temp.key) == 0)
		{
			return true;
		}
	}
	fclose(pfile);
	return false;


}
bool IsUserExit(struct User* Puser)
{
	if (Puser == NULL)
		return false;
	FILE* pfile = NULL;
	//���ļ�
	errno_t flag = fopen_s(&pfile, "user1.date", "r");
	if (flag != 0 || pfile == NULL)
		return false;
	//��ȡ�ļ�
	while (!feof(pfile))//���˽�βfeof������
	{
		struct User temp = { 0 };
		fread(&temp, sizeof(struct User), 1, pfile);
		if (strcmp(Puser->name, temp.name) == 0 )
		{
			return true;
		}
	}
	fclose(pfile);
	return false;

}
void VisterLoginUI(void)//�οͽ���
{
	//��տ���̨����������˵�
	system("cls");
	LoginMenuUI();
	SetCursorPosition(11, 0);
	printf("\t\t\t\t\t*     3 ������ο���ݵ�½!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	//ʵ��3 2 1����
	Sleep(1000);
	SetCursorPosition(11, 46);
	putchar('2');
	Sleep(1000);
	SetCursorPosition(11, 46);
	putchar('1');
	Sleep(1000);
	SetCursorPosition(11, 46);
	putchar('0');
	Sleep(1000);
}
void QuitLoginUI()//�˳�
{
	system("cls");
	LoginMenuUI();
	SetCursorPosition(11, 0);   //��11��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*      �˳�ϵͳ��3 �����ת!!!     *\n");
	printf("\t\t\t\t\t************************************\n");
	//ʵ��3 2 1����
	Sleep(1000);
	SetCursorPosition(11, 57);
	putchar('2');
	Sleep(1000);
	SetCursorPosition(11, 57);
	putchar('1');
	Sleep(1000);
	SetCursorPosition(11, 57);
	putchar('0');
	Sleep(1000);
}
void OrderFailUI(void)
{
	//��տ���̨����������˵�
	system("cls");
	LoginMenuUI();
	SetCursorPosition(11, 0);   //��10��λ�ÿ�ʼ���
	printf("\t\t\t\t\t*   ָ������ʧ�ܣ�����������!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 67); //�������ִ������λ��
}