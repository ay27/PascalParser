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

	if (run.var_id != -1) throw((string)"�����ظ�����");

	int back = var.size();

	var.push_back(VarInfo(run.token, 0));

	getToken();

	//����������ͬʱ����
	if (run.token == ",")
	{
		while (run.token != ":")
		{
			getToken();
			if (run.var_id != -1) throw((string)"�����ظ�����");
			var.push_back(VarInfo(run.token, 0));

			getToken();
			if (run.token != "," && run.token != ":") throw((string)"�﷨����");
		}
	}
	else if (run.token != ":") throw((string)"ȱ��:");

	//������������
	getToken();
	if (run.type_id == -1) throw((string)"�����ڸ���������");
	for (int i=back; i<var.size(); i++)
		var[i].type = run.type_id;

	getToken();
	if (run.token != ";") throw((string)"ȱ��;");

	getToken();
	if (run.key_id != BEGIN) { put_back(); exevar(); }
	else put_back();
}

void exefor()
{
	getToken();
	
	int var_id = run.var_id;
	if (var_id == -1) throw((string)"�ñ���û������");

	getToken();
	if (run.token!=":=") throw((string)"ȱ��:=");

	int beg = evaluate();
	
	getToken();
	if (run.key_id != TO) throw((string)"ȱ��to");

	int target = evaluate();

	fstack.push(ForInfo(var_id, target, run.line+1));

	getToken();
	if (run.key_id != DO) throw((string)"ȱ��do");

	var[var_id].value = beg;
	while ((int)var[var_id].value <= (int)fstack.top().target)
	{
		run = RunInfo(0, fstack.top().line);
		getToken();
		if (run.key_id != BEGIN) throw((string)"ȱ��begin");
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
	if (run.token!="(") throw((string)"ȱ��(");

	while (run.token!=")")
	{
		getToken();
		if (run.var_id == -1) throw((string)"����û������");
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
		if (run.token!="," && run.token!=")") throw((string)"ȱ��,��)");
	}
	getToken();
	if (run.token!=";") throw((string)"ȱ��;");
}


void exewrite()
{
	getToken();
	if (run.token!="(") throw((string)"ȱ��(");

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
		if (run.token!="," && run.token!=")") throw((string)"ȱ��,��)");
		if (run.token == ",") printf(" ");
	}
	getToken();
	if (run.token!=";") throw((string)"ȱ��;");

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
		if (run.key_id != THEN) throw((string)"ȱ��then");
	}
}
