#pragma once

#include <string>
using namespace std;

//load函数，从文件中读入程序
void load();

//run函数，运行程序
void runs();

//getToken函数，获取下一个标识符
void getToken();

//assignment函数，赋值运算
void assignment();

//exevar函数，处理变量的声明
void exevar();

//exefor函数，处理for循环
void exefor();

//exeblock函数，处理语句块
void exeblock();

//exeread函数，处理read输入
void exeread();

//exewrite函数，处理write输出
void exewrite();

//exewriteln函数，处理writeln输出
void exewriteln();

//exeif函数，处理if语句
void exeif();

//evaluate函数，计算一个表达式的值
double evaluate();

//put_back函数，返回上一个token的位置
void put_back();

//is_var函数，查找一个str是否为变量
int is_var(string str);

//is_keyword函数，查找一个str是否为关键字
int is_keyword(string str);

//is_type函数，查找一个str是否为数据类型
int is_type(string str);

//find_var函数，返回一个变量的值
double find_var(string str);