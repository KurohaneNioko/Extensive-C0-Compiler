#pragma once
#include"Compiler.h"

typedef struct
{
	std::string name;
	int cls;		// class: int char void
	int type;		// type: const var array fun param
	int length;		// int|char->0,const->value []->length, func->num_of_params
	int defLine;	// Line No. of def of IDEN
	int addr;		// addr of IDEN
	//记录下这个局部变量在这个函数的每个基本块里的使用情况
	//bool flag[kMaxBasicBlock];
	//记录下这个标识符对应的寄存器，仅仅对临时变量和简单变量以及参数变量有效
	//int regIndex;
} varinfo;

namespace ST {	//Symbol Table
	// class of IDEN = {INT, CHAR}
	extern constexpr auto INT_CLS = 1;
	extern constexpr auto CHA_CLS = 2;
	extern constexpr auto VOID_CLS = 3;
	// type of IDEN = {CONST, VAR, ARRAY, FUNC}
	extern constexpr auto CONST_TYP = 1;
	extern constexpr auto VAR_TYP = 2;
	extern constexpr auto ARRAY_TYP = 3;
	extern constexpr auto FUN_TYP = 4;
	extern constexpr auto PARAM_TYP = 5;

	extern std::map<std::string, varinfo> global_sym;
	extern std::map<std::string, std::map<std::string, varinfo>> func_sym;

	varinfo *lookup(std::string curFunc, std::string name, bool local);
	void addsym(std::string curFunc, std::string namae, int _class, int type, int length, int line);
	void printSym();

}

