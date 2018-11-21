#pragma once

#include"Compiler.h"

#if DEBUG
#define Lexical_Out 0
#else
#define Lexical_Out 0
#endif


#define CODEEOF (Lex::code_file.eof())
namespace Lex
{
	extern constexpr auto UNKNOWN = 0;		// 5StarsBB
	extern constexpr auto IDEN = 1;		// ISLAND
	extern constexpr auto UNSGN_INT = 2;		// 19260817
	extern constexpr auto SGL_CHARA = 3;		// 'a'
	extern constexpr auto STRING = 4;		// "HuaLaiShi"
	extern constexpr auto RSVD_WD = 5;		// if
	extern constexpr auto RSVD_SYM = 6;		// ==
	/* reserved words -> symbol 4 recognition */
	extern const std::map<std::string, std::string> reservedWords;/* =
	{
		{"const",	"CONST_SYM"},
		{"int",		"INT_SYM"},
		{"char",	"CHAR_SYM"},
		{"void",	"VOID_SYM"},
		{"main",	"MAIN_SYM"},
		{"if",		"IF_SYM"},
		{"else",	"ELSE_SYM"},
		{"for",		"FOR_SYM" },
		{"while",	"WHILE_SYM"},
		{"scanf",	"SCANF_SYM"},
		{"printf",	"PRINTF_SYM"},
		{"return",	"RET_SYM"}
	};*/
	/* reserved symbols, no alpha */
	extern const std::map<std::string, std::string> non_alpha_sym; /*=
	{
		{"+",	"ADD"},		{"-",	"SUB"},
		{"*",	"MUL"},		{"/",	"DIV"},
		{"(",	"L_SMALL"},	{")",	"R_SMALL"},
		{"[",	"L_MID"},	{"]",	"R_MID"},
		{"{",	"L_BIG"},	{"}",	"R_BIG"},
		{"=",	"ASSIGN"},	
		{"!=",	"NOT_EQL"},	{"==",	"EQUAL"},
		{">",	"GREATER"},	{">=",	"GRT_EQL"},	
		{"<",	"LESS"},	{"<=",	"LES_EQL"},
		{"\"",	"DBL_QUOTE"},{"'",	"SGL_QUOTE"},
		{",",	"COMMA"},	{";",	"SEMICOLON"}
	};*/
	/* code input */
	extern std::ifstream code_file;
	/* current word */
	extern std::string curElmt;
	extern int curNum;
	extern int curCls;
	/* record Line No. */
	extern int LineCounter;
	/* record colomn No. */
	extern std::size_t linePointer;
	int getsym();
}


