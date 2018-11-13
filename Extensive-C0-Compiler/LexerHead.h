#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<map>
#include"Compiler.h"

#define Lexical_Out 1
namespace Lex
{
	constexpr auto UNKNOWN = 0;		// 5StarsBB
	constexpr auto IDEN = 1;		// ISLAND
	constexpr auto UNSGN_INT = 2;		// 19260817
	constexpr auto SGL_CHARA = 3;		// 'a'
	constexpr auto STRING = 4;		// "HuaLaiShi"
	constexpr auto RSVD_WD = 5;		// if
	constexpr auto RSVD_SYM = 6;		// ==
	/* reserved words -> symbol 4 recognition */
	const std::map<std::string, std::string> reservedWords =
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
	};
	/* reserved symbols, no alpha */
	const std::map<std::string, std::string> non_alpha_sym =
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
	};
	/* code input */
	std::ifstream code_file;
	/* current word */
	std::string curElmt;
	int curNum = 0;
	/* record Line No. */
	int LineCounter = 0;
	int getsym();
}


