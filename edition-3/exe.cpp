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

void exevar()
{
	int var_id;

	getToken();

	if (run.var_id != -1) throw((string)"变量重复定义");

	int back = var.size();

	var.push_back(VarInfo(run.token, 0));

	getToken();

	//处理多个变量同时声明
	if (run.token == ",")
	{
		while (run.token != ":")
		{
			getToken();
			if (run.var_id != -1) throw((string)"变量重复定义");
			var.push_back(VarInfo(run.token, 0));

			getToken();
			if (run.token != "," && run.token != ":") throw((string)"语法错误");
		}
	}
	else if (run.token != ":") throw((string)"缺少:");

	//处理数据类型
	getToken();
	if (run.type_id == -1) throw((string)"不存在该数据类型");
	for (int i=back; i<var.size(); i++)
		var[i].type = run.type_id;

	getToken();
	if (run.token != ";") throw((string)"缺少;");

	getToken();
	if (run.key_id != BEGIN) { put_back(); exevar(); }
	else put_back();
}

void exefor()
{
	getToken();
	
	int var_id = run.var_id;
	if (var_id == -1) throw((string)"该变量没有声明");

	getToken();
	if (run.token!=":=") throw((string)"缺少:=");

	int beg = evaluate();
	
	getToken();
	if (run.key_id != TO) throw((string)"缺少to");

	int target = evaluate();

	fstack.push(ForInfo(var_id, target, run.line+1));

	getToken();
	if (run.key_id != DO) throw((string)"缺少do");

	var[var_id].value = beg;
	while ((int)var[var_id].value <= (int)fstack.top().target)
	{
		run = RunInfo(0, fstack.top().line);
		getToken();
		if (run.key_id != BEGIN) throw((string)"缺少begin");
		exeblock();
		var[var_id].value++;
	}
	var[var_id].value--;
	fstack.pop();
}

void exeblock()
{
	block.push(run);
	runs();
}

void exeread()
{
	getToken();
	if (run.token!="(") throw((string)"缺少(");

	while (run.token!=")")
	{
		getToken();
		if (run.var_id == -1) throw((string)"变量没有声明");
		switch (var[run.var_id].type)
		{
		case INTEGER:
			int temp;
			scanf("%d", &temp);
			var[run.var_id].value = temp;
			break;
		case REAL:
			double tt;
			scanf("%lf", &tt);
			var[run.var_id].value = tt;
			break;
		case CHAR:
			char ch;
			scanf("%c", &ch);
			var[run.var_id].value = ch;
			break;
		}

		getToken();
		if (run.token!="," && run.token!=")") throw((string)"缺少,或)");
	}
	getToken();
	if (run.token!=";") throw((string)"缺少;");
}


void exewrite()
{
	getToken();
	if (run.token!="(") throw((string)"缺少(");

	while (run.token!=")")
	{
		getToken();
		if (run.tok_type==STR || run.tok_type==NUMBER)
			printf("%s", run.token.data());
		else if (run.tok_type==VARIABLE)
		{
			if (var[run.var_id].type==INTEGER) printf("%d", (int)var[run.var_id].value);
			if (var[run.var_id].type==REAL) printf("%lf", var[run.var_id].value);
			if (var[run.var_id].type==CHAR) printf("%c", (int)var[run.var_id].value);
		}
		getToken();
		if (run.token!="," && run.token!=")") throw((string)"缺少,或)");
		if (run.token == ",") printf(" ");
	}
	getToken();
	if (run.token!=";") throw((string)"缺少;");

}

void exewriteln()
{
	exewrite();
	printf("\n");
}

void exeif()
{
	double result = evaluate();

	if (!(int)result)
	{
		getToken();
		while (run.key_id != END)
			getToken();
		put_back();
	}
	else {
		getToken();
		if (run.key_id != THEN) throw((string)"缺少then");
	}
}
