#include"ObjectCode.h"

#if DEBUG
#define COMMENT 1
#define MIPS_DEBUG 0
#else
#define COMMENT 0
#endif
const std::string SW = "sw";
const std::string LW = "lw";
const std::string SB = "sb";
const std::string LBU = "lbu";
const std::string LI = "li";
const std::string ADD = "add";
const std::string ADDI = "addi";
//const std::string SUBI = "subi";
const std::string SUB = "sub";
const std::string BEQ = "beq";
const std::string BNE = "bne";
const std::string BGE = "bge";
const std::string BGEZ = "bgez";
const std::string BGT = "bgt";
const std::string BGTZ = "bgtz";
const std::string BLE = "ble";
const std::string BLEZ = "blez";
const std::string BLT = "blt";
const std::string BLTZ = "bltz";
const std::string J = "j";
const std::string JAL = "jal";
const std::string JR = "jr";
const std::string MUL = "mul";
const std::string DIV = "div";
//const std::string MFLO = "mflo";
const std::string SYSCALL = "syscall";
const std::string LA = "la";
const std::string SLL = "sll";
const std::string MOVE = "move";
//const std::string ADDU = "addu";

const std::string ZERO = "$0";
const std::string V0 = "$v0";
const std::string A0 = "$a0";
//const std::string A1 = "$a1";
//const std::string A2 = "$a2";
//const std::string A3 = "$a3";

const std::string T8 = "$t8";
const std::string T9 = "$t9";
const std::string S8 = "$fp";

const std::string SP = "$sp";
const std::string RA = "$ra";

const std::string RETV0 = "RET_v0";
constexpr auto size_of_reg = 4;
std::vector<std::string> mips;
#define mpb mips.push_back
typedef std::vector<mcode>::iterator ociter;
#define SSSS std::stringstream ss
// SSSS.Gridman !
#define mpss mpb(ss.str())
int data_head = data_base;	// next data at
std::map<std::string, int> local_var_size;
std::string curfunc = "";
#define FrameSize (curfunc == "main" ? local_var_size[curfunc] \
					: (local_var_size[curfunc] \
					+ size_of_reg * (reg_t_max + reg_s_max + 1)))
// 2 : ra sp, if main with argv, FS of main should add params
// change 2 to 1: no need save SP
#define FS FrameSize
//int pushcount = 0;
runinfo curRI;

void assignAddr()
{
	for (auto i = ST::func_sym.begin(); i != ST::func_sym.end(); i++)
	{
		int addr = 0;
		for (auto param_count = 0; param_count < ST::global_sym[i->first].length; param_count++)
		{
			for (auto j = i->second.begin(); j != i->second.end(); j++)
				if (j->second.type == ST::PARAM_TYP && j->second.length == param_count)
				{
					j->second.addr = addr;
					addr += size_of_reg;
				}
		}
		for (auto j = i->second.begin(); j != i->second.end(); j++)
			if (j->second.cls == ST::CHA_CLS && j->second.type != ST::PARAM_TYP && j->second.type != ST::CONST_TYP)
			{
				j->second.addr = addr;
				addr += (j->second.type == ST::VAR_TYP ? 1 : j->second.length);
			}
		addr = addr + size_of_reg - (addr & 0x00000003);
		for (auto j = i->second.begin(); j != i->second.end(); j++)
			if (j->second.cls == ST::INT_CLS && j->second.type != ST::PARAM_TYP && j->second.type != ST::CONST_TYP)
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
std::string mark2func(std::string &s)
{
	return "func_" + s;
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
	runinfo t;
	for (auto i = 0; i < reg_t_max + reg_s_max; i++)
	{
		t.CLK_use[i] = false;
		t.ts_use[i] = false;
		t.ts_content[i] = "";
	}
	t.CLK_ptr = 0;
	t.symtab = ST::func_sym[curfunc];
	curRI = t;
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
	curRI.CLK_ptr = nextRegIndex(i);
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
#if COMMENT
		SSSS;
		ss << "# " << index2tempReg(i) << ": " << curRI.ts_content[i] << " -> " << var;
		mpss;
#endif
		modifyRegInfo(var, i);
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
	auto iden = curRI.ts_content[i];
	auto reg = index2tempReg(i); SSSS;
	if (curRI.symtab.count(iden) > 0)
	{	// local var, write in stack
		varinfo t = curRI.symtab[iden];
		auto addr = t.addr;
		ss << (t.cls == ST::CHA_CLS ? SB : SW) << " "
			<< reg << " -" << addr << " (" << SP << ")";
	}
	else
	{	// global var, write it back (lazy)
		/// inavctive: i've written it when it was assigned.
		assert(ST::global_sym.count(iden) > 0);
		varinfo t = ST::global_sym[iden];
		ss << (t.cls == ST::CHA_CLS ? SB : SW) << " "
			<< reg << " " << mark2global_IDEN(iden);
	}
	mpss;
#if COMMENT
	ss.str("");
	ss << "# MemAccess " << index2tempReg(i) << ": "
		<< curRI.ts_content[i] << " -> " << var;
	mpss;
#endif
	modifyRegInfo(var, i);
	return reg;
}

int reg2Index(std::string reg)
{
	assert(reg.length() >= 3 && *(reg.begin())=='$');
	if (reg[1] == 't')
		return reg[2] - '0';
	else if (reg[1] == 's')
		return reg[2] - '0' + reg_t_max;
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
	{	SSSS;
	ss << "# now " << rd << " is " << v;
	mpss; }
#endif
	if (!is_rsrt)
		return rd;
	SSSS;
	if (curRI.symtab.count(v) > 0)
	{	// local var
		varinfo t = curRI.symtab[v];
		ss << (t.cls == ST::CHA_CLS ? LBU : LW) << " "
			<< rd << " -" << (t.addr) << " (" << SP << ")";
	}
	else
	{	//global var
		//std::cout << v << " " << curfunc << std::endl;
		assert(ST::global_sym.count(v) > 0);
		varinfo t = ST::global_sym[v];
		ss << (t.cls == ST::CHA_CLS ? LBU : LW) << " "
			<< rd << " " << mark2global_IDEN(v);
	}
	mpss;
	return rd;
}

void futureUseChk(std::string opr, std::string reg, ociter o)
{
	if (*opr.begin() != '#')
	{
		int idx = reg2Index(reg);
		curRI.ts_use[idx] = false;
		curRI.ts_content[idx] = "";
		return;
	}
	auto i = o + 1;
	for (; i != Med::itmd_code.end(); i++)
	{
		if ((*i).op == OP::EXIT || (*i).op == OP::FUNC_END || (*i).rst == opr)
		{
			int idx = reg2Index(reg);
			curRI.ts_use[idx] = false;
			curRI.ts_content[idx] = "";
			return;
		}
		if ((*i).num1 == opr || (*i).num2 == opr
			|| ((*i).op == OP::SCAN && (*i).num1 == opr))
			return;
	}
	if (i == Med::itmd_code.end())
	{
		int idx = reg2Index(reg);
		curRI.ts_use[idx] = false;
	}
}

bool opr_is_const(std::string opr, int &rst)
{
	auto t = opr.begin();
	if (*(opr.begin()) == '\'')
	{
		rst = *(t + 1);
		return true;
	}
	int r = 0;
	try
	{
		r = std::stoi(opr);
	}
	catch (const std::exception&)
	{
		return false;
	}
	rst = r;
	return true;
}

void write2RAM(std::string iden, std::string reg)
{
	if (*(iden.begin()) != '#')
	{
		SSSS;
		if (curRI.symtab.count(iden) > 0)
		{	// local var
			varinfo t = curRI.symtab[iden];
			ss << (t.cls == ST::CHA_CLS ? SB : SW) << " "
				<< reg << " -" << (t.addr) << " (" << SP << ")";
		}
		else
		{	//global var
			//std::cout << v << " " << curfunc << std::endl;
			assert(ST::global_sym.count(iden) > 0);
			varinfo t = ST::global_sym[iden];
			ss << (t.cls == ST::CHA_CLS ? SB : SW) << " "
				<< reg << " " << mark2global_IDEN(iden);
		}
		mpss;
		curRI.ts_content[reg2Index(reg)] = "";
		curRI.ts_use[reg2Index(reg)] = false;
	}
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
	data_head += size_of_reg - data_head & 0x00000003;
	mpb(".align 2");
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
	initCurRI();

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
	int offset = FS + std::stoi(c.num2) * size_of_reg;
	int v;
	bool para_const = opr_is_const(c.num1, v);
	std::string save_reg; SSSS;
	if (para_const)
	{
		ss << LI << " " << T9 << " " << v;
		save_reg = T9;
		mpss;
		ss.str("");
	}
	else
	{
		save_reg = regSeek(c.num1, true);
		futureUseChk(c.num1, save_reg, o);
	}
	ss << SW << " " << save_reg << " -" << offset << " (" << SP << ")";
	mpss;
	//++pushcount;
#if COMMENT
	mpb("# push param: " + c.num1);
#endif // COMMENT

}

void call(mcode &c)
{
	assert(c.op == OP::CALL);
	mpb("# save start");
	int stack_ptr = FS + local_var_size[c.rst];
	/*	para |	FS = caller Frame size				para + local|	main Frame
		local|										-------------
		t0-s8|	current func's caller save them		para
		ra	 |	caller Frame						local
		------										t0-s8
		para |	callee Frame						ra
		local|										-------------
		t0-s8|	callee's caller save them			
		ra   |
	*/
	for (auto i = 0; i < reg_t_max + reg_s_max; i++)
		if(curRI.ts_use[i])
		{
			SSSS;
			ss << SW << " " << index2tempReg(i)
				<< " -" << stack_ptr << " (" << SP << ")";
			mpss;
			stack_ptr += size_of_reg;
		}

	stack_ptr = FS + local_var_size[c.rst] + size_of_reg * (reg_t_max + reg_s_max);
	{ SSSS; ss << SW << " " << RA << " -" << stack_ptr << " (" << SP << ")"; mpss; }
	stack_ptr += size_of_reg;
	//{ SSSS; ss << SW << " " << SP << " -" << stack_ptr << " (" << SP << ")"; mpss; }
	{ SSSS; ss << ADDI << " " << SP << " " << SP << " " << (-1 * FS); mpss; }
	{ SSSS; ss << JAL << " " << mark2func(c.rst); mpss; }
	mpb("# recover start");
	{SSSS; ss << ADDI << " " << SP << " " << SP << " " << FS; mpss; }
	stack_ptr -= size_of_reg;
	{ SSSS; ss << LW << " " << RA << " -" << stack_ptr << " (" << SP << ")"; mpss; }
	stack_ptr = FS + local_var_size[c.rst];
	for (auto i = 0; i < reg_t_max + reg_s_max; i++)
	{
		if (curRI.ts_use[i])
		{
			SSSS;
			ss << LW << " " << index2tempReg(i)
				<< " -" << stack_ptr << " (" << SP << ")";
			mpss;
			stack_ptr += size_of_reg;
		}
	}
	mpb("# recover end");
	//pushcount = 0;	// ATTENTION
}

void func_end_return(mcode &c)
{
	if (c.op == OP::FUNC_END) curfunc = "";
	{SSSS; ss << JR << " " << RA; mpss; }
}

void save_arr(mcode &c, ociter o)
{	// arr IRcode index val
	auto arr = c.rst,
		index = c.num1,
		value = c.num2; SSSS;
	varinfo arr_iden; bool local = false; int idx, val;
	bool const_index = opr_is_const(index, idx);
	bool const_value = opr_is_const(value, val);
	if (curRI.symtab.count(arr) > 0)
	{
		arr_iden = curRI.symtab[arr];
		local = true;
	}
	else
	{
		assert(ST::global_sym.count(arr) > 0);
		arr_iden = ST::global_sym[arr];
	}
	assert(arr_iden.type == ST::ARRAY_TYP);
	int elmt_size = 1; std::string SAVEcode = SB;
	if (arr_iden.cls == ST::INT_CLS)
	{
		elmt_size = size_of_reg;
		SAVEcode = SW;
	}
	else
		assert(arr_iden.cls == ST::CHA_CLS);

	int cases = (local ? 4 : 0) + (const_index ? 2 : 0) + (const_value ? 1 : 0);
	// local const_index const_value
	std::string valreg, idxreg;
	if (const_value)
	{
		ss << LI << ' ' << T9 << ' ' << val; mpss; ss.str("");
		valreg = T9;
	}
	else
		valreg = regSeek(value, true);
	if (local)
	{
		//	t t t: li $t9 val, sw/sb $t9 -(idx*size+addr)($sp)
		//  t t f: sw/sb valreg -idx*size+addr($sp)
		//  t f t: li $t9 val, sll $t8 idxreg log(2)(elmtsize), addi $t8 $t8 addr, sub $t8 $sp $t8, sw/sb $t9 $t8
		//  t f f: sll $t8 idxreg log(2)(size), addi $t8 $t8 addr, sub $t8 $sp $t8, sw/sb valreg ($t8)
		if (const_index)
		{
			ss << SAVEcode << ' ' << valreg << ' ' 
				<< -1 * (idx*elmt_size + arr_iden.addr) << " (" << SP << ")"; mpss;
		}
		else 
		{
			idxreg = regSeek(index, true);
			if (elmt_size > 1)
			{
				ss << SLL << ' ' << T8 << ' ' << idxreg << ' ' << int(log2(elmt_size)); mpss; ss.str("");
				ss << ADDI << ' ' << T8 << ' ' << T8 << ' ' << arr_iden.addr; mpss; ss.str("");
			}
			else
				ss << ADDI << ' ' << T8 << ' ' << idxreg << ' ' << arr_iden.addr; mpss; ss.str("");
			ss << SUB << ' ' << T8 << ' ' << SP << ' ' << T8; mpss; ss.str("");
			ss << SAVEcode << ' ' << valreg << ' ' << '(' << T8 << ')'; mpss; ss.str("");
		}
	}
	else
	{
		//  f t t: li $t9 val, sw/sb $t9 mark(arr)+idx*size
		//  f t f: sw/sb valreg mark(arr)+idx*size
		//  f f t: li $t9 val, sll $t8 idxreg log(2)(elmtsize), sw/sb $t9 mark(arr)($t8)
		//  f f f: sll $t8 idxreg log(2)(elmtsize) sw/sb valreg mark(arr)($t8)
		if (const_index)
		{
			ss << SAVEcode << ' ' << valreg << ' ' << mark2global_IDEN(arr) << '+' << idx * elmt_size; mpss;
		}
		else
		{
			idxreg = regSeek(index, true);
			if (elmt_size > 1)
			{
				ss << SLL << ' ' << T8 << ' ' << idxreg << ' ' << int(log2(elmt_size)); mpss; ss.str("");
			}
			ss << SAVEcode << ' ' << valreg << ' ' << mark2global_IDEN(arr)
				<< " (" << (elmt_size > 1 ? T8 : idxreg) << ")"; mpss; ss.str("");
		}
	}
	if (!const_index)
		futureUseChk(index, idxreg, o);
	if (!const_value)
		futureUseChk(value, valreg, o);
#if COMMENT
	{SSSS; ss << "# save array: " << arr << '[' << index << "] = " << value; mpss; }
#endif
}

void read_arr(mcode &c, ociter o)
{	// dst IRcode arr idx
	auto arr = c.num1, 
		index = c.num2, 
		dst = c.rst;
	varinfo arr_iden; bool local = false; int idx;
	bool const_index = opr_is_const(index, idx);
	std::string reg_index;
	if (curRI.symtab.count(arr) > 0)
	{
		arr_iden = curRI.symtab[arr];
		local = true;
	}
	else
	{
		assert(ST::global_sym.count(arr) > 0);
		arr_iden = ST::global_sym[arr];
	}
	assert(arr_iden.type == ST::ARRAY_TYP);
	int elmt_size = 1;
	if (arr_iden.cls == ST::INT_CLS)
		elmt_size = size_of_reg;
	else
		assert(arr_iden.cls == ST::CHA_CLS);	
	std::string rdreg;
	if (local)
	{
		/* local int idx-unknown:
		//		sll $t9 reg_index 2
		//		addi $t9 $t9 arr_iden.addr
		//		sub $t9 $sp $t9
		//		lw rdreg ($t9)
		// local char unknown:
		//		addi $t9 reg_index arr_iden.addr
		//		sub $t9 $sp $t9
		//		lbu rdreg ($t9)
		// local known:
		// lw/lbu rdreg -(arr_iden.addr + idx * elmt_size) $sp */
		SSSS;
		if (const_index)
		{
			rdreg = regSeek(dst, false);
			ss << (arr_iden.cls == ST::INT_CLS ? LW : LBU)
				<< " " << rdreg << " -" << arr_iden.addr + idx * elmt_size << "(" << SP << ")";
			mpss;
		}
		else
		{
			reg_index = regSeek(index, true);
			rdreg = regSeek(dst, false);
			if (arr_iden.cls == ST::INT_CLS)
			{
				ss << SLL << " " << T9 << " " << reg_index << ' ' << 2; mpss; ss.str("");
				ss << ADDI << " " << T9 << " " << T9 << " " << arr_iden.addr; mpss; ss.str("");
				ss << SUB << ' ' << T9 << ' ' << SP << ' ' << T9; mpss; ss.str("");
				ss << LW << ' ' << rdreg << ' ' << '(' << T9 << ')'; mpss; ss.str("");
			}
			else
			{
				ss << ADDI << " " << T9 << " " << reg_index << " " << arr_iden.addr; mpss; ss.str("");
				ss << SUB << ' ' << T9 << ' ' << SP << ' ' << T9; mpss; ss.str("");
				ss << LBU << ' ' << rdreg << ' ' << '(' << T9 << ')'; mpss; ss.str("");
			}
		}
	}
	else
	{
		/* global int unknown:
		//		sll $t9 reg_index 2
		//		lw rdreg arr($t9)
		// global char unknown:
		//		lbu rdreg arr(reg_index)
		// global known:
		// lw/lbu rdreg arr+ idx*elmt_size */
		SSSS;
		if (const_index)
		{
			rdreg = regSeek(dst, false);
			ss << (arr_iden.cls == ST::INT_CLS ? LW : LBU)
				<< " " << rdreg << " " << mark2global_IDEN(arr) << '+' << idx * elmt_size;
			mpss;
		}
		else
		{
			reg_index = regSeek(index, true);
			rdreg = regSeek(dst, false);
			if (arr_iden.cls == ST::INT_CLS)
			{
				ss << SLL << " " << T9 << " " << reg_index << ' '<< 2; mpss; ss.str("");
				ss << LW << ' ' << rdreg << ' ' << mark2global_IDEN(arr) << '(' << T9 << ')'; mpss; ss.str("");
			}
			else
				ss << LBU << ' ' << rdreg << ' ' << mark2global_IDEN(arr) << '(' << reg_index << ')'; mpss;
		}
	}
	write2RAM(c.rst, rdreg);
	if (!const_index)
		futureUseChk(index, reg_index, o);
#if COMMENT
	{SSSS; ss << "# read array: " << dst << " = " << arr << '[' << index << ']'; mpss; }
#endif
}

void calc(mcode &c, ociter o)
{
	auto r1 = c.num1, r2 = c.num2;
	int v1, v2;
	bool r1const = opr_is_const(r1, v1);
	bool r2const = opr_is_const(r2, v2);
	std::string r1reg, r2reg; SSSS;
	if (c.rst == RETV0)		// when optimize, don't touch anything about RETV0, 
	{
		if (r1const)	// li $v0 v1
			ss << LI << ' ' << V0 << ' ' << v1;
		else
		{	//move $v0 r1reg
			r1reg = regSeek(r1, true);
			ss << MOVE << ' ' << V0 << ' ' << r1reg;
			futureUseChk(r1, r1reg, o);
		}
		mpss;
		return;
	}
	std::string rdreg;
	if (r1 == RETV0)
	{
		rdreg = regSeek(c.rst, false);
		ss << MOVE << ' ' << rdreg << ' ' << V0;
		mpss;
		return;
	}
	if (r1const & r2const)
	{
		int val =
			c.op == OP::ADD ? v1 + v2 :
			c.op == OP::SUB ? v1 - v2 :
			c.op == OP::MUL ? v1 * v2 :
			c.op == OP::DIV ? v1 / v2 : 0;
		rdreg = regSeek(c.rst, false);
		if (val == 0)
			ss << ADD << ' ' << rdreg << ' ' << ZERO << ' ' << ZERO;
		else
			ss << LI << ' ' << rdreg << ' ' << val;
		mpss;
	}
	else if (!r1const & !r2const)
	{
		
		r1reg = regSeek(r1, true);
		r2reg = regSeek(r2, true);
		rdreg = regSeek(c.rst, false);
		auto o =
			c.op == OP::ADD ? ADD :
			c.op == OP::SUB ? SUB :
			c.op == OP::MUL ? MUL : DIV;
		ss << o << ' ' << rdreg << ' ' << r1reg << ' ' << r2reg; mpss;
	}
	else if (r1const & !r2const)
	{
		r2reg = regSeek(r2, true);
		if (v1 == 0)
		{
			rdreg = regSeek(c.rst, false);
			if (c.op == OP::ADD)
				ss << MOVE << ' ' << rdreg << ' ' << r2reg;
			else if (c.op == OP::SUB)
				ss << SUB << ' ' << rdreg << ' ' << ZERO << ' ' << r2reg;
			else if (c.op == OP::MUL || c.op == OP::DIV)
				ss << MOVE << ' ' << rdreg << ' ' << ZERO;
			else { assert(false); }
			mpss;
		}
		else
		{
			rdreg = regSeek(c.rst, false);
			if (c.op == OP::ADD)
				ss << ADD << ' ' << rdreg << ' ' << r2reg << ' ' << v1;
			else if (c.op == OP::SUB)
			{
				ss << SUB << ' ' << T9 << ' ' << r2reg << ' ' << v1; mpss; ss.str("");
				ss << SUB << ' ' << rdreg << ' ' << ZERO << ' ' << T9;
			}
			else if (c.op == OP::MUL)
			{
				ss << MUL << ' ' << rdreg << ' ' << r2reg << ' ' << v1;
			}
			else if (c.op == OP::DIV)
			{
				ss << LI << ' ' << T9 << ' ' << v1; mpss; ss.str("");
				ss << DIV << ' ' << rdreg << ' ' << T9 << ' ' << r2reg;
			}
			else { assert(false); }
			mpss;
		}
	}
	else if (!r1const & r2const)
	{
		r1reg = regSeek(r1, true);
		if (v2 == 0)
		{
			rdreg = regSeek(c.rst, false);
			if (c.op == OP::ADD || c.op == OP::SUB)
				ss << MOVE << ' ' << rdreg << ' ' << r1reg;
			else if (c.op == OP::MUL || c.op == OP::DIV)
				ss << MOVE << ' ' << rdreg << ' ' << ZERO;
			else { assert(false); }
			mpss;
		}
		else
		{
			rdreg = regSeek(c.rst, false);
			auto o =
				c.op == OP::ADD ? ADD :
				c.op == OP::SUB ? SUB :
				c.op == OP::MUL ? MUL : DIV;
			ss << o << ' ' << rdreg << ' ' << r1reg << ' ' << v2; mpss;
		}
	}
	else { assert(false); }
	write2RAM(c.rst, rdreg);
	if (!r1const)
		futureUseChk(c.num1, r1reg, o);
	if (!r2const)
		futureUseChk(c.num2, r2reg, o);
}

void cmp(mcode &c, ociter o)
{
	auto cop = c.op;
	auto r1 = c.num1, r2 = c.num2;
	int v1, v2;
	bool r1const = opr_is_const(r1, v1);
	bool r2const = opr_is_const(r2, v2);
	std::string r1reg, r2reg; SSSS;
	if (cop == OP::EQU || cop == OP::NEQ)
	{
		bool is_beq = cop == OP::EQU;
		if (r1const & r2const)
		{
			bool eq = v1 == v2;
			if(is_beq & eq || !is_beq & !eq)
				ss << J << " " << mark2label(c.rst);
			/* else do nothing: no jump */
		}
		else if (!r1const & r2const)
		{
			r1reg = regSeek(r1, true);
			ss << (is_beq ? BEQ : BNE) << " " << r1reg << " " <<
				v2 << " " << mark2label(c.rst);
		}
		else if (r1const & !r2const)
		{
			r2reg = regSeek(r2, true);
			ss << (is_beq ? BEQ : BNE) << " " << r2reg << " " <<
				v1 << " " << mark2label(c.rst);
		}
		else if (!r1const & !r2const)
		{
			r1reg = regSeek(r1, true);
			r2reg = regSeek(r2, true);
			ss << (is_beq ? BEQ : BNE) << " " << r1reg << " " <<
				r2reg << " " << mark2label(c.rst);
		}
	}
	else
	{
		if (r1const & r2const)
		{
			if((cop == OP::GRT && v1 > v2) ||
				(cop == OP::GREQ && v1 >= v2) ||
				(cop == OP::LES && v1 < v2) ||
				(cop == OP::LESEQ && v1 <= v2))
				ss << J << " " << mark2label(c.rst);
			/* else do nothing: no jump */
		}
		else if (!r1const & r2const)
		{
			r1reg = regSeek(r1, true);
			if (v2 == 0)
			{
				auto o = cop == OP::GRT ? BGTZ :
					cop == OP::GREQ ? BGEZ :
					cop == OP::LES ? BLTZ : BLEZ;
				ss << o << " " << r1reg << " " << mark2label(c.rst);
			}
			else
			{
				auto o = cop == OP::GRT ? BGT :
					cop == OP::GREQ ? BGE :
					cop == OP::LES ? BLT : BLE;
				ss << o << " " << r1reg << " " <<
					v2 << " " << mark2label(c.rst);
			}
		}
		else if (r1const & !r2const)
		{
			r2reg = regSeek(r2, true);
			if (v1 == 0)
			{	// 0 < $t0
				auto o = cop == OP::GRT ? BLTZ :
					cop == OP::GREQ ? BLEZ :
					cop == OP::LES ? BGTZ : BGEZ;
				ss << o << " " << r2reg << " " << mark2label(c.rst);
			}
			else
			{
				auto o = cop == OP::GRT ? BLT :
					cop == OP::GREQ ? BLE :
					cop == OP::LES ? BGT : BGE;
				ss << o << " " << r2reg << " " << v1 << " " << mark2label(c.rst);
			}
		}
		else if (!r1const & !r2const)
		{
			r1reg = regSeek(r1, true);
			r2reg = regSeek(r2, true);
			auto o = cop == OP::GRT ? BGT :
				cop == OP::GREQ ? BGE :
				cop == OP::LES ? BLT : BLE;
			ss << o << " " << r1reg << " " <<
				r2reg << " " << mark2label(c.rst);
		}
	}
	mpss;
	if(!r1const)
		futureUseChk(r1, r1reg, o);
	if(!r2const)
		futureUseChk(r2, r2reg, o);
}

void scan(mcode &c)
{
	SSSS;
	if (c.rst == "int")
		ss << LI << " " << V0 << ' ' << 5; 
	else
	{
		assert(c.rst == "char");
		ss << LI << " " << V0 << ' ' << 12;
	}
	mpss; ss.str("");
	ss << "syscall"; mpss; ss.str("");
	auto reg = regSeek(c.num1, false);
	ss << MOVE << ' ' << reg << ' ' << V0; mpss;
	write2RAM(c.num1, reg);
#if COMMENT
	{SSSS; ss << "# read " << c.rst << " " << c.num1; mpss; }
#endif // COMMENT
}

void print(mcode &c, ociter o)
{
	SSSS;
	if (c.rst == "int" || c.rst == "char")
	{	
		int val; bool is_const;
		ss << LI << " " << V0 << ' ' << (c.rst=="int"?1:11); mpss; ss.str("");
		is_const = opr_is_const(c.num1, val);
		if (is_const)
			ss << LI << ' ' << A0 << ' ' << val;
		else
		{
			auto reg = regSeek(c.num1, true);
			ss << MOVE << ' ' << A0 << ' ' << reg;
			futureUseChk(c.num1, reg, o);
		}
	}
	else
	{
		assert(c.rst == "str");
		ss << LI << " " << V0 << ' ' << 4; mpss; ss.str("");
		ss << LA << ' ' << A0 << ' ' << mark2string(c.num1);
	}
	mpss; ss.str("");
	ss << "syscall"; mpss; ss.str("");
#if COMMENT
	{SSSS; ss << "# print " << c.rst << " " << c.num1; mpss; }
#endif // COMMENT
}

void OC::Med2Mips(std::string mipsfile)
{
	codeHead();
	assignAddr();
	mpb(".text");
	mpb(".globl main");
	auto m = 0;
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
		else if (i->op == OP::PUSH_PARA)
			push(*i, i);
		else if (i->op == OP::CALL)
			call(*i);
		else if (i->op == OP::FUNC_END || i->op == OP::RET)
			func_end_return(*i);
		else if (i->op == OP::EQU || i->op == OP::NEQ ||
			i->op == OP::GRT || i->op == OP::GREQ ||
			i->op == OP::LES || i->op == OP::LESEQ)
			cmp(*i, i);
		else if (i->op == OP::ADD || i->op == OP::SUB ||
			i->op == OP::MUL || i->op == OP::DIV)
			calc(*i, i);
		else if (i->op == OP::SAVE_ARR)
			save_arr(*i, i);
		else if (i->op == OP::READ_ARR)
			read_arr(*i, i);
		else if (i->op == OP::SCAN)
			scan(*i);
		else if (i->op == OP::PRINT)
			print(*i, i);
		else
			assert(false);
#if MIPS_DEBUG
		bool putTab = false;
		for (; m != mips.size(); m++)
		{
			if (mips[m] == ".text")
			{
				putTab = true;
				std::cout << mips[m] << std::endl;
				continue;
			}
			if (putTab && mips[m] != ".globl main" && mips[m].find(':') == -1)
				std::cout << '\t';
			std::cout << mips[m] << std::endl;
		}
#endif
	}
	mpb("exit:");
	bool putTab = false;
#if INCLASS
	std::ofstream mipsout(mipsfile, std::ios::trunc | std::ofstream::ate);
#else
	std::ofstream mipsout("../mipsr.asm", std::ios::trunc | std::ofstream::ate);
#endif
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
