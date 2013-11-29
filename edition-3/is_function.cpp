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

int is_var(string str)
{
	for (int i=0; i<var.size(); i++)
		if (str == var[i].str)
			return i;
	return -1;
}

int is_keyword(string str)
{
	for (int i=0; i<Key_size; i++)
		if (str == key[i].str)
			return i;
	return -1;
}

int is_type(string str)
{
	if (str == "integer") return 1;
	if (str == "real") return 2;
	if (str == "char") return 3;
	return -1;
}

double find_var(string str)
{
	double x = is_var(str);
	if (x == -1) return 0xFFFFFFFF;
	else return var[x].value;
}
