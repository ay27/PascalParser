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

bool is_space_tab(char ch);
bool is_number(char ch);
bool is_alpha(char ch);
bool is_delimiter(char ch);

void not_complete()
{
	if (run.line>=prog.size()) throw((string)"程序不完整");
}

void getToken()
{
	string temp;
	temp.clear();
	run = RunInfo(run.idx, run.line);

	if (run.idx >= prog[run.line].length()) {run.line++; run.idx = 0; }

	while (is_space_tab(prog[run.line][run.idx]))
	{
		run.idx++;
		if (run.idx>=prog[run.line].length()) { run.line++; run.idx = 0; }
		not_complete();
	}

	
	if (is_number(prog[run.line][run.idx]))
	{
		while (is_number(prog[run.line][run.idx]))
		{
			temp += prog[run.line][run.idx];
			run.idx++;
			if (run.idx>=prog[run.line].length()) {run.idx=0; run.line++; break;}
			not_complete();
		}
		run.token = temp;
		run.tok_type = NUMBER;
		return;
	}
	
	if (is_alpha(prog[run.line][run.idx]))
	{
		while (is_alpha(prog[run.line][run.idx]))
		{
			temp += tolower(prog[run.line][run.idx]);
			run.idx++;
			if (run.idx>=prog[run.line].length()) {run.idx=0; run.line++; break; }
			not_complete();
		}
		run.token = temp;

		if ((run.var_id = is_var(temp)) != -1)  run.tok_type = VARIABLE;

		else if ((run.key_id = is_keyword(temp)) != -1)   run.tok_type = KEYWORD;

		else if ((run.type_id = is_type(temp)) != -1) run.tok_type = PTYPE;
		return;
	}

	if (prog[run.line][run.idx] == '"')
	{
		run.idx++;
		if (run.idx>=prog[run.line].length() || run.line>=prog.size()) throw((string)"\"不匹配,程序不完整");

		while (prog[run.line][run.idx] != '"')
		{
			temp += prog[run.line][run.idx];
			run.idx++;
			if (run.idx>=prog[run.line].length()) {run.idx=0; run.line++; break; }
			not_complete();
		}
		run.idx++;
		if (run.idx>=prog[run.line].length()) {run.idx=0; run.line++; }
		not_complete();
		run.token = temp;
		run.tok_type = STR;
		return;
	}

	if (is_delimiter(prog[run.line][run.idx]))
	{
		char ch = prog[run.line][run.idx];
		temp += ch;
		run.idx++;
		if (run.idx>=prog[run.line].length()) { run.idx=0; run.line++; }
		if (ch!='.' && run.line>=prog.size()) throw((string)"程序不完整");
		if (ch=='<' || ch=='>' || ch=='=' || ch=='!')
		{
			char tt=prog[run.line][run.idx];
			if (tt=='<' || tt=='>' || ch=='=')
			{
				temp+=tt;
				run.idx++;
				if (run.idx>=prog[run.line].length()) {run.idx=0; run.line++; }
				not_complete();
			}
		}
		else if (ch==':')
		{
			if (prog[run.line][run.idx]=='=')
			{
				temp += '=';
				run.idx++;
				if (run.idx>=prog[run.line].length()) {run.idx=0; run.line++; }
				not_complete();
			}
		}
		run.token = temp;
		run.tok_type = DELIMITER;
		return;
	}
}

bool is_space_tab(char ch)
{
	if (ch==' ' || ch=='\t') return true;
	return false;
}

bool is_number(char ch)
{
	if (ch>='0' && ch<='9') return true;
	if (ch=='.') return true;
	return false;
}

bool is_alpha(char ch)
{
	if ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) return true;
	return false;
}

bool is_delimiter(char ch)
{
	if (ch=='+' || ch=='-' || ch=='*' || ch=='/' ||
		ch=='%' || ch=='^' || ch==':' || ch=='=' ||
		ch=='<' || ch=='>' || ch==',' || ch==';' ||
		ch=='(' || ch==')' || ch=='.') return true;
	return false;
}
