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

struct use 
{
	unsigned BBno;
	int BBLine;
};
typedef struct DUChain
{
	unsigned defBB;		// BB No. when def 
	int defBBLine;	// def line in BB
	std::string name;
	std::vector<struct use> useinfo;
}duc;

namespace OPT
{
	extern std::string optinfofile;
	extern std::ofstream optout;
	extern std::map<std::string, std::map<std::string, std::vector<duc>>> func_DU;
	decltype(Med::itmd_code.begin()) firstIRinBLK(const unsigned &blk_no);
	void allOptimize();
}
