#include <string>
#include <stack>
#include <vector>
#include <cstdlib>
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

double eval1();
double eval2();
double eval3();
double eval4();
double eval5();
double eval6();
double atom();

void put_back()
{
	for (int i=0; i<run.token.length(); i++)
	{
		run.idx--;
		if (run.idx < 0)
		{
			run.line--;
			run.idx = prog[run.line].length() - 1;
		}
	}
}


double evaluate()
{
	getToken();

	if (run.tok_type != NUMBER && run.tok_type!=VARIABLE)
		throw((string)"表达式错误");

	double result = eval1();

	put_back();

	return result;
}

double eval1()
{
	double left = eval2();
	double result = left;
	double right;

	if (run.token == "<")
	{
		getToken();
		right = eval1();
		if (left < right) result = 1.0;
		else result = 0.0;
	}
	else if (run.token == ">")
	{
		getToken();
		right = eval1();
		if (left > right) result = 1.0;
		else result = 0.0;
	}
	else if (run.token == "<=")
	{
		getToken();
		right = eval1();
		if (left <= right) result = 1.0;
		else result = 0.0;
	}
	else if (run.token == ">=")
	{
		getToken();
		right = eval1();
		if (left >= right) result = 1.0;
		else result = 0.0;
	}
	else if (run.token == "==")
	{
		getToken();
		right = eval1();
		if (left == right) result = 1.0;
		else result = 0.0;
	}
	else if (run.token =="!=")
	{
		getToken();
		right = eval1();
		if (left == right) result = 1.0;
		else result = 0.0;
	}

	return result;
}

double eval2()
{
	double result = eval3();
	
	bool flag = true;
	while (flag)
	{
		if (run.token == "+") { getToken(); result += eval3(); }
		else if (run.token == "-") {getToken();  result -= eval3(); }
		else flag = false;
	}
	return result;
}

double eval3()
{
	double result = eval4();

	bool flag = true;
	while (flag)
	{
		if (run.token == "*") {getToken(); result *= eval4(); }
		else if (run.token == "/") 
		{
			getToken();
			double xx=eval4();
			if (xx == 0.0) throw((string)"被0除");
			result /= xx;
		}
		else if (run.token == "%")
		{
			getToken();
			int xx = eval4();
			if (xx == 0.0) throw((string)"被0除");
			result = (int)result % xx;
		}
		else flag = false;
	}

	return result;

}

double eval4()
{
	double result = eval5();

	if (run.token == "^")
	{
		getToken();
		double presult = eval4();
		double ex = result;
		if (presult == 0.0) result = 1.0;
		else
			for (int t=(int)presult-1; t>0; t--)
				result *= ex;
	}

	return result;
}

double eval5()
{
	string op="";
	double result;

	if (run.token=="+" || run.token=="-")
	{
		op = run.token;
		getToken();
	}
	result = eval6();
	if (op=="-") result = -result;
	return result;
}

double eval6()
{
	double result;

	if (run.token=="(")
	{
		getToken();
		result = eval2();
		getToken();
		if (run.token != ")") throw((string)"括号不匹配");
	}
	else result = atom();

	return result;
}

double atom()
{
	double result;

	if (run.tok_type==NUMBER)
	{
		result = atof(run.token.data());
		getToken();
	}
	else if (run.tok_type==VARIABLE)
	{
		result = find_var(run.token);
		if (result == 0xFFFFFFFF) throw((string)"变量没有声明");
		getToken();
	}
	else throw((string)"表达式错误");

	return result;
}
