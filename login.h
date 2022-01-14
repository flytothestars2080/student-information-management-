#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<stdbool.h>
struct User
{
	char name[15];
	char key[20];
}; 
void LoginMenuUI(void);//菜单
void SetCursorPosition(short y, short x);//光标设置函数
bool login(void);//登入
void LoginUI(void);//登入界面显示
void LoginFailUI(void);//登入失败界面
void LoginSucessUI(void);//登入成功界面
void RegisterUI(void);//注册界面
void RegisterFailUI(void);//注册失败界面
void RegisterSucessUI(void);//登录注册成功界面
void Countdown(short x, short y, int time, int start);//倒计时
void Saveusr(struct User* puser);//用户名和密码写入文件
bool Isright(struct User* Puser);//验证用户名和密码
bool IsUserExit(struct User* Puser);//验证用户名
void VisterLoginUI(void);
void QuitLoginUI(void);
void OrderFailUI();
