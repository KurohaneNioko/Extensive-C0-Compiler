#include"OptimzeHead.h"
std::vector<BB> blocks;
std::string OPT::optinfofile;
std::ofstream OPT::optout;
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
				int val =
					op == OP::ADD ? v1 + v2 :
					op == OP::SUB ? v1 - v2 :
					op == OP::MUL ? v1 * v2 :
					op == OP::DIV ? v1 / v2 : 0;
				it->op = OP::ADD;

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
					it->op = OP::ADD; it->num1 = it->num2; it->num2 = "0";
					combineFlag = true;
				}
				else if (v1 == 0 && (op == OP::DIV || op == OP::MUL))
				{
					it->op = OP::ADD; it->num1 = "0"; it->num2 = "0";
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
				it = Med::itmd_code.erase(it);	// don't worry about deleting the first
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
	OPT::optout << "Basic block info:" << std::endl;
	int j = 0;
	for (auto i = blocks.begin(); i != blocks.end(); i++, j++)
	{
		OPT::optout << j;
		if (!(i->prevBBno.empty()))
		{	
			OPT::optout << "  prev: ";
			for (auto t = i->prevBBno.begin(); t != i->prevBBno.end(); t++)
			{
				OPT::optout << *t << ' ';
			}
		}
		if (!(i->nextBBno.empty()))
		{
			OPT::optout << "  ";
			OPT::optout << "  next: ";
			for (auto t = i->nextBBno.begin(); t != i->nextBBno.end(); t++)
			{
				OPT::optout << *t << ' ';
			}
		}
		OPT::optout << std::endl;
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
			//(it-1)->BBno 
			if (!(bbcounter > (it - 1)->BBno))
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
			if (it + 1 != Med::itmd_code.end()/* && !(bbcounter > (it - 1)->BBno)*/)
				addBlock();

		}
		else
		{
			it->BBno = bbcounter;
		}
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
	if (c.op == OP::PUSH_PARA && c.num1 == var)
	{
		r.first = USE;
		r.second.insert(1);
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
decltype(Med::itmd_code.begin()) OPT::firstIRinBLK(const unsigned &blk_no)
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
void singleChainLocalVarSpread(std::map<std::string, int> def, bool &with_spread, const unsigned &currentblkNo)
{
	auto firstIR = OPT::firstIRinBLK(currentblkNo);
	auto lastIR = lastIRinBlock(currentblkNo);
	for (auto it = firstIR; it != lastIR + 1; it++)
	{
		for (auto varit = def.begin(); varit != def.end(); )
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
				varit++;
				break;
			}
			case(DEF):
			{
				auto def_var = def_place == 0 ? it->rst :
					def_place == 1 ? it->num1 : "";
				assert(def_var == varit->first);
				varit = def.erase(varit);
				//if (varit != def.begin())
					//varit--;
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
				//if (varit != def.begin())
					//varit--;
				break;
			}
			default:
				varit++;
				break;
			}
		}
	}
	for (auto nextblkiter = blocks[currentblkNo].nextBBno.begin();
		nextblkiter != blocks[currentblkNo].nextBBno.end();
		nextblkiter++)
	{
		auto next_blk = *nextblkiter;
		auto chekingblk = blocks[next_blk];
		if (chekingblk.prevBBno.size() == 1 && chekingblk.prevBBno.count(currentblkNo) == 1)
		{
			singleChainLocalVarSpread(def, with_spread, next_blk);
		}
	}
}
void naiveConstSpread(bool &with_spread)/* HARD! */
{
	unsigned blk_no = 0;
	for (auto blk_iter = blocks.begin(); blk_iter != blocks.end(); blk_iter++, blk_no++)
	{
		auto IRiter = OPT::firstIRinBLK(blk_no);
		auto lastIRiter = lastIRinBlock(blk_no);
		auto func_name = blk_iter->func_name;
		auto local_symtab = ST::func_sym[func_name];
		std::map<std::string, int> def;
		for (auto it = IRiter; it != lastIRiter+1; it++)
		{
			int val;	// const record
			if (it->op == OP::ADD && _opr_is_const(it->num1, val) && it->num2 == "0")
				def[it->rst] = val;
			else
			{	// spread every const value of var
				for (auto varit = def.begin(); varit != def.end();)
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
						varit++;
						break;
					}
					case(DEF):
					{
						auto def_var = def_place == 0 ? it->rst :
							def_place == 1 ? it->num1 : "";
						assert(def_var == varit->first);
						varit = def.erase(varit);
						//if(varit!=def.begin())
							//varit--;
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
						//if (varit != def.begin())
							//varit--;
						break;
					}
					default:
						varit++;
						break;
					}
				}
			}
		}
		// try to spread over BB
		// if current block's next block(s) has only one prev block(current block),
		// then i can spread local var, not global var (because of function call)
		auto localvar_def = def;		//get spreadable def set
		for (auto i = localvar_def.begin(); i != localvar_def.end();)
		{
			if (!(local_symtab.count(i->first)))
				i = localvar_def.erase(i);
			else i++;
		}
		for (auto nextblkiter = blk_iter->nextBBno.begin();
			nextblkiter != blk_iter->nextBBno.end();
			nextblkiter++)
		{
			auto next_blk = *nextblkiter;
			auto chekingblk = blocks[next_blk];
			if (chekingblk.prevBBno.size() == 1 && chekingblk.prevBBno.count(blk_no) == 1)
			{
				singleChainLocalVarSpread(def, with_spread, next_blk);
			}
		}
	}
}

std::vector<bool> checked_block;
void checkUseInblock(const std::string &var, bool &tobeused, const unsigned &block_no)
{
	auto block = blocks[block_no];
	auto firstIR = OPT::firstIRinBLK(block_no);
	auto lastIR = lastIRinBlock(block_no);
	for (auto i = firstIR; i != lastIR + 1; i++)
	{
		std::pair<int, std::set<int>> result;
		int def_place;
		useInIR(*i, var, result, def_place);
		if(result.first == USE || result.first == USE_DEF)
		{
			tobeused = true;
			break;
		}
		if (result.first == DEF)
			break;
	}
	if (!tobeused)
	{
		// lookup IR after this block
		auto after_block = block.nextBBno;
		for (auto nextblk_iter = after_block.begin();
			nextblk_iter != after_block.end();
			nextblk_iter++)
		{
			if (checked_block[*nextblk_iter] == false)
			{
				checked_block[*nextblk_iter] = true;
				checkUseInblock(var, tobeused, *nextblk_iter);
			}
			if (tobeused)
				break;
		}
	}
	
}
void deleteUnusedAssign()
{
	// don't touch global var, don't track scanf, impossible->rst is array
	// track use after def, track-def op = ADD, SUB, MUL, DIV, readarr
	unsigned blk_no = 0; std::string curfunc = "";
	for (auto blk_iter = blocks.begin(); blk_iter != blocks.end(); blk_iter++, blk_no++)
	{
		auto firstIR = OPT::firstIRinBLK(blk_no);
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
				std::vector<bool> temp(blocks.size(), false);
				checked_block = temp;
				bool to_be_used = false;
				// lookup IR after def
				for (auto j = i + 1; j != lastIR + 1; j++)
				{
					std::pair<int, std::set<int>> result;
					int def_place;
					useInIR(*j, checking_var, result, def_place);
					if (result.first == USE || result.first == USE_DEF)
					{
						to_be_used = true;
						break;
					}
				}
				if (!to_be_used)
				{	
					// lookup IR after this block
					auto after_block = blk_iter->nextBBno;
					for (auto nextblk_iter = after_block.begin();
						nextblk_iter != after_block.end();
						nextblk_iter++)
					{
						if (checked_block[*nextblk_iter] == false)
						{
							checked_block[*nextblk_iter] = true;
							checkUseInblock(checking_var, to_be_used, *nextblk_iter);
						}
						if (to_be_used)
							break;
					}
				}
				if (!to_be_used)
				{	/* WARNING: modify iterator */
					// delete this IR

					OPT::optout << "delete:" << std::endl;
					OPT::optout << std::right;
					OPT::optout << std::setw(14) << i->rst << "  " << std::setw(10) << i->op << "  "
						<< std::setw(14) << i->num1 << "  " << std::setw(14) << i->num2
#if OPTIMIZE
						<< std::setw(4) << i->BBno
#endif
						<< std::endl;
					i = Med::itmd_code.erase(i);
					firstIR = OPT::firstIRinBLK(blk_no);
					lastIR = lastIRinBlock(blk_no);
					// all IR's begin is func_begin, it won't be deleted! so i-- is ok
					i--;
				}
				// reset checked block info 
				std::vector<bool> temp1(blocks.size(), false);
				checked_block = temp1;
			}
		}

	}
}


bool is_func_simplevar(std::string &v, std::map<std::string, varinfo> &s)
{
	if (v == "RET_v0") return false;
	if (s.count(v))
		return s[v].type == ST::VAR_TYP || s[v].type == ST::PARAM_TYP;
	return false;
}
void initDUC(duc &temp, std::string &name, unsigned &defBBno, 
	decltype(Med::itmd_code.begin()) firstITER, decltype(Med::itmd_code.begin()) lastITER)
{
	temp.name = name;
	temp.defBB = defBBno;
	temp.defBBLine = std::distance(firstITER, lastITER);
	std::vector<struct use> uses; uses.clear();
	temp.useinfo = uses;
}
void insertUse(duc &temp, const unsigned &BBno,
	decltype(Med::itmd_code.begin()) firstITER, decltype(Med::itmd_code.begin()) lastITER)
{
	struct use use_elmt; use_elmt.BBno = BBno; use_elmt.BBLine = std::distance(firstITER, lastITER);
	temp.useinfo.push_back(use_elmt);
}
bool same_use_more_than1(duc &temp, const unsigned &BBno,
	decltype(Med::itmd_code.begin()) firstITER, decltype(Med::itmd_code.begin()) lastITER)
{
	unsigned cnt = 0;
	for (auto i = temp.useinfo.begin(); i != temp.useinfo.end(); i++)
	{
		if (i->BBLine == std::distance(firstITER, lastITER) && i->BBno == BBno)
			cnt++;
		if (cnt >= 2)
			return true;
	}
	return false;
}
std::map<std::string, std::map<std::string, std::vector<duc>>> OPT::func_DU;
void nextBB_DUWeb(duc &temp, const unsigned &currentBBno, std::vector<unsigned> walk_count)
{
	auto currentBB = blocks[currentBBno];
	auto firstIR = OPT::firstIRinBLK(currentBBno);
	auto lastIR = lastIRinBlock(currentBBno);
	bool current_blk_def = false;
	for (auto j = firstIR; j != lastIR + 1; j++)
	{
		std::pair<int, std::set<int>> usedef_code_place;
		int def_place;		// check use/def in IR
		useInIR(*j, temp.name, usedef_code_place, def_place);
		switch (usedef_code_place.first)
		{
		case(USE):
		{
			if (same_use_more_than1(temp, currentBBno, firstIR, j))
				return;
			else
				insertUse(temp, currentBBno, firstIR, j);
			break;
		}
		case(DEF):
		{
			current_blk_def = true;
			break;
		}
		case(USE_DEF):
		{
			if (!same_use_more_than1(temp, currentBBno, firstIR, j))
				insertUse(temp, currentBBno, firstIR, j);
			current_blk_def = true;
			break;
		}
		default:
			break;
		}
		if (current_blk_def) break;
	}
	walk_count[currentBBno]++ ;
	if (walk_count[currentBBno] == 2)
		return;
	if (!current_blk_def)
	{
		// search next block, recurrsive
		for (auto nextblkit = currentBB.nextBBno.begin();
			nextblkit != currentBB.nextBBno.end(); nextblkit++)
		{
			std::vector<unsigned> newvec = walk_count;
			if (newvec[*nextblkit] > 0)
				return;
			nextBB_DUWeb(temp, *nextblkit, newvec);
				
		}
	}
}
void DefUseWeb()
{
	std::map<std::string, std::vector<duc>> temp_func_DU;
	for (auto i = ST::func_sym.begin(); i != ST::func_sym.end(); i++)
	{
		std::vector<duc> temp;
		temp.clear();
		temp_func_DU.insert(std::pair<std::string, std::vector<duc>>(i->first, temp));
	}
	unsigned blk_no = 0;
	for (auto blk_iter = blocks.begin(); blk_iter != blocks.end(); blk_iter++, blk_no++)
	{
		auto firstIRiter = OPT::firstIRinBLK(blk_no);
		auto lastIRiter = lastIRinBlock(blk_no);
		auto func_name = blk_iter->func_name;
		auto local_symtab = ST::func_sym[func_name];
		// param!!!!
		if (firstIRiter->op == OP::FUNC_BEGIN)
		{
			std::set<std::string> params;
			for (auto i = ST::func_sym[func_name].begin(); i != ST::func_sym[func_name].end(); i++)
				if (i->second.type == ST::PARAM_TYP)
					params.insert(i->first);
			for (auto i = params.begin(); i != params.end(); i++)
			{
				std::string varname = *i;
				duc varduc;
				initDUC(varduc, varname, blk_no, firstIRiter, firstIRiter);
				auto IRiter = firstIRiter;
				// find use in current block until def
				bool current_blk_def = false;
				for (auto j = IRiter + 1; j != lastIRiter + 1; j++)
				{
					std::pair<int, std::set<int>> usedef_code_place;
					int def_place;		// check use/def in IR
					useInIR(*j, varname, usedef_code_place, def_place);
					switch (usedef_code_place.first)
					{
					case(USE):
					{
						insertUse(varduc, blk_no, firstIRiter, j);
						break;
					}
					case(DEF):
					{
						current_blk_def = true;
						break;
					}
					case(USE_DEF):
					{
						insertUse(varduc, blk_no, firstIRiter, j);
						current_blk_def = true;
						break;
					}
					default:
						break;
					}
					if (current_blk_def) break;
				}
				if (!current_blk_def)
				{
					// search next block, recurrsive
					for (auto nextblkit = blocks[blk_no].nextBBno.begin();
						nextblkit != blocks[blk_no].nextBBno.end(); nextblkit++)
					{
						std::vector<unsigned> newvec(blocks.size(), 0);
						nextBB_DUWeb(varduc, *nextblkit, newvec);
					}
				}
				temp_func_DU[func_name].push_back(varduc);
			}
		}
		// def : add/sub/mul/div readarr(rst) scan(num1), 
		// use : add/sub/mul/div savearr readarr print push cmp
		// ignore array/global/ret_v0
		for (auto IRiter = firstIRiter; IRiter != lastIRiter + 1; IRiter++)
		{
			auto op = IRiter->op;
			std::string varname;
			if (op == OP::ADD || op == OP::SUB || op == OP::MUL || op == OP::DIV || op == OP::READ_ARR)
				varname = IRiter->rst;
			else if (op == OP::SCAN)
				varname = IRiter->num1;
			else continue;
			if (!is_func_simplevar(varname, local_symtab)) continue;
			// find use in current block until def
			duc varduc;
			initDUC(varduc, varname, blk_no, firstIRiter, IRiter);
			bool current_blk_def = false;
			for (auto j = IRiter + 1; j != lastIRiter + 1; j++)
			{
				std::pair<int, std::set<int>> usedef_code_place;
				int def_place;		// check use/def in IR
				useInIR(*j, varname, usedef_code_place, def_place);
				switch (usedef_code_place.first)
				{
				case(USE):
				{
					insertUse(varduc, blk_no, firstIRiter, j);
					break;
				}
				case(DEF):
				{
					current_blk_def = true;
					break;
				}
				case(USE_DEF):
				{
					insertUse(varduc, blk_no, firstIRiter, j);
					current_blk_def = true;
					break;
				}
				default:
					break;
				}
				if (current_blk_def) break;
			}
			if (!current_blk_def)
			{
				// search next block, recurrsive
				for (auto nextblkit = blocks[blk_no].nextBBno.begin();
					nextblkit != blocks[blk_no].nextBBno.end(); nextblkit++)
				{
					std::vector<unsigned> newvec(blocks.size(), 0);
					nextBB_DUWeb(varduc, *nextblkit, newvec);
				}
			}
			temp_func_DU[func_name].push_back(varduc);
		}
	}
	// save by namne-du web in OPT::func_DU
	for (auto i = ST::func_sym.begin(); i != ST::func_sym.end(); i++)
	{
		std::map<std::string, std::vector<duc>> temp;
		temp.clear();
		OPT::func_DU.insert(std::pair<std::string, std::map<std::string, std::vector<duc>>>(i->first, temp));
	}
	for (auto i = ST::func_sym.begin(); i != ST::func_sym.end(); i++)
	{
		for (auto j = temp_func_DU[i->first].begin(); j != temp_func_DU[i->first].end(); j++)
		{
			if (!OPT::func_DU[i->first].count(j->name))
			{
				std::vector<duc> tempset;
				tempset.push_back(*j);
				OPT::func_DU[i->first].insert(std::pair<std::string, std::vector<duc>>(j->name, tempset));
			}
			else
			{
				OPT::func_DU[i->first][j->name].push_back(*j);
			}
		}
	}

}
void printDUweb()
{
	OPT::optout << "Def-Use Web" << std::endl;
	for (auto i = OPT::func_DU.begin(); i != OPT::func_DU.end(); i++)
	{
		OPT::optout << "====== " << i->first << " ======" << std::endl;;
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			OPT::optout << j->first << std::endl;
			for (auto k = j->second.begin(); k != j->second.end(); k++)
			{
				OPT::optout << k->defBB << ", " << k->defBBLine <<  std::endl;
				auto i = 0;
				for (auto s = k->useinfo.begin(); s != k->useinfo.end(); s++)
				{
					OPT::optout << '(' << s->BBno << ", " << s->BBLine << ") --> ";
					i++;
					if (i % 3 == 0) OPT::optout << std::endl;
				}
				OPT::optout << std::endl;
			}
			OPT::optout << std::endl;
		}
	}
}

bool is_crash(const std::string &var1, const std::string &var2, const std::string &func_name)
{
	assert(ST::func_sym[func_name].count(var1) != 0 &&
		ST::func_sym[func_name].count(var2) != 0 &&
		OPT::func_DU[func_name].count(var1) != 0 &&
		OPT::func_DU[func_name].count(var2) != 0);
	auto DU1 = OPT::func_DU[func_name][var1];
	auto DU2 = OPT::func_DU[func_name][var2];
	// def-use crash
	for (auto i = DU1.begin(); i != DU1.end(); i++)
	{
		auto defBBi = i->defBB; auto defBBL = i->defBBLine;
		for (auto j = DU2.begin(); j != DU2.end(); j++)
			for(auto k=j->useinfo.begin();k!=j->useinfo.end();k++)
				if (k->BBno == defBBi && k->BBLine == defBBL)
					return true;
	}
	for (auto i = DU2.begin(); i != DU2.end(); i++)
	{
		auto defBBi = i->defBB; auto defBBL = i->defBBLine;
		for (auto j = DU1.begin(); j != DU1.end(); j++)
			for (auto k = j->useinfo.begin(); k != j->useinfo.end(); k++)
				if (k->BBno == defBBi && k->BBLine == defBBL)
					return true;
	}
	// use-use crash
	for (auto i = DU1.begin(); i != DU1.end(); i++)
		for (auto is = i->useinfo.begin(); is != i->useinfo.end(); is++)
			for (auto j = DU2.begin(); j != DU2.end(); j++)
				for (auto js = j->useinfo.begin(); js != j->useinfo.end(); js++)
					if (is->BBLine == js->BBLine && is->BBno == js->BBno)
						return true;
	
	return false;
}
std::map<std::string, std::map<std::string, std::set<std::string>>> crashGraph;
void buildcrashGraph()
{
	for (auto i = OPT::func_DU.begin(); i != OPT::func_DU.end(); i++)
	{
		// i->second is var's DU of a function
		auto func_name = i->first;
		std::map<std::string, std::set<std::string>> temp;
		crashGraph.insert(
			std::pair<std::string, std::map<std::string, std::set<std::string>>>
			(func_name, temp)
		);
		std::vector<std::string> vars;
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			vars.push_back(j->first);
			std::set<std::string> t;
			crashGraph[func_name].insert(std::pair<std::string, std::set<std::string>>(j->first, t));
		}
		for (auto j = vars.begin(); j != vars.end(); j++)
		{
			auto var1 = *j;
			for (auto k = j+1; k != vars.end(); k++)
			{
				auto var2 = *k;
				if (is_crash(var1, var2, func_name))
				{
					crashGraph[func_name][var1].insert(var2);
					crashGraph[func_name][var2].insert(var1);
				}
			}
		}

	}
}
//print crash info
void printVarCrash()
{
	OPT::optout << std::endl << "Crash Graph" << std::endl;
	for (auto i = crashGraph.begin(); i != crashGraph.end(); i++)
	{
		OPT::optout << i->first << " ======" << std::endl;
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			OPT::optout << j->first << ':' << std::endl << "    ";
			for (auto k = j->second.begin(); k != j->second.end(); k++)
			{
				OPT::optout << *k << "  ";
			}
			OPT::optout << std::endl;
		}
		OPT::optout << std::endl;
	}
}
#define node_degree(x) (x.size())
void remove_node(const std::string &var, std::map<std::string, std::set<std::string>> &G)
{
	assert(G.count(var));
	for (auto i = G.begin(); i != G.end(); i++)
	{
		for (auto j = i->second.begin(); j != i->second.end(); )
		{
			if ((*j) == var)
				j = i->second.erase(j);
			else
				j++;
		}
	}
}
void regDistribute()
{
	std::size_t totalreg = reg_t_max + reg_s_max;
	auto cg = crashGraph;
	for (auto i = cg.begin(); i != cg.end(); i++)
	{
		std::stack<std::string> remove_small_degree;
		std::set<std::string> no_reg_var;
		func_name = i->first;
		while (1)
		{
			for (auto j = i->second.begin(); j != i->second.end(); )
			{
				if (node_degree(j->second) < totalreg)
				{
					remove_small_degree.push(j->first);
					remove_node(j->first, i->second);
					j = i->second.erase(j);
				}
				else
					j++;
			}
			if (i->second.size() == 0)
				break;
			if (i->second.size() > 0)	// some node degree too big
			{
				std::size_t max_degree = 0;
				std::string degree_max_node;
				for (auto j = i->second.begin(); j != i->second.end(); j++)
				{
					auto t = node_degree(j->second);
					if (t > max_degree)
					{
						max_degree = t;
						degree_max_node = j->first;
					}
				}
				no_reg_var.insert(degree_max_node);
				remove_node(degree_max_node, i->second);
			}
		}
		// now i get a stack and a set
		// use crashGraph to check if crash and use other reg
		if (remove_small_degree.size() <= totalreg)
		{
			for (auto i = remove_small_degree.size(); i > 0; i--)
			{
				std::string var = remove_small_degree.top();
				ST::func_sym[func_name][var].reg = i-1;
				remove_small_degree.pop();
			}
		}
		else {
			for (auto i = no_reg_var.begin(); i != no_reg_var.end(); i++)
				ST::func_sym[func_name][*i].reg = -6;	//no reg for it
			std::vector<int> distribute_count(totalreg, 0);
			for (auto i = remove_small_degree.size(); i > 0; i--)
			{
				std::string var = remove_small_degree.top();
				auto crashvar = crashGraph[func_name][var];
				std::vector<bool> available_reg(totalreg, true);
				for (auto j = crashvar.begin(); j != crashvar.end(); j++)
				{
					auto regno = ST::func_sym[func_name][*j].reg;
					if (regno>=0)
						available_reg[regno] = false;
				}
				// get least load reg
				int least_load = INT_MAX, leastload_no = -6;
				for(auto i=0;i< reg_t_max + reg_s_max;i++)
					if (distribute_count[i] < least_load && available_reg[i])
					{
						least_load = distribute_count[i];
						leastload_no = i;
					}
				ST::func_sym[func_name][var].reg = leastload_no;
				distribute_count[leastload_no]++;
				remove_small_degree.pop();
			}
		}
	}
}

void simplifyFunctionSymbolTable()
{
	for (auto i = ST::func_sym.begin(); i != ST::func_sym.end(); i++)
	{
		auto func_name = i->first;
		for (auto j = i->second.begin(); j != i->second.end(); )
		{
			if (j->second.type == ST::ARRAY_TYP || j->second.type == ST::CONST_TYP ||
				j->second.type == ST::FUN_TYP || j->second.type == ST::PARAM_TYP)
				j++;
			else
			{
				if (OPT::func_DU[func_name].count(j->first) == 0)
					j = i->second.erase(j);
				else
					j++;
			}
		}
	}

}

void OPT::allOptimize()
{
	//alg Simp, tregthReduce, then for each function, block & web
	OPT::optout.open(OPT::optinfofile, std::ios::trunc | std::ofstream::ate);
	if (!OPT::optout)
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

	deleteUnusedAssign();

	DivideBasicBlock();
	print_BB();
	OPT::optout << std::endl;

	Med::printIMC(OPT::optout);

	DefUseWeb();
	printDUweb();
	OPT::optout << std::endl;

	buildcrashGraph();
	printVarCrash();

	regDistribute();

	simplifyFunctionSymbolTable();
	
}