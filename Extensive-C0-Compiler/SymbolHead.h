#pragma once
#include"Error.h"
#include"Compiler.h"

typedef struct
{
	int cls;		// class: int char void
	int type;		// type: const var array fun param
	int length;		// const->value []->length, func->num_of_params
	int defLine;	// Line No. of def of IDEN
	int addr = -1;		// addr of IDEN
	int reg = -1;	// which reg it'll use  t0 ~ t7, s0 ~ s8
	std::string name;
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
	extern std::map<std::string, int> output_str_sym;

	varinfo *lookup(const std::string &curFunc, const std::string &name, bool local);
	bool is_global_iden(const std::string &curFunc, std::string &s);
	std::map<std::string, varinfo> lookup_func(const std::string &func_name);
	varinfo *lookup_para(std::map<std::string, varinfo> &func_symtab, int place);

	void addsym(std::string curFunc, std::string namae, int _class, int type, int length, int line);
	int addStr(std::string &s);
	void printSym(std::ofstream&o);

}

