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

extern Keyword key[];
extern vector<VarInfo> var;
extern stack<ForInfo> fstack;
extern RunInfo run;
extern vector<string> prog;
extern stack<RunInfo> block;

void runs()
{
	do {
		getToken();

		if (run.tok_type == VARIABLE)
			assignment();
		else switch (run.key_id)
		{
		case VAR:
			exevar();
			break;
		case FOR:
			exefor();
			break;
		case BEGIN:
			exeblock();
			break;
		case READ:
			exeread();
			break;
		case WRITE:
			exewrite();
			break;
		case WRITELN:
			exewriteln();
			break;
		case IF:
			exeif();
			break;
		case END:
			if (block.empty()) throw((string)"begin-end��ƥ��");
			block.pop();
			getToken();
			if (run.token == ".") {cout<<"������ɣ�"<<endl; exit(0); }
			if (run.token != ";") throw((string)"ȱ��;");
			return;
			break;
		case UNKNOW:
			throw((string)"����ʶ��ķ���");
			break;
		}
	} while (run.token != EOP);
}
