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

	//��ʼ�����в���
	var.clear();
	prog.clear();

	
	//��ȡ�ļ��еĳ���
	string temp;
	while (getline(file, temp))  prog.push_back(temp);
	file.close();

	//��ʼ�����в���
	run = RunInfo(0, 0);

	
}
