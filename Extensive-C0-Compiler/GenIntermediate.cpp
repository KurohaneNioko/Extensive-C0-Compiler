#include "Intermediate.h"

std::vector<mcode> Med::itmd_code;

int Med::temp_order = 0;
int label_order = 0;
int str_order = 0;

std::string Med::gen_temp(std::string &curFunc, int &lc, int cls)
{
	assert(cls == ST::INT_CLS || cls == ST::CHA_CLS);
	auto name = Med::temphd + std::to_string(++temp_order);
	ST::addsym(curFunc, name, cls, ST::VAR_TYP, 0, lc);
	return name;
}

std::string Med::gen_label()
{
	return Med::labelhd + std::to_string(++label_order);
}

/*std::string Med::gen_str()
{
	return Med::strhd + std::to_string(++str_order);
}*/

void Med::addIMC(std::string rst, const std::string &op, std::string op1, std::string op2)
{
	mcode t;
	t.num1 = op1;
	t.num2 = op2;
	t.op = op;
	t.rst = rst;
	Med::itmd_code.push_back(t);
}

bool Med::is_operand_num(std::string &s, int &value)
{
	int num;
	try
	{
		num = std::stoi(s);
	}
	catch (const std::out_of_range&)
	{
		value = INT_MAX;
		return false;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
	value = num;
	return true;
}

void Med::printIMC(std::ofstream&o)
{
	for(auto iter = itmd_code.begin(); iter!= itmd_code.end(); iter++)
	{
		o << std::right;
		o << std::setw(14) << iter->rst << "  " << std::setw(10) << iter->op << "  "
			<< std::setw(14) << iter->num1 << "  " << std::setw(14) << iter->num2 
#if OPTIMIZE
			<< std::setw(4) << iter->BBno
#endif
			<< std::endl;
	}
}