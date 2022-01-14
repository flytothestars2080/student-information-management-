#pragma once
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
struct User
{
	char name[15];
	char key[20]; 
};
struct StuMessage
{
	unsigned  int StuNumber;//ѧ��
	char name[15];
	unsigned int date;
};
struct node
{
	struct StuMessage  stu_message;
	unsigned int count;
	struct node* Pnext;
	struct node* Ppre;
};
extern struct User User_Message;//���Ǹ�����
void ManageMenuUI(void );//�������˵�
void SetCursorPosition(y, x);//���ù��λ��
void inputFailUI(void);//ѡ�����
void QuitUI(void);//�˳�
void Countdown(short x, short y, int time, int start);//����ʱ����

void AddStuUI(void);//ѧ�����ui;
void AddStuSucessUI(void);//ѧ����ӳɹ�ui
bool add(struct node* phead, struct StuMessage * PstuMessage);//ѧ����ӳɹ�
void AddStuFailUI(void);//���ʧ�ܽ���
void FreeList(struct node* phead);//�ͷ�����

void saveinflie(struct node* phead);//������ļ�
void SaveInflieSucessUI(void);//����ɹ�ui
void ReadFormFlie(struct node*phead);//���ļ��ж�ȡ

void NameIsExistUI(void);//�ж�����ui
bool IsnameExist(struct node* phead, char* pname);//�ж������Ƿ����
void LookAll(struct node* phead);//��������

void ProduceStuNumber(struct node* phead);//����ѧ��

void LookSpecifyName(struct node* phead, struct StuMessage stu);//�鿴ָ��������
void LookSpecifyNameUI(void);//�鿴ui

void RangeUI(void);
void LookRangeStu(struct node* phead, unsigned iScore1, unsigned iScore2);//��Χ����

void DeleteNameUI(void);//ɾ��
void DeleteNameSuccessUI(void);
void DeleteNameFailUI(void);
bool DeleteStubyName(struct node* phead, struct StuMessage* pstu);
void ProduceNewStuNumber(struct node* phead);//��������ѧ��

void ChangeUI(void);
void ChangeSuccessUI(void);
void ChangeFailUI(void);
bool ChangeStuMessage(struct node*phead,struct StuMessage*pstu);

void Test(struct node* phead);
void TestSucessUI(void);

void SortByScore(struct node* phead);//ð������
void SortByStuNumber(struct node* phead); //ð������
void SortByScore2(struct node* phead);//ѡ������




