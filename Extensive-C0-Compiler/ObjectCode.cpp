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

std::string ZERO = "$0";
std::string V0 = "$v0";
std::string A0 = "$a0";
std::string A1 = "$a1";
std::string A2 = "$a2";
std::string A3 = "$a3";

std::string T8 = "$t8";
std::string T9 = "$t9";
std::string S8 = "$fp";

std::string SP = "$sp";
std::string RA = "$ra";

constexpr auto size_of_reg = 4;
std::vector<std::string> mips;
#define mpb mips.push_back
int data_head = data_base;	// next data at
auto curFunc = "";
runinfo curRI;
std::stack<runinfo> regstack;

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
	for (auto i = 0; i < reg_t_max + reg_s_max; i++)
	{
		if (curRI.ts_content[i] == s && i < reg_t_max)
			return "$t" + std::to_string(i);
		else if(curRI.ts_content[i] == s && i >= reg_t_max)
			return "$s" + std::to_string(i-reg_t_max);
	}
	return "0";
}
void initCurRI()
{
	memset(&curRI, 0, sizeof(curRI));
	for (auto i = 0; i < reg_t_max + reg_s_max; i++)
		curRI.ts_content[i] = "";
}
int nextRegIndex(int i)
{
	return i + 1 < reg_t_max + reg_s_max ? 
		i + 1 : 
		i + 1 - reg_t_max - reg_s_max;
}
std::string index2tempReg(int i)
{
	auto ret = i < reg_t_max ? "$t" + std::to_string(i) :
		"$s" + std::to_string(i - reg_t_max);
	if (ret == "$s8")
		ret = "$fp";
	return ret;
}
std::string regAppoint()
{
	// seek not-use-yet reg
	auto stop_pos = curRI.CLK_ptr;
	do
	{
		auto i = curRI.CLK_ptr;
		if (curRI.ts_content[i] == "")
		{
			auto ret = index2tempReg(i);
			curRI.CLK_ptr = nextRegIndex(curRI.CLK_ptr);
			return ret;
		}
		curRI.CLK_ptr = nextRegIndex(curRI.CLK_ptr);
	} while (curRI.CLK_ptr != stop_pos);

	// seek won't be used reg
	std::set<int> unuse_reg;
	stop_pos = curRI.CLK_ptr;
	do
	{
		auto i = curRI.CLK_ptr;
		if (curRI.ts_use[i] == false)
		{
			auto s = curRI.ts_content[i];
			if (*(s.begin()) == '#')
			{
				return index2tempReg(i);
			}
			unuse_reg.insert(i);
		}
		curRI.CLK_ptr = nextRegIndex(curRI.CLK_ptr);
	} while (curRI.CLK_ptr != stop_pos);
	if (!unuse_reg.empty())
	{
		auto i = *unuse_reg.begin();
		curRI.CLK_ptr = nextRegIndex(i);
		return index2tempReg(i);
	}

	// use clock algorithm to find a var to change
	while (curRI.CLK_use[curRI.CLK_ptr] != false)
	{
		if (curRI.CLK_use[curRI.CLK_ptr] == true)
		{
			curRI.CLK_use[curRI.CLK_ptr] = false;
		}
		curRI.CLK_ptr = nextRegIndex(curRI.CLK_ptr);
	}
	auto i = curRI.CLK_ptr;
	curRI.CLK_ptr = nextRegIndex(curRI.CLK_ptr);
	auto iden = curRI.ts_content[i];
	varinfo *temp_id = ST::lookup(curFunc, iden, true);
	if (ST::is_global_iden(curFunc, iden))
	{
		// global var, no need to write it back
		// i've written it when it was assigned.
	}
	else
	{
		// local var, write in stack
		varinfo v;
		v.name = iden;
		v.cls = ST::INT_CLS;
		v.type = ST::VAR_TYP;
		v.length = 0;
		if (temp_id == nullptr)
		{	// var not in symtab
			curRI.symtab.insert(std::pair<std::string, varinfo>(iden, v));
		}
		// find a place in stack for iden and modify addr in symtab
		auto find = false;
		auto offset = 0;
		while (find!=false)
		{
			auto i = curRI.symtab.begin();
			for (; i != curRI.symtab.end(); i++)
				if (i->second.addr == offset)
				{
					if (i->second.type == ST::VAR_TYP || i->second.type == ST::PARAM_TYP)
						offset += 4;
					else
					{	//array
						auto size = i->second.cls == ST::CHA_CLS ? 1 : 4;
						offset += size * i->second.length;
						offset += size_of_reg - offset & 0x00000003;
					}
					break;
				}
			if (i == curRI.symtab.end())
			{	// look up current offset and find no use
				find = true;
				if (offset >= curRI.frame_size)
					curRI.frame_size += 4;
			}
		}
		curRI.symtab[iden].addr = offset;
		/* sw index2Reg(i) ( "-"+std::to_string(offset) )$sp */
		mpb("sw " + index2tempReg(i) + " (-" + std::to_string(offset) + ")" + SP);
	}
}

/*	meet IDEN in IMC:
	check in local
		if find==null
			use mark2global_IDEN
		else find its use reg
			if reg=="0"
				find a new reg for it and modify curReg
*/

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
	data_head += size_of_reg - data_head & 0x00000003;
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

void reg_appoint()
{
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
}

void s8_fp()
{
	const std::string from = "$8", to = "$fp";
	for (auto i = mips.begin(); i != mips.end(); i++)
	{
		std::size_t start = 0;
		while ((start = (*i).find(from, start)) != std::string::npos)
		{
			(*i).replace(start, from.length(), to);
			start += to.length();
		}
	}
}