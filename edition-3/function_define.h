#pragma once

#include <string>
using namespace std;

//load���������ļ��ж������
void load();

//run���������г���
void runs();

//getToken��������ȡ��һ����ʶ��
void getToken();

//assignment��������ֵ����
void assignment();

//exevar�������������������
void exevar();

//exefor����������forѭ��
void exefor();

//exeblock��������������
void exeblock();

//exeread����������read����
void exeread();

//exewrite����������write���
void exewrite();

//exewriteln����������writeln���
void exewriteln();

//exeif����������if���
void exeif();

//evaluate����������һ�����ʽ��ֵ
double evaluate();

//put_back������������һ��token��λ��
void put_back();

//is_var����������һ��str�Ƿ�Ϊ����
int is_var(string str);

//is_keyword����������һ��str�Ƿ�Ϊ�ؼ���
int is_keyword(string str);

//is_type����������һ��str�Ƿ�Ϊ��������
int is_type(string str);

//find_var����������һ��������ֵ
double find_var(string str);