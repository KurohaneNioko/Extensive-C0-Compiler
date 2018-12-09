#pragma once
#include"Intermediate.h"
#include"SymbolHead.h"
#include"Compiler.h"

constexpr auto reg_t_max = 10;
constexpr auto reg_s_max = 8;

struct reguse
{
	bool t_use[reg_t_max] = { false };	// t0 ~ t9
	bool s_use[reg_s_max] = { false };	// s0 ~s7
	std::string t_content[reg_t_max] = { "" };
	std::string s_content[reg_s_max] = { "" };
};







namespace OC
{
	void Med2Mips();
}

