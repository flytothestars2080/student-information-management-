#include"login.h"
struct User User_Message = { "游客" };
bool login(void)
{
	
	while (1)
	{
		LoginMenuUI();//界面显示
		int input = -1;
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
		{
			LoginUI(); //登录
			scanf_s("%s", User_Message.name, sizeof(User_Message.name));
			SetCursorPosition(12, 60);
			scanf_s("%s", User_Message.key, sizeof(User_Message.key));
			if (Isright(&User_Message))
			{
				LoginSucessUI();//密码正确
				return true;
			}
			else
			{
				LoginFailUI();
				//密码错误
			}
		}
			  break;
		case 2://注册
		{
			RegisterUI();
			scanf_s("%s", User_Message.name, sizeof(User_Message.name));
			SetCursorPosition(12, 60);
			scanf_s("%s", User_Message.key, sizeof(User_Message.key));
			if (true == IsUserExit(&User_Message))
			{
				RegisterFailUI();
			}	//注册失败
			else
			{
				//注册成功
				RegisterSucessUI();
				Saveusr(&User_Message);
				return true;//1.
			};
			
		}
			break;
		case 3:
		{
			//游客登录
			VisterLoginUI();
			return true;
		}
			break;
		case 4:
		{
			//退出
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
void LoginUI(void)//登录界面
{
	SetCursorPosition(11, 0);
	printf("\t\t\t\t\t*          登录名 :                *\n");
	printf("\t\t\t\t\t*        登录密码 :                *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(11, 60);
};
void LoginMenuUI(void) 
{
	SetCursorPosition(2, 0);//设置光标位置
	printf("\t\t\t\t\t************************************\n");//\t vs下八个空格
	printf("\t\t\t\t\t*          欢迎使用本系统          *\n");
	printf("\t\t\t\t\t*   (相关操作请直接输入对应指令)   *\n");
	printf("\t\t\t\t\t*           1: 用户登录            *\n");
	printf("\t\t\t\t\t*           2: 账号注册            *\n");
	printf("\t\t\t\t\t*           3: 游客登录            *\n");
	printf("\t\t\t\t\t*           4: 退出系统            *\n");
	printf("\t\t\t\t\t*     请输入指令(1/2/3/4):         *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 66);
};
void SetCursorPosition(short y, short x)
{
	COORD CP = { x,y };
	//win32API，头文件是windows.h，设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CP);
}
void LoginFailUI(void)//登入失败界面
{
	SetCursorPosition(14, 0);
	printf("\t\t\t\t\t*   登录失败，请重新输入指令!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 66);
}
void LoginSucessUI(void)
{
	SetCursorPosition(14, 0);//登入成功界面
	printf("\t\t\t\t\t*      登录成功，3 秒后跳转!!!     *\n");
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
	SetCursorPosition(11, 0); //第10行位置开始输出
	printf("\t\t\t\t\t*          注册名 :                *\n");
	printf("\t\t\t\t\t*        注册密码 :                *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(11, 60);//跳到登录名后面准备输入登录名
}
void RegisterFailUI()
{
	SetCursorPosition(14, 0);
	printf("\t\t\t\t\t*   注册失败，请重新输入指令!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 67);//光标跳到执行输入位置
}
void RegisterSucessUI()
{
	SetCursorPosition(14, 0);
	printf("\t\t\t\t\t*    注册成功，3 秒后直接登陆!!!   *\n");
	printf("\t\t\t\t\t************************************\n");
	Countdown(14, 55, 1000, 3);
	//实现3 2 1读秒
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
	//打开文件
	errno_t flag=fopen_s(&pfile, "user1.date", "a");
	if (flag!= 0||pfile==NULL)
		return;
	//写入文件
	fwrite(puser, sizeof(struct User), 1, pfile);//
	//关闭文件
	fclose(pfile);
}
bool Isright(struct User*Puser)
{
	if (Puser == NULL)
		return false;
	FILE* pfile = NULL;
	//打开文件
	errno_t flag = fopen_s(&pfile, "user1.date", "r");
	if (flag != 0||pfile == NULL)
		return false;
	//读取文件
	while (!feof(pfile))//到了结尾feof返回真
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
	//打开文件
	errno_t flag = fopen_s(&pfile, "user1.date", "r");
	if (flag != 0 || pfile == NULL)
		return false;
	//读取文件
	while (!feof(pfile))//到了结尾feof返回真
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
void VisterLoginUI(void)//游客界面
{
	//清空控制台，冲新输入菜单
	system("cls");
	LoginMenuUI();
	SetCursorPosition(11, 0);
	printf("\t\t\t\t\t*     3 秒后将以游客身份登陆!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	//实现3 2 1读秒
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
void QuitLoginUI()//退出
{
	system("cls");
	LoginMenuUI();
	SetCursorPosition(11, 0);   //第11行位置开始输出
	printf("\t\t\t\t\t*      退出系统，3 秒后跳转!!!     *\n");
	printf("\t\t\t\t\t************************************\n");
	//实现3 2 1读秒
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
	//清空控制台，冲新输入菜单
	system("cls");
	LoginMenuUI();
	SetCursorPosition(11, 0);   //第10行位置开始输出
	printf("\t\t\t\t\t*   指令输入失败，请重新输入!!!    *\n");
	printf("\t\t\t\t\t************************************\n");
	SetCursorPosition(9, 67); //光标跳到执行输入位置
}