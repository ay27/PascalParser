#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <vector>
#include "function_define.h"
#include "struct.h"
#include "const.h"

using namespace std;


Keyword key[] = {
				Keyword("unknow", UNKNOW),
				Keyword("var", VAR),
				Keyword("for", FOR),
				Keyword("to", TO),
				Keyword("begin", BEGIN),
				Keyword("end", END),
				Keyword("read", READ),
				Keyword("write", WRITE),
				Keyword("writeln", WRITELN),
				Keyword("if", IF),
				Keyword("then", THEN),
				Keyword("do", DO)};

const TYPE type[] = {
					TYPE("integer",INTEGER),
					TYPE("real", REAL),
					TYPE("char", CHAR)};

vector<VarInfo> var;
stack<ForInfo> fstack;
RunInfo run;
vector<string> prog;
stack<RunInfo> block;


int main()
{
	try {
		load();
		runs();
	} catch (string exc)
	{
		printf("%s\n", exc.data());
		printf("在第%d行，第%d列.\n", run.line+1, run.idx+1);
	}
	return 0;
}
