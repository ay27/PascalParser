#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stack>
#include <vector>
#include "function_define.h"
#include "struct.h"
#include "const.h"

using namespace std;


extern vector<VarInfo> var;
extern RunInfo run;
extern vector<string> prog;

void load()
{
	ifstream file("test.pas");

	//初始化运行参数
	var.clear();
	prog.clear();

	
	//读取文件中的程序
	string temp;
	while (getline(file, temp))  prog.push_back(temp);
	file.close();

	//初始化运行参数
	run = RunInfo(0, 0);

	
}
