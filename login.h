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
void LoginMenuUI(void);//�˵�
void SetCursorPosition(short y, short x);//������ú���
bool login(void);//����
void LoginUI(void);//���������ʾ
void LoginFailUI(void);//����ʧ�ܽ���
void LoginSucessUI(void);//����ɹ�����
void RegisterUI(void);//ע�����
void RegisterFailUI(void);//ע��ʧ�ܽ���
void RegisterSucessUI(void);//��¼ע��ɹ�����
void Countdown(short x, short y, int time, int start);//����ʱ
void Saveusr(struct User* puser);//�û���������д���ļ�
bool Isright(struct User* Puser);//��֤�û���������
bool IsUserExit(struct User* Puser);//��֤�û���
void VisterLoginUI(void);
void QuitLoginUI(void);
void OrderFailUI();
