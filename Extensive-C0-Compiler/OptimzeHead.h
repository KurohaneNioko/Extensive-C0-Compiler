#pragma once
#include"Compiler.h"
#include"Intermediate.h"
#include"SymbolHead.h"

typedef struct {
	std::set<int> nextBBno;	// next basic block No.
	std::set<int> prevBBno; // previous basic block No.
	std::string func_name;
}BasicBlock;
typedef BasicBlock BB;

extern std::vector<BB> blocks;

namespace OPT
{
	extern std::string optinfofile;
	void allOptimize();
}
