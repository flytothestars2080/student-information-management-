#include"manage.h"
struct node* phead2;//���ֻ�ڻص���������
BOOL WINAPI fun(DWORD dwCtrlType)//�ص���������ǿ�ƹر�
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
	printf("\t\t\t\t\t*         �� ӭ ʹ �� �� ϵ ͳ          *\n");
	printf("\t\t\t\t\t*             ����Ա��                  *\n");
	SetCursorPosition(4, 62);
	printf("%s", User_Message.name);
	SetCursorPosition(5, 0);
	printf("\t\t\t\t\t*             (ָ�����)              *\n");
	printf("\t\t\t\t\t*          0.�˳�ϵͳ                   *\n");
	printf("\t\t\t\t\t*          1.���һ��ѧ��               *\n");
	printf("\t\t\t\t\t*          2.�������ݽ��ļ�             *\n");
	printf("\t\t\t\t\t*          3.��ʾָ��ѧ����Ϣ           *\n");
	printf("\t\t\t\t\t*          4.��ʾ����ѧ����Ϣ           *\n");
	printf("\t\t\t\t\t*          5.�޸�ָ��ѧ����Ϣ           *\n");
	printf("\t\t\t\t\t*          6.ɾ��ָ��ѧ����Ϣ           *\n");
	printf("\t\t\t\t\t*          7.����                       *\n");
	printf("\t\t\t\t\t*          8.���ݳɼ�˳��鿴           *\n");
	printf("\t\t\t\t\t*          9.ͳ��(��ʾ������ѧ��)       *\n");
	printf("\t\t\t\t\t*****************************************\n");
	printf("\t\t\t\t\t*             ����ָ�                *\n");
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
	case 0://�˳�  ���ԼӸ�winapi �رմ����Զ�����
		saveinflie(&empty_head);
		QuitUI();
		FreeList(&empty_head);
		return;
		break;
	case 1://���
		AddStuUI();
		scanf_s("%s", stu.name,sizeof(stu.name));
		SetCursorPosition(20, 64);
		scanf_s("%u", &stu.date);
		//ͬ�����
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
		//����
		saveinflie(&empty_head);
		SaveInflieSucessUI();
		break;
	case 3://����ָ��ѧ��
		LookSpecifyNameUI();
		scanf_s("%s", stu.name, sizeof(stu.name));
		LookSpecifyName(&empty_head, stu);
		break;
	case 4://�鿴����ѧ��
		LookAll(&empty_head);
		break;
	case 5: //�޸�ѧ���ɼ�
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
	case 6://ɾ��
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
	case 7://����
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
	printf("\t\t\t\t\t*   ָ������ʧ�ܣ�����������!!!         *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void QuitUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*            ллʹ��,�ټ�!             *\n");
	printf("\t\t\t\t\t*         3 ����Զ��˳�ϵͳ            *\n");
	printf("\t\t\t\t\t*****************************************\n");
	 Countdown(20, 50, 1000, 3);
};

void AddStuUI(void) 
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             ѧ�����֣�                *\n");
	printf("\t\t\t\t\t*             ѧ��������                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19,64);

};
void AddStuSucessUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*           ѧ����Ϣ��ӳɹ�!           *\n");
	printf("\t\t\t\t\t*****************************************\n");

};
bool add(struct node* phead, struct StuMessage *PstuMessage) //˫��ѭ��β���
{
	//�����ԺϷ����
	if (phead == NULL || PstuMessage == NULL)
		return false;
	//�������
	struct node* pnew = (struct node*)malloc(sizeof(struct node));
	if (pnew == NULL)
		return false;
	//����д��
	pnew->stu_message = *PstuMessage;
	pnew->Pnext = NULL;
	pnew->Ppre = NULL;
	//����
	//����
	pnew->Pnext=phead;
	pnew->Ppre=phead->Ppre;
	//��Ͻ�
	phead->Ppre->Pnext=pnew;
	phead->Ppre=pnew;
	phead->count++;//�����Ӽ�
	return true;
};
void ProduceStuNumber(struct node* phead)
{
	if (phead == NULL || phead->count <= 0)
		return;
	//β����������ǰһ������ѧ��������ѧ������ʼ��
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
	//��ͷ���³�ʼ��
	phead->count = 0;
	phead->Pnext = phead;
	phead->Ppre = phead;
	phead->stu_message.StuNumber = 0;
};
void AddStuFailUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*           ѧ����Ϣ���ʧ��!           *\n");
	printf("\t\t\t\t\t*****************************************\n");
};

void saveinflie(struct node* phead) 
{
	//�����Ϸ��Լ��
	if (phead == NULL)
		return;
	//���ļ�
	FILE* pflie = NULL;
	errno_t nes = fopen_s(&pflie, "stu.date", "w");
	if (nes != 0 || pflie == NULL)
		return;
	//д���ļ�
	struct node* pt = phead->Pnext;
	while (pt!=phead)
	{
		fwrite(&(pt->stu_message), sizeof(struct StuMessage), 1, pflie);
		pt = pt->Pnext;
	}
	fclose(pflie);
	//�ر��ļ�

};
void SaveInflieSucessUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*           �� �� �� �� ! ! !           *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void ReadFormFlie(struct node* phead)
{
	//�������
	if (phead == NULL)
		return;
	//���ļ�
	FILE* pflie = NULL;
	errno_t nes = fopen_s(&pflie, "stu.date", "r");
	if (nes != 0 || pflie == NULL)
		return;
	//��ȡ�ļ�
	struct StuMessage stu;
	while (fread(&stu, sizeof(struct StuMessage), 1, pflie) != 0)
	{
		add(phead, &stu);
	}
	//�ر��ļ�
	fclose(pflie);
	
};

bool IsnameExist(struct node* phead, char* pname)
{
	//�Ϸ��Լ��
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
	printf("\t\t\t\t\t*           ѧ���Ѵ���!                 *\n");
	printf("\t\t\t\t\t*****************************************\n");
}

void LookAll(struct node* phead)
{
	//�����Ϸ��Լ��
	if (phead == NULL || phead->count == 0)
		return;
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	//���ݱ���
	printf("\t\t\t\t\t*        ѧ��      ����      �ɼ�       *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	struct node* pt = phead->Pnext;
	while (pt!=phead)
	{
		printf("\t\t\t\t\t* |        %2d      %-10s%3d      | *\n",pt->stu_message.StuNumber,pt->stu_message.name,pt->stu_message.date);
		pt = pt->Pnext;
	}
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	//���ݽ�β
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
    printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
};
void LookSpecifyName(struct node* phead, struct StuMessage stu)
{

	//�����Ϸ��Լ��
	if (phead == NULL || phead->count == 0)
		return;
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             ��������:%-10s       *\n",stu.name);
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(21, 0);
	//���ݱ���
	printf("\t\t\t\t\t*        ѧ��      ����      �ɼ�       *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	struct node* pt = phead->Pnext;
	while (pt != phead)
	{
		if(strcmp(pt->stu_message.name,stu.name)==0)
		printf("\t\t\t\t\t* |        %2d      %-10s%3d      | *\n", pt->stu_message.StuNumber, pt->stu_message.name, pt->stu_message.date);
		pt = pt->Pnext;
	}
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	//���ݽ�β
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);

};
void LookSpecifyNameUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             �������֣�                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
}

void RangeUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*           ���������Χ��       ��     *\n");
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
	//���ݱ���
	printf("\t\t\t\t\t*        ѧ��      ����      �ɼ�       *\n");
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	struct node* pt = phead->Pnext;
	while (pt != phead)
	{
		if (pt->stu_message.date>=min&&pt->stu_message.date<=max)
			printf("\t\t\t\t\t* |        %2d      %-10s%3d      | *\n", pt->stu_message.StuNumber, pt->stu_message.name, pt->stu_message.date);
		pt = pt->Pnext;
	}
	//���ݽ�β
	printf("\t\t\t\t\t*  -----------------------------------  *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
}

void DeleteNameUI(void)
{
	system("cls");
	ManageMenuUI();
	SetCursorPosition(19, 0);
	printf("\t\t\t\t\t*             ɾ�����֣�                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
};
void DeleteNameSuccessUI(void)
{
	SetCursorPosition(21, 0);
	printf("\t\t\t\t\t*             ɾ���ɹ���                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 64);
}
void DeleteNameFailUI(void)
{
	SetCursorPosition(21, 0);
	printf("\t\t\t\t\t*             ɾ��ʧ�ܣ�                *\n");
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
		if (strcmp(pt->stu_message.name, pstu->name) == 0)//ɾ��
		{
			struct node* ptemp = pt->Ppre;//���Ҫɾ����ǰһ�����
			pt->Ppre->Pnext=pt->Pnext;//ǰһ������pnextָ��ָ��pt�ĺ�һ�����
			pt->Pnext->Ppre=pt->Ppre;//��һ������ppreָ��ָ��pt��ǰһ�����
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
	printf("\t\t\t\t\t*          Ҫ�޸ĵ�ѧ�����֣�           *\n");
	printf("\t\t\t\t\t*          Ҫ�޸ĵ�ѧ��������           *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(19, 69);
}
void ChangeSuccessUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*             �޸ĳɹ���                *\n");
	printf("\t\t\t\t\t*****************************************\n");
	SetCursorPosition(17, 64);
}
void ChangeFailUI(void)
{
	SetCursorPosition(22, 0);
	printf("\t\t\t\t\t*             �޸�ʧ�ܣ�                *\n");
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
		if (strcmp(pt->stu_message.name, pstu->name) == 0)//�޸�
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
	printf("\t\t\t\t\t*             �������!                 *\n");
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
		pt->stu_message.date = rand() % 71 + 30;//����30~100�������
		pt = pt->Pnext;
	}
	return ;
	
}

void SortByScore(struct node* phead) //ð���㷨
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
				//����
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
				//����
				struct StuMessage temp = ptemp->stu_message;
				ptemp->stu_message = ptemp->Pnext->stu_message;
				ptemp->Pnext->stu_message = temp;

			}
			ptemp = ptemp->Pnext;
		}
	}

}
void SortByScore2(struct node* phead)//ѡ������
{
	if (phead == NULL || phead->count <= 0)
		return;
	struct node* pt = NULL;//ѭ��ָ��
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
		pmax = pt;//���迪ʼ��λ����С
		pstart = pt;//��ǿ�ʼ��λ��
		for (unsigned int j = 0; j < phead->count - i; j++)//  ѡ����������С��
		{
			if (pmax->stu_message.date < pt->stu_message.date)
			{
				pmax = pt;
			}
			pt = pt->Pnext;
		}
		//�Ϳ�ʼ��λ�ý������
		temp = pstart->stu_message;
		pstart->stu_message = pmax->stu_message;
		pmax->stu_message = temp;
	}

}//