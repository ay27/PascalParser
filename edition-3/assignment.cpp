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
extern const TYPE type[];
extern vector<VarInfo> var;
extern stack<ForInfo> fstack;
extern RunInfo run;
extern vector<string> prog;
extern stack<RunInfo> block;

void assignment()
{
	int var_id=run.var_id;

	getToken();
	
	if (run.token!=":=") throw((string)"»±…Ÿ£∫=");

	double result = evaluate();

	var[var_id].value = result;

	getToken();
	if (run.token != ";") throw((string)"»±…Ÿ;");
}

