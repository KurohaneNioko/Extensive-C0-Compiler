#include"OptimzeHead.h"
std::vector<BB> blocks;
std::string OPT::optinfofile;
std::ofstream optout;
//const combine: implement by ObjCode
bool _opr_is_const(std::string opr, int &rst)
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
bool combineFlag = false, algSimpFlag = false;
void constCombine()
{
	combineFlag = false;
	for (auto it = Med::itmd_code.begin(); it != Med::itmd_code.end(); it++)
	{
		if (it->op == OP::ADD || it->op == OP::SUB || it->op == OP::MUL || it->op == OP::DIV)
		{
			auto op = it->op;
			if (it->num2 == "0" && it->op == OP::ADD)
				continue;
			auto r1 = it->num1, r2 = it->num2;
			int v1, v2;
			bool r1const = _opr_is_const(r1, v1);
			bool r2const = _opr_is_const(r2, v2);
			if (r1const & r2const)
			{
				it->op = OP::ADD;
				int val =
					op == OP::ADD ? v1 + v2 :
					op == OP::SUB ? v1 - v2 :
					op == OP::MUL ? v1 * v2 :
					op == OP::DIV ? v1 / v2 : 0;
				it->num1 = std::to_string(val);
				it->num2 = "0";
				combineFlag = true;
			}
			else if (!r1const & r2const)
			{
				if ((op == OP::SUB && v2 == 0) ||
					((op == OP::MUL || op == OP::DIV) && v2 == 1))
				{
					it->op = OP::ADD; it->num2 = "0";
					combineFlag = true;
				}
			}
			else if (r1const & !r2const)
			{
				if ((v1 == 0 && op == OP::ADD) || (v1 == 1 && op == OP::MUL))
				{
					it->op == OP::ADD; it->num1 = it->num2; it->num2 = "0";
					combineFlag = true;
				}
				else if (v1 == 0 && (op == OP::DIV || op == OP::MUL))
				{
					it->op == OP::ADD; it->num1 = "0"; it->num2 = "0";
					combineFlag = true;
				}
			}

		}
	}
}
void algebraSimplify()
{
	/* TODO: kill x = x +0, -0, *1, /1  */
	for (auto it = Med::itmd_code.begin(); it != Med::itmd_code.end(); it++)
	{
		if (it->op == OP::ADD || it->op == OP::SUB || it->op == OP::MUL || it->op == OP::DIV)
		{
			int v1, v2; auto r1 = it->num1, r2 = it->num2, rst = it->rst;
			bool r1const = _opr_is_const(r1, v1);
			bool r2const = _opr_is_const(r2, v2);
			// +0 -0 0+ *1 /1 1*
			if ((r1const && !r2const && v1 == 0 && r2 == rst && it->op == OP::ADD) ||
				(!r1const && r2const && v2 == 0 && r1 == rst && (it->op == OP::ADD || it->op == OP::SUB)) ||
				(r1const && !r2const && v1 == 1 && r2 == rst && it->op == OP::MUL) ||
				(!r1const && r2const && v2 == 1 && r1 == rst && (it->op == OP::MUL || it->op == OP::DIV)))
			{
				it = Med::itmd_code.erase(it);
				if(it!=Med::itmd_code.begin())
					it--;
			}
		}
	}
}
void strengthReduce()/* NO NEED! +,-,*,/=>count=1  */
{
	/* TODO: -1*x, x*-1, x/-1 => sub 0 x
		left 4 ObjCode: (2^n, n>=1)*x,  */

}

void print_BB()
{
	optout << "Basic block info:" << std::endl;
	int j = 0;
	for (auto i = blocks.begin(); i != blocks.end(); i++, j++)
	{
		optout << j;
		if (!(i->prevBBno.empty()))
		{	
			optout << "  prev: ";
			for (auto t = i->prevBBno.begin(); t != i->prevBBno.end(); t++)
			{
				optout << *t << ' ';
			}
		}
		if (!(i->nextBBno.empty()))
		{
			optout << "  ";
			optout << "  next: ";
			for (auto t = i->nextBBno.begin(); t != i->nextBBno.end(); t++)
			{
				optout << *t << ' ';
			}
		}
		optout << std::endl;
	}
}
int bbcounter = -1;
std::string func_name = "";
void addBlock()
{
	BB blk;
	blk.func_name = func_name;
	blocks.push_back(blk);
	bbcounter++;
}
auto lastIRinBlock(unsigned blkcnt)
{
	assert(blkcnt < blocks.size());
	for (auto i = Med::itmd_code.begin(); i != Med::itmd_code.end(); i++)
	{
		if (i->BBno == blkcnt)
		{
			auto j = i;
			for (; j != Med::itmd_code.end(); j++)
				if (j->BBno != blkcnt)
					break;
			return (j - 1);
		}
	}
	return (Med::itmd_code.end()-1);
}
int labelBlockNo(const std::string &labelname)
{
	for (auto i = Med::itmd_code.begin(); i != Med::itmd_code.end(); i++)
	{
		if (i->op == OP::LABEL && i->rst == labelname)
			return i->BBno;
	}
	return -1;
}
void DivideBasicBlock()
{
	/* TODO: start at func_begin, stop at func_end
		cut after call / label / compare / goto / exit / return  */
	blocks.clear(); bbcounter = -1;
	for (auto it = Med::itmd_code.begin(); it != Med::itmd_code.end(); it++)
	{
		if (it->op == OP::LABEL)
		{
			addBlock();
			it->BBno = bbcounter;
		}
		else if (it->op == OP::FUNC_BEGIN)
		{
			func_name = it->rst;
			addBlock();
			it->BBno = bbcounter;
		}
		else if (it->op == OP::EXIT || it->op == OP::CALL || it->op == OP::GOTO || it->op == OP::RET ||
			it->op == OP::EQU || it->op == OP::NEQ || it->op == OP::GRT || it->op == OP::GREQ ||
			it->op == OP::LES || it->op == OP::LESEQ)
		{
			it->BBno = bbcounter;
			if (it + 1 != Med::itmd_code.end())
				addBlock();

		}else
			it->BBno = bbcounter;
	}
	func_name = "";
	//connect
	int j = 0;
	for (auto i = blocks.begin(); i != blocks.end(); i++,j++)
	{
		const mcode m = *(lastIRinBlock(j));
		auto op = m.op;
		if (op == OP::EQU || op == OP::NEQ || op == OP::GRT || op == OP::GREQ ||
			op == OP::LES || op == OP::LESEQ)
		{
			if (j != blocks.size() - 1)	// it's not last block(has natrue next), BLOCK j+1 is next
			{
				i->nextBBno.insert(j + 1);
				blocks[j+1].prevBBno.insert(j);
			}
			int jumpblock = labelBlockNo(m.rst);
			assert(jumpblock != -1);
			i->nextBBno.insert(jumpblock);
			blocks[jumpblock].prevBBno.insert(j);
			
		}
		else if (op == OP::GOTO)
		{
			int jumpblock = labelBlockNo(m.rst);
			assert(jumpblock != -1);
			i->nextBBno.insert(jumpblock);
			blocks[jumpblock].prevBBno.insert(j);
		}
		else if (op == OP::EXIT || op == OP::RET || op==OP::FUNC_END)
		{

		}
		else
		{
			if (j != blocks.size() - 1)	// it's not last block(has natrue next), BLOCK j+1 is next
			{
				i->nextBBno.insert(j + 1);
				blocks[j + 1].prevBBno.insert(j);
			}
		}
	}
}

#define NO_USE 0
#define USE 1
#define DEF   -1
#define USE_DEF 2
// 0 no use&no def,  1 in use,  -1 def,  2 use&def
// 0->rst, 1->num1, 2->num2, -1->NULL
void useInIR(const mcode &c, const std::string &var, std::pair<int, std::set<int>> &r, int &def_place)
{
	def_place = -1;
	r.first = NO_USE;
	if (c.op == OP::PUSH_PARA && c.rst == var)
	{
		r.first = USE;
		r.second.insert(0);
	}
	else if (c.op == OP::SCAN && c.num1 == var)
	{
		r.first = DEF;
		def_place = 1;
	}
	else if (c.op == OP::SAVE_ARR && (c.num1 == var || c.num2 == var))
	{
		r.first = USE;
		if (c.num1 == var)
			r.second.insert(1);
		if (c.num2 == var)
			r.second.insert(2);
	}
	else if (c.op == OP::READ_ARR && c.num2 == var && c.rst != var)
	{
		r.first = USE;
		r.second.insert(2);
	}
	else if (c.op == OP::READ_ARR && c.num2 != var && c.rst == var)
	{
		r.first = DEF;
		def_place = 0;
	}
	else if (c.op == OP::READ_ARR && c.num2 == var && c.rst == var)
	{
		r.first = USE_DEF;
		def_place = 0;
		r.second.insert(2);
	}
	else if (c.op == OP::ADD || c.op == OP::SUB || c.op == OP::MUL || c.op == OP::DIV || c.op==OP::PRINT ||
		c.op == OP::EQU || c.op == OP::NEQ || c.op == OP::GRT || c.op == OP::GREQ || 
		c.op == OP::LES || c.op == OP::LESEQ)
	{
		if (c.rst != var && (c.num1 == var || c.num2 == var))
		{
			r.first = USE;
			if (c.num1 == var)
				r.second.insert(1);
			if (c.num2 == var)
				r.second.insert(2);
		}
		if (c.rst == var && !(c.num1 == var || c.num2 == var))
		{
			r.first = DEF;
			def_place = 0;
		}
		if (c.rst == var && (c.num1 == var || c.num2 == var))
		{
			r.first = USE_DEF;
			if (c.num1 == var)
				r.second.insert(1);
			if (c.num2 == var)
				r.second.insert(2);
		}
	}
}
auto firstIRinBLK(unsigned &blk_no)
{
	assert(blk_no < blocks.size());
	auto i = Med::itmd_code.begin();
	for (; i != Med::itmd_code.end(); i++)
	{
		if (i->BBno == blk_no)
			return i;
	}
	return i;
}
void naiveConstSpread(bool &with_spread)/* HARD! */
{
	unsigned blk_no = 0;
	for (auto blk_iter = blocks.begin(); blk_iter != blocks.end(); blk_iter++, blk_no++)
	{
		auto IRiter = firstIRinBLK(blk_no);
		auto lastIRiter = lastIRinBlock(blk_no);
		std::map<std::string, int> def;
		for (auto it = IRiter; it != lastIRiter+1; it++)
		{
			int val;	// const record
			if (it->op == OP::ADD && _opr_is_const(it->num1, val) && it->num2 == "0")
				def[it->rst] = val;
			else
			{	// spread every const value of var
				for (auto varit = def.begin(); varit != def.end(); varit++)
				{
					//travel var-value set
					std::pair<int, std::set<int>> usedef_code_place;
					int def_place;		// check use/def in IR
					useInIR(*it, varit->first, usedef_code_place, def_place);
					switch (usedef_code_place.first)
					{
					case(USE):
					{
						for (auto replace_iter = usedef_code_place.second.begin();
							replace_iter != usedef_code_place.second.end();
							replace_iter++)
						{
							if (*replace_iter == 0)
								it->rst = std::to_string(varit->second);
							if (*replace_iter == 1)
								it->num1 = std::to_string(varit->second);
							if (*replace_iter == 2)
								it->num2 = std::to_string(varit->second);
						}
						with_spread = true;
						break;
					}
					case(DEF):
					{
						auto def_var = def_place == 0 ? it->rst :
							def_place == 1 ? it->num1 : "";
						assert(def_var == varit->first);
						varit = def.erase(varit);
						if(varit!=def.begin())
							varit--;
						break;
					}
					case(USE_DEF):
					{
						for (auto replace_iter = usedef_code_place.second.begin();
							replace_iter != usedef_code_place.second.end();
							replace_iter++)
						{
							if (*replace_iter == 0)
								it->rst = std::to_string(varit->second);
							if (*replace_iter == 1)
								it->num1 = std::to_string(varit->second);
							if (*replace_iter == 2)
								it->num2 = std::to_string(varit->second);
						}
						with_spread = true;
						auto def_var = def_place == 0 ? it->rst :
							def_place == 1 ? it->num1 : "";
						assert(def_var == varit->first);
						varit = def.erase(varit);
						if (varit != def.begin())
							varit--;
					}
					default:
						break;
					}
				}
				
			}
		}
	}
}

std::vector<bool> checked_block(blocks.size(), false);
void checkUseInblock(const std::string &var)
{

}
void deleteUnusedAssign()
{
	// don't touch global var, don't track scanf, impossible->rst is array
	// track use after def, track-def op = ADD, SUB, MUL, DIV, readarr
	unsigned blk_no = 0; std::string curfunc = "";
	for (auto blk_iter = blocks.begin(); blk_iter != blocks.end(); blk_iter++, blk_no++)
	{
		auto firstIR = firstIRinBLK(blk_no);
		if (firstIR->op == OP::FUNC_BEGIN)
			curfunc = firstIR->rst;
		auto func_sym = ST::func_sym[curfunc];
		auto lastIR = lastIRinBlock(blk_no);
		for (auto i = firstIR; i != lastIR + 1; i++)
		{
			if ((i->op == OP::ADD || i->op == OP::SUB || i->op == OP::MUL || i->op == OP::DIV || 
					i->op == OP::READ_ARR))
			{
				// get to-be-checked var
				auto checking_var = i->rst;
				if (func_sym.count(checking_var) == 0)
					continue;
				bool to_be_use = false;
				// lookup IR after def
				for (auto j = i + 1; j != lastIR + 1; j++)
				{
					std::pair<int, std::set<int>> result;
					int def_place;
					useInIR(*j, checking_var, result, def_place);
					if (result.first == USE || result.first == USE_DEF)
					{
						to_be_use = true;
						break;
					}
				}
				if (!to_be_use)
				{	
					// lookup IR after this block
					//for()
				}
				if (!to_be_use)
				{
					// delete this IR
				}
				// reset checked block info 
			}
		}

	}
}

void localDAG()
{

}

void DefUseWeb()
{

}

void OPT::allOptimize()
{
	//alg Simp, tregthReduce, then for each function, block & web
	// dag if have time
	optout.open(OPT::optinfofile, std::ios::trunc | std::ofstream::ate);
	if (!optout)
	{
		std::cout << "optIfo open failed";
		system("pause");
		exit(-1);
	}
	bool with_spread = false;
	do
	{
		with_spread = false;
		algebraSimplify();
		constCombine();
		DivideBasicBlock();
		naiveConstSpread(with_spread);
	} while (with_spread);



	print_BB();

	optout << std::endl;
	Med::printIMC(optout);
	if (optout.is_open())
	{
		optout.close();
	}
}