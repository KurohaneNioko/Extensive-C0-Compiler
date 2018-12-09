#include"ObjectCode.h"
#include<stack>
#define COMMENT_OUT 1
std::string SW = "sw";
std::string LW = "lw";
std::string LI = "li";
std::string ADD = "add";
std::string ADDI = "addi";
std::string SUBI = "subi";
std::string SUB = "sub";
std::string BEQ = "beq";
std::string BNE = "bne";
std::string BGEZ = "bgez";
std::string BGTZ = "bgtz";
std::string BLEZ = "blez";
std::string BLTZ = "bltz";
std::string J = "j";
std::string JAL = "jal";
std::string JR = "jr";
std::string MULOBJ = "mul";
std::string DIVOBJ = "div";
std::string MFLO = "mflo";
std::string SYSCALL = "syscall";
std::string LA = "la";
std::string SLL = "sll";
std::string MOVE = "move";
std::string ADDU = "addu";
std::string SP = "$sp";
std::string FP = "$fp";
std::string RA = "$ra";
std::string GP = "$gp";
//t9统一作为操作数1使用的默认寄存器
std::string T9 = "$t9";
//t8专门作为操作数2使用的默认寄存器
std::string T8 = "$t8";
//t7统一作为操作数3使用的默认寄存器
std::string T7 = "$t7";
std::string V0 = "$v0";
std::string A0 = "$a0";
std::string ZERO = "$0";

std::vector<std::string> mips;
#define mpb mips.push_back
int data_head = data_base;	// next data at
reguse curReg;
std::stack<reguse> regstack;

std::string mark2label(std::string &s)
{
	assert(!s.find("%"));
	return "label" + s.erase(0, 1);
}
std::string mark2global_IDEN(std::string &s)
{
	assert(ST::lookup("", s, false) != nullptr);
	return "_" + s;
}
std::string mark2string(std::string &s)
{
	assert(!s.find("~"));
	return "string_" + s.erase(0, 1);
}
std::string mark2useReg(std::string &s)
{
	for (auto i = 0; i < reg_t_max; i++)
	{
		if (curReg.t_content[i] == s)
			return "$t" + std::to_string(i);
	}
	for (auto i = 0; i < reg_s_max; i++)
	{
		if (curReg.s_content[i] == s)
			return "$s" + std::to_string(i);
	}
	return "0";
}

/* add _ before every global name to prevent iden like jal*/
void codeHead()
{
	mpb(".data");
	for (auto iter = ST::global_sym.begin(); iter != ST::global_sym.end(); iter++)
	{
		if (iter->second.type == ST::VAR_TYP && iter->second.cls == ST::CHA_CLS)
		{
			mpb("_" + iter->first + " : .byte 0");
			iter->second.addr = data_head;
			data_head += sizeof(char);
		}
		else if (iter->second.type == ST::ARRAY_TYP && iter->second.cls == ST::CHA_CLS)
		{
			mpb("_" + iter->first + " : .space " + std::to_string(iter->second.length));
			iter->second.addr = data_head;
			data_head += iter->second.length;
		}
	}
	data_head += 4 - data_head & 0x00000003;
	for (auto iter = ST::global_sym.begin(); iter != ST::global_sym.end(); iter++)
	{
		if (iter->second.type == ST::VAR_TYP && iter->second.cls == ST::INT_CLS)
		{
			mpb("_" + iter->first + " : .word 0");
			iter->second.addr = data_head;
			data_head += sizeof(int);
		}
		else if (iter->second.type == ST::ARRAY_TYP && iter->second.cls == ST::INT_CLS)
		{
			mpb("_" + iter->first + " : .space " + std::to_string(iter->second.length * sizeof(int)));
			iter->second.addr = data_head;
			data_head += iter->second.length * sizeof(int);
		}
	}
	for (auto iter = ST::output_str_sym.begin(); iter != ST::output_str_sym.end(); iter++)
	{
		mpb("string_" + std::to_string(iter->second) + " : .asciiz " + iter->first + "\"");
		data_head += iter->first.length();
	}
}

void funcbegin(mcode &c)
{
	assert(c.op == OP::FUNC_BEGIN);
	mpb((c.rst == "main" ? "" : "func_")+c.rst + ":");
}

void label(mcode &c)
{
	assert(c.op == OP::LABEL && !c.rst.find("%"));
	mpb(mark2label(c.rst) + ":");
}

void exit(mcode &c)
{
	assert(c.op == OP::EXIT);
	mpb("j exit");
}

void _goto(mcode &c)
{
	assert(c.op == OP::GOTO);
	mpb("j " + mark2label(c.rst));
}

void OC::Med2Mips()
{
	codeHead();
	mpb(".text");
	mpb(".globl main");
	for (auto i = Med::itmd_code.begin(); i != Med::itmd_code.end(); i++)
	{
		if (i->op == OP::FUNC_BEGIN)
			funcbegin(*i);
		else if (i->op == OP::LABEL)
			label(*i);
		else if (i->op == OP::EXIT)
			exit(*i);
		else if (i->op == OP::GOTO)
			_goto(*i);
	}
	mpb("exit:");
	bool putTab = false;
	std::ofstream mipsout("../mipsr.asm", std::ios::trunc | std::ofstream::ate);
	for (auto iter = mips.begin(); iter != mips.end(); iter++)
	{
		if ((*iter) == ".text")
		{
			putTab = true;
			mipsout << *iter << std::endl;
			continue;
		}
		if (putTab && (*iter) != ".globl main" && (*iter).find(':') == -1)
			mipsout << '\t';
		mipsout << *iter << std::endl;
	}
}