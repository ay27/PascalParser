#pragma once

#include "const.h"
#include <string>
using namespace std;

struct Keyword
{
	//static int size;
	string str;
	int id;
	Keyword() { str.clear();  id=0; }
	Keyword(string str, int id):str(str), id(id) {/*size++; */}
};
//int Keyword::size = 0;

struct ForInfo
{
	int var_id;
	int target;
	int line;
	ForInfo()
	{
		var_id = target = line = -1;
	}
	ForInfo(int var_id, int target, int line)
		:var_id(var_id),target(target),line(line)
	{}
};

struct RunInfo
{
	int idx;
	int line;
	string token;
	int tok_type;
	int key_id;
	int var_id;
	int type_id;
	RunInfo()
	{
		idx = line = tok_type = key_id  = var_id =type_id = -1;
		token.clear();
	}
	RunInfo(int idx, int line)
		:idx(idx), line(line)
	{
		token.clear(); tok_type = key_id  = var_id = type_id = -1;
	}
};

struct VarInfo
{
	string str;
	double value;
	int type;
	VarInfo()
	{
		str.clear();
		value = type = -1;
	}
	VarInfo(string str, double val, int type)
		:str(str), value(val), type(type)
	{}
	VarInfo(string str, double val)
		:str(str), value(val), type(-1)
	{}
};

struct TYPE
{
	string str;
	int type;
	TYPE() { }
	TYPE(string str, int type):str(str), type(type) { }
};