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
void constCombine()	/* USELESS */
{

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
void constSpread()/* HARD! */
{
	
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
			return *(j - 1);
		}
	}
	return *(Med::itmd_code.end()-1);
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
		const mcode m = lastIRinBlock(j);
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
	print_BB();
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
	constCombine();
	algebraSimplify();
	DivideBasicBlock();

	if (optout.is_open())
	{
		optout.close();
	}
}