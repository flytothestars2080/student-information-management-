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
	unsigned  int StuNumber;//学号
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
extern struct User User_Message;//这是个声明
void ManageMenuUI(void );//管理主菜单
void SetCursorPosition(y, x);//设置光标位置
void inputFailUI(void);//选择错误
void QuitUI(void);//退出
void Countdown(short x, short y, int time, int start);//倒计时函数

void AddStuUI(void);//学生添加ui;
void AddStuSucessUI(void);//学生添加成功ui
bool add(struct node* phead, struct StuMessage * PstuMessage);//学生添加成功
void AddStuFailUI(void);//添加失败界面
void FreeList(struct node* phead);//释放链表

void saveinflie(struct node* phead);//保存进文件
void SaveInflieSucessUI(void);//保存成功ui
void ReadFormFlie(struct node*phead);//从文件中读取

void NameIsExistUI(void);//判断重名ui
bool IsnameExist(struct node* phead, char* pname);//判断名字是否存在
void LookAll(struct node* phead);//看所有人

void ProduceStuNumber(struct node* phead);//生成学号

void LookSpecifyName(struct node* phead, struct StuMessage stu);//查看指定的名字
void LookSpecifyNameUI(void);//查看ui

void RangeUI(void);
void LookRangeStu(struct node* phead, unsigned iScore1, unsigned iScore2);//范围查找

void DeleteNameUI(void);//删除
void DeleteNameSuccessUI(void);
void DeleteNameFailUI(void);
bool DeleteStubyName(struct node* phead, struct StuMessage* pstu);
void ProduceNewStuNumber(struct node* phead);//重新生成学号

void ChangeUI(void);
void ChangeSuccessUI(void);
void ChangeFailUI(void);
bool ChangeStuMessage(struct node*phead,struct StuMessage*pstu);

void Test(struct node* phead);
void TestSucessUI(void);

void SortByScore(struct node* phead);//冒泡排序
void SortByStuNumber(struct node* phead); //冒泡排序
void SortByScore2(struct node* phead);//选择排序




