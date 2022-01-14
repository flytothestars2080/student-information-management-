#include"manage.h"
struct node* phead2;//这个只在回调函数里用
BOOL WINAPI fun(DWORD dwCtrlType)//回调函数处理强制关闭
{
	switch (dwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		saveinflie( phead2);
		phead2 = NULL;
		break;
	}

	return TRUE;
};
void ManageMenuUI(void)
{
	/*system("cls");*/
	SetCursorPosition(0, 0);
	printf("\n\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*         欢 迎 使 用 本 系 统          *\n");
	printf("\t\t\t\t\t*             操作员：                  *\n");
	SetCursorPosition(4, 62);
	printf("%s", User_Message.name);
	SetCursorPosition(5, 0);
	printf("\t\t\t\t\t*             (指令集如下)              *\n");
	printf("\t\t\t\t\t*          0.退出系统                   *\n");
	printf("\t\t\t\t\t*          1.添加一名学生               *\n");
	printf("\t\t\t\t\t*          2.保存数据进文件             *\n");
	printf("\t\t\t\t\t*          3.显示指定学生信息           *\n");
	printf("\t\t\t\t\t*          4.显示所有学生信息           *\n");
	printf("\t\t\t\t\t*          5.修改指定学生信息           *\n");
	printf("\t\t\t\t\t*          6.删除指定学生信息           *\n");
	printf("\t\t\t\t\t*          7.考试                       *\n");
	printf("\t\t\t\t\t*          8.根据成绩顺序查看           *\n");
	printf("\t\t\t\t\t*          9.统计(显示不及格学生)       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*             输入指令：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
}
void Manage(void)
{
	BOOL A =SetConsoleCtrlHandler(fun, TRUE);
	srand((unsigned int)time(NULL));
	struct node empty_head;
	empty_head.count = 0;
	empty_head.Pnext = &empty_head;
	empty_head.Ppre = &empty_head;
	empty_head.stu_message.StuNumber = 0;
	struct StuMessage stu;
	phead2 = &empty_head;
	ReadFormFlie(&empty_head);
	while(1)
	{
	ManageMenuUI();
	int input = -1;
	scanf_s("%d", &input);
	switch (input)
	{
	case 0://退出  可以加个winapi 关闭窗口自动报存
		saveinflie(&empty_head);
		QuitUI();
		FreeList(&empty_head);
		return;
		break;
	case 1://添加
		AddStuUI();
		scanf_s("%s", stu.name,sizeof(stu.name));
		SetCursorPosition(20, 64);
		scanf_s("%u", &stu.date);
		//同名检测
		/*if (IsnameExist(&empty_head, stu.name) == true)
		{
			NameIsExistUI();
			break;
		}*/
		if (add(&empty_head, &stu))
		{
			ProduceStuNumber(&empty_head);
            AddStuSucessUI();
		}
		else
		{
			AddStuFailUI();
		}
		break;
	case 2:
		//保存
		saveinflie(&empty_head);
		SaveInflieSucessUI();
		break;
	case 3://查找指定学生
		LookSpecifyNameUI();
		scanf_s("%s", stu.name, sizeof(stu.name));
		LookSpecifyName(&empty_head, stu);
		break;
	case 4://查看所有学生
		LookAll(&empty_head);
		break;
	case 5: //修改学生成绩
		ChangeUI();
		scanf_s("%s", stu.name,sizeof(stu.name));
		SetCursorPosition(20, 69);
		scanf_s("%u", &stu.date );
		if (ChangeStuMessage(&empty_head, &stu))
		{
			ChangeSuccessUI();
		}
		else
		{
			ChangeFailUI();
		}
		break;
	case 6://删除
		DeleteNameUI();
		scanf_s("%s", stu.name, sizeof(stu.name));
		if (DeleteStubyName(&empty_head, &stu))
		{
               DeleteNameSuccessUI();
		}
		else
		{
			DeleteNameFailUI();
		}
		
		break;
	case 7://考试
		 Test(&empty_head);
		 TestSucessUI();
		break;
	case 8:
		SortByScore2(&empty_head);
		LookAll(&empty_head);
		SortByStuNumber(&empty_head);
		break;
	case 9:
	{
		RangeUI();
		unsigned int iscore1=0, iscore2=0;
		scanf_s("%d", &iscore1);
		SetCursorPosition(19, 76);
		scanf_s("%d", &iscore2);
		LookRangeStu(&empty_head,iscore1, iscore2);
		break;
	}
	default:
	{char t;
	while ((t = getchar()) != '\n' && t != EOF);
	inputFailUI();
	}
		break;
	}

    }
};

void inputFailUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*   指令输入失败，请重新输入!!!         *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void QuitUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*            谢谢使用,再见!             *\n");
	printf("\t\t\t\t\t*         3 秒后自动退出系统            *\n");
	printf("\t\t\t\t\t*****************************************\n");
	 Countdown(20, 50, 1000, 3);
};

void AddStuUI(void) 
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             学生名字：                *\n");
	printf("\t\t\t\t\t*             学生分数：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19,64);

};
void AddStuSucessUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*           学生信息添加成功!           *\n");
	printf("\t\t\t\t\t*****************************************\n");

};
bool add(struct node* phead, struct StuMessage *PstuMessage) //双向循环尾添加
{
	//参数性合法检测
	if (phead == NULL || PstuMessage == NULL)
		return false;
	//创建结点
	struct node* pnew = (struct node*)malloc(sizeof(struct node));
	if (pnew == NULL)
		return false;
	//数据写入
	pnew->stu_message = *PstuMessage;
	pnew->Pnext = NULL;
	pnew->Ppre = NULL;
	//链接
	//先连
	pnew->Pnext=phead;
	pnew->Ppre=phead->Ppre;
	//后断接
	phead->Ppre->Pnext=pnew;
	phead->Ppre=pnew;
	phead->count++;//计数加加
	return true;
};
void ProduceStuNumber(struct node* phead)
{
	if (phead == NULL || phead->count <= 0)
		return;
	//尾结点根据他的前一个结点的学号数进行学号数初始化
	phead->Ppre->stu_message.StuNumber = phead->Ppre->Ppre->stu_message.StuNumber + 1;
};
void FreeList(struct node*phead)
{
	if (phead == NULL||phead->count==0)
		return;
	struct node* pt = phead->Pnext;
	while(pt!=phead)
	{
		struct node* ptemp = pt;
		pt = pt->Pnext;
		free(ptemp);
	}
	//空头重新初始化
	phead->count = 0;
	phead->Pnext = phead;
	phead->Ppre = phead;
	phead->stu_message.StuNumber = 0;
};
void AddStuFailUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*           学生信息添加失败!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
};

void saveinflie(struct node* phead) 
{
	//参数合法性检测
	if (phead == NULL)
		return;
	//打开文件
	FILE* pflie = NULL;
	errno_t nes = fopen_s(&pflie, "stu.date", "w");
	if (nes != 0 || pflie == NULL)
		return;
	//写入文件
	struct node* pt = phead->Pnext;
	while (pt!=phead)
	{
		fwrite(&(pt->stu_message), sizeof(struct StuMessage), 1, pflie);
		pt = pt->Pnext;
	}
	fclose(pflie);
	//关闭文件

};
void SaveInflieSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*           保 存 成 功 ! ! !           *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void ReadFormFlie(struct node* phead)
{
	//参数检测
	if (phead == NULL)
		return;
	//打开文件
	FILE* pflie = NULL;
	errno_t nes = fopen_s(&pflie, "stu.date", "r");
	if (nes != 0 || pflie == NULL)
		return;
	//读取文件
	struct StuMessage stu;
	while (fread(&stu, sizeof(struct StuMessage), 1, pflie) != 0)
	{
		add(phead, &stu);
	}
	//关闭文件
	fclose(pflie);
	
};

bool IsnameExist(struct node* phead, char* pname)
{
	//合法性检测
	if (phead == NULL || pname == NULL)
		return false;
	struct node* pt = phead->Pnext;
	while (pt!=phead)
	{
		if (strcmp(pt->stu_message.name, pname) == 0)
		{
			return true;
		}
		pt = pt->Pnext;
	}
	return false;
}
void NameIsExistUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*           学生已存在!                 *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

void LookAll(struct node* phead)
{
	//参数合法性检测
	if (phead == NULL || phead->count == 0)
		return;
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	//数据标题
	printf("\t\t\t\t\t*        学号      姓名      成绩       *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	struct node* pt = phead->Pnext;
	while (pt!=phead)
	{
		printf("\t\t\t\t\t* |        %2d      %-10s%3d      | *\n",pt->stu_message.StuNumber,pt->stu_message.name,pt->stu_message.date);
		pt = pt->Pnext;
	}
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	//数据结尾
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
    printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void LookSpecifyName(struct node* phead, struct StuMessage stu)
{

	//参数合法性检测
	if (phead == NULL || phead->count == 0)
		return;
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             搜索名字:%-10s       *\n",stu.name);
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(21, 0);
	//数据标题
	printf("\t\t\t\t\t*        学号      姓名      成绩       *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	struct node* pt = phead->Pnext;
	while (pt != phead)
	{
		if(strcmp(pt->stu_message.name,stu.name)==0)
		printf("\t\t\t\t\t* |        %2d      %-10s%3d      | *\n", pt->stu_message.StuNumber, pt->stu_message.name, pt->stu_message.date);
		pt = pt->Pnext;
	}
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	//数据结尾
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);

};
void LookSpecifyNameUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             搜索名字：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
}

void RangeUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*           输入分数范围：       到     *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 69);

};
void LookRangeStu(struct node* phead, unsigned iScore1, unsigned iScore2)
{
	if (phead == NULL || phead->count == 0)
		return;
	unsigned int min;
	unsigned int max;
	if (iScore1 >= iScore2)
	{
		min = iScore2;
		max = iScore1;
	}
	else
	{
		min = iScore1;
		max = iScore2;
	}
	
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	//数据标题
	printf("\t\t\t\t\t*        学号      姓名      成绩       *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	struct node* pt = phead->Pnext;
	while (pt != phead)
	{
		if (pt->stu_message.date>=min&&pt->stu_message.date<=max)
			printf("\t\t\t\t\t* |        %2d      %-10s%3d      | *\n", pt->stu_message.StuNumber, pt->stu_message.name, pt->stu_message.date);
		pt = pt->Pnext;
	}
	//数据结尾
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
}

void DeleteNameUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             删除名字：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
};
void DeleteNameSuccessUI(void)
{
	SetCursorPosition(21, 0);
	printf("\t\t\t\t\t*             删除成功：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
}
void DeleteNameFailUI(void)
{
	SetCursorPosition(21, 0);
	printf("\t\t\t\t\t*             删除失败：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
}
bool DeleteStubyName(struct node* phead, struct StuMessage* pstu)
{
	if (phead == NULL || pstu == NULL || phead->count <= 0)
		return false;
	struct node* pt = phead->Pnext;
	unsigned icount = phead->count;
	while (pt != phead)
	{
		if (strcmp(pt->stu_message.name, pstu->name) == 0)//删除
		{
			struct node* ptemp = pt->Ppre;//标记要删除的前一个结点
			pt->Ppre->Pnext=pt->Pnext;//前一个结点的pnext指针指向pt的后一个结点
			pt->Pnext->Ppre=pt->Ppre;//后一个结点的ppre指针指向pt的前一个结点
			free(pt);
			pt = ptemp;
			phead->count--;
		}
		pt = pt->Pnext;
	}
	if (icount == phead->count)
		return false;
	else
		return true;
}

void ProduceNewStuNumber(struct node* phead)
{
	if (phead == NULL || phead->count <= 0)
		return;
	struct node* pt = phead->Pnext;
	unsigned int icount = 0;
	while (pt != phead)
	{
		icount++;
		pt->stu_message.StuNumber = icount;
		pt = pt->Pnext;
	}
}

void ChangeUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*          要修改的学生名字：           *\n");
	printf("\t\t\t\t\t*          要修改的学生分数：           *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 69);
}
void ChangeSuccessUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*             修改成功：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
}
void ChangeFailUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*             修改失败：                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
}
bool ChangeStuMessage(struct node* phead, struct StuMessage* pstu)
{
	if (phead == NULL || pstu == NULL || phead->count <= 0)
		return false;
	struct node* pt = phead->Pnext;
	while (pt != phead)
	{
		if (strcmp(pt->stu_message.name, pstu->name) == 0)//修改
		{
			pt->stu_message.date = pstu->date;
			return true;
		}
		pt = pt->Pnext;
	}
	
	return false;
}

void TestSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             考试完成!                 *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void Test(struct node* phead)
{
	if (phead == NULL || phead->count <= 0)
		return;
	struct node* pt = phead->Pnext;
	while (pt != phead)
	{
		pt->stu_message.date = rand() % 71 + 30;//生成30~100的随机数
		pt = pt->Pnext;
	}
	return ;
	
}

void SortByScore(struct node* phead) //冒泡算法
{
	if (phead == NULL||phead->count<=0)
		return;

	for (unsigned i = 0; i < phead->count - 1; i++)
	{
		struct node* ptemp = phead->Pnext;
		while (ptemp->Pnext!=phead)
		{
			if (ptemp->stu_message.date < ptemp->Pnext->stu_message.date)
			{   
				//交换
				struct StuMessage temp= ptemp->stu_message;
				ptemp->stu_message = ptemp->Pnext->stu_message;
				ptemp->Pnext->stu_message = temp;

			}
			ptemp = ptemp->Pnext;
		}
	}

}
void SortByStuNumber(struct node* phead)
{
	if (phead == NULL || phead->count <= 0)
		return;

	for (unsigned i = 0; i < phead->count - 1; i++)
	{
		struct node* ptemp = phead->Pnext;
		while (ptemp->Pnext != phead)
		{
			if (ptemp->stu_message.StuNumber > ptemp->Pnext->stu_message.StuNumber)
			{
				//交换
				struct StuMessage temp = ptemp->stu_message;
				ptemp->stu_message = ptemp->Pnext->stu_message;
				ptemp->Pnext->stu_message = temp;

			}
			ptemp = ptemp->Pnext;
		}
	}

}
void SortByScore2(struct node* phead)//选择排序
{
	if (phead == NULL || phead->count <= 0)
		return;
	struct node* pt = NULL;//循环指针
	struct node* pmax = NULL;
	struct node* pstart = NULL;
	struct StuMessage  temp;

	pt = phead->Pnext;

	for (unsigned i = 0; i < phead->count - 1; i++)
	{
		for (unsigned int j = 0; j < i; j++)
		{
			pt = pt->Pnext;
		}
		pmax = pt;//假设开始的位置最小
		pstart = pt;//标记开始的位置
		for (unsigned int j = 0; j < phead->count - i; j++)//  选择排序找最小的
		{
			if (pmax->stu_message.date < pt->stu_message.date)
			{
				pmax = pt;
			}
			pt = pt->Pnext;
		}
		//和开始的位置交换结点
		temp = pstart->stu_message;
		pstart->stu_message = pmax->stu_message;
		pmax->stu_message = temp;
	}

}//