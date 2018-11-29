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
	//��¼������ֲ����������������ÿ�����������ʹ�����
	//bool flag[kMaxBasicBlock];
	//��¼�������ʶ����Ӧ�ļĴ�������������ʱ�����ͼ򵥱����Լ�����������Ч
	//int regIndex;
} varinfo;

namespace Sym {
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
	// length of IDEN = 0 ~ inf, int|char-0(const->value), fun-num_of_params, array-len

	extern std::map<std::string, varinfo> global_sym;
	extern std::map<std::string, std::map<std::string, varinfo>> func_sym;
}

