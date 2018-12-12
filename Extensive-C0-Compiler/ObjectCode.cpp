#include"ObjectCode.h"
#include<stack>

#if DEBUG
#define COMMENT 1
#else
#define COMMENT 0
#endif
std::string SW = "sw";
std::string LW = "lw";
std::string SB = "sb";
std::string LBU = "lbu";
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
typedef std::vector<mcode>::iterator ociter;
#define SSSS std::stringstream ss
// SSSS.Gridman !
#define mpss mpb(ss.str())
#define Down_Loop for (auto i = o + 1; i != Med::itmd_code.end(); i++)

int data_head = data_base;	// next data at
std::map<std::string, int> local_var_size;

#define FrameSize (curfunc == "main" ? ST::global_sym[curfunc].length * size_of_reg \
					: (ST::global_sym[curfunc].length * size_of_reg \
					+ local_var_size[curfunc] \
					+ size_of_reg * (reg_t_max + reg_s_max + 2)))
// 2 : ra sp
#define FS FrameSize
std::string curfunc = "";
int pushcount = 0;

runinfo curRI;
std::stack<runinfo> RIstack;

void assignAddr()
{
	for (auto i = ST::func_sym.begin(); i != ST::func_sym.end(); i++)
	{
		int addr = 0;
		for (auto j = i->second.begin(); j != i->second.end(); j++)
			if (j->second.type == ST::PARAM_TYP)
			{
				j->second.addr = addr;
				addr += size_of_reg;
			}
		for (auto j = i->second.begin(); j != i->second.end(); j++)
			if (j->second.cls == ST::CHA_CLS && j->second.type != ST::PARAM_TYP)
			{
				j->second.addr = addr;
				addr += (j->second.type == ST::VAR_TYP ? 1 : j->second.length);
			}
		addr += size_of_reg - addr & 0x00000003;
		for (auto j = i->second.begin(); j != i->second.end(); j++)
			if (j->second.cls == ST::INT_CLS && j->second.type != ST::PARAM_TYP)
			{
				j->second.addr = addr;
				addr += (j->second.type == ST::VAR_TYP ? 
					size_of_reg : j->second.length * size_of_reg);
			}
		local_var_size.insert(std::pair<std::string, int>(i->first, addr));
	}
}

std::string index2tempReg(int i)
{
	auto ret = i < reg_t_max ? "$t" + std::to_string(i) :
		"$s" + std::to_string(i - reg_t_max);
	if (ret == "$s8")
		ret = "$fp";
	return ret;
}

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
		if (curRI.ts_content[i] == s)
			return index2tempReg(i);
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

void modifyRegInfo(std::string &var, int &i)
{
	curRI.CLK_use[i] = true;
	curRI.ts_use[i] = true;
	curRI.ts_content[i] = var;
}
std::string regAppoint(std::string &var)
{
	// seek not-use-yet reg
	auto stop_pos = curRI.CLK_ptr;
	do
	{
		auto i = curRI.CLK_ptr;
		if (curRI.ts_content[i] == "")
		{
			curRI.CLK_ptr = nextRegIndex(i);
			modifyRegInfo(var, i);
#if COMMENT
			SSSS;
			ss << "# " << index2tempReg(i) << ": None -> " << var;
			mpss;
#endif
			return index2tempReg(i);
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
				modifyRegInfo(var, i);
#if COMMENT
				SSSS;
				ss << "# " << index2tempReg(i) << ": " << s << " -> " << var;
				mpss;
#endif
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
		modifyRegInfo(var, i);
#if COMMENT
		SSSS;
		ss << "# " << index2tempReg(i) << ": " << curRI.ts_content[i] << " -> " << var;
		mpss;
#endif
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
	varinfo *temp_id = ST::lookup(curfunc, iden, true);
	assert(temp_id != nullptr);
	auto reg = index2tempReg(i);
	if (ST::is_global_iden(curfunc, iden))
	{
		// global var, write it back (lazy)
		/// inavctive: i've written it when it was assigned.
		SSSS;
		ss << (temp_id->cls == ST::CHA_CLS ? SB : SW) << " " 
			<< reg << " " << mark2global_IDEN(iden);
		mpss;
	}
	else
	{
		// local var, write in stack
		auto addr = temp_id->addr;
		SSSS;
		ss << (temp_id->cls == ST::CHA_CLS ? SB : SW) << " "
			<< reg << " (-" << addr << ")" << SP;
		mpss;
	}
	modifyRegInfo(var, i);
#if COMMENT
	SSSS;
	ss << "# MemAccess " << index2tempReg(i) << ": "
		<< curRI.ts_content[i] << " -> " << var;
	mpss;
#endif
	return reg;
}

int reg2Index(std::string reg)
{
	assert(reg.length() >= 3 && *(reg.begin())=='$');
	if (reg[1] == 't')
		return reg[2] - '0';
	else if (reg[1] == 's')
		reg[2] - '0' + reg_t_max;
	else if (reg == "$fp")
		return reg_t_max + reg_s_max - 1;
	assert(false);
	return -1;
}

std::string regSeek(std::string &v, bool is_rsrt)
{	// if reg_t/s_max changed, modify here.
	auto lookup_ts = mark2useReg(v);
	if (lookup_ts != "0")
	{
		curRI.ts_use[reg2Index(lookup_ts)] = true;
		return lookup_ts;
	}
	auto rd = regAppoint(v);	// rd is the reg to be used
#if COMMENT
	SSSS;
	ss << "# now " << rd << " is " << v;
	mpss;
#endif
	if (!is_rsrt)
		return rd;
	if (curRI.symtab.count(v) > 0)
	{	// local var
		varinfo t = curRI.symtab[v];
		SSSS;
		ss << (t.type == ST::CHA_CLS ? LBU : LW) << " "
			<< rd << " (-" << std::to_string(t.addr) << ")" << SP;
		mpss;
	}
	else
	{	//global var
		assert(ST::global_sym.count(v) > 0);
		varinfo t = ST::global_sym[v];
		SSSS;
		ss << (t.type == ST::CHA_CLS ? LBU : LW) << " "
			<< rd << " " << mark2global_IDEN(v);
		mpss;
	}
	return rd;
}



void futureUseChk(std::string opr, std::string reg, ociter o)
{
	Down_Loop
	{
		if ((*i).op == OP::EXIT || (*i).op == OP::FUNC_END || (*i).rst == opr)
		{
			int idx = reg2Index(reg);
			curRI.ts_use[idx] = false;
			return;
		}
		if ((*i).num1 == opr || (*i).num2 == opr)
			return;
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
	curfunc = c.rst;
}

void label(mcode &c)
{
	assert(c.op == OP::LABEL && !c.rst.find("%"));
	mpb(mark2label(c.rst) + ":");
}

void exit(mcode &c)
{
	assert(c.op == OP::EXIT);
	mpb("j exit");		// alter: li + syscall
}

void _goto(mcode &c)
{
	assert(c.op == OP::GOTO);
	mpb("j " + mark2label(c.rst));
}

void push(mcode &c, ociter o)
{
	int offset = FS + pushcount * size_of_reg;
	auto save_reg = regSeek(c.num1, true);
	SSSS;
	ss << SW << " " << save_reg << " (-" << offset << ")" << SP;
	mpss;
	futureUseChk(c.num1, save_reg, o);
	++pushcount;
}

void call(mcode &c)
{
	pushcount = 0;	// ATTENTION
	int start = 0;
	
}

void OC::Med2Mips()
{
	codeHead();
	assignAddr();
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
