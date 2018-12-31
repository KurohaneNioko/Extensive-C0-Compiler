#pragma once
#include"Intermediate.h"
#include"SymbolHead.h"
#include"Compiler.h"



struct runinfo
{
	bool CLK_use[reg_t_max + reg_s_max];// = { false };	// for clock algorithm in page swap (OS)
	bool ts_use[reg_t_max + reg_s_max];// = { false };	// t0 ~ t7, s0 ~ s8
	int CLK_ptr;// = 0;
	std::string ts_content[reg_t_max + reg_s_max];// = { "" };
	std::map<std::string, varinfo> symtab;
	//std::string ax_content[4] = { "" };
};




namespace OC
{
	void Med2Mips(std::string mipsfile);
}

