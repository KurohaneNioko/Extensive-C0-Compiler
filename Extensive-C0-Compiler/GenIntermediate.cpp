#include "Intermediate.h"

std::vector<mcode> Med::itmd_code;

int temp_order = 0;
int label_order = 0;
int str_order = 0;

std::string Med::gen_temp()
{
	return Med::temphd + std::to_string(++temp_order);
}

std::string Med::gen_label()
{
	return Med::labelhd + std::to_string(++label_order);
}

std::string Med::gen_str()
{
	return Med::strhd + std::to_string(++str_order);
}

void Med::addIMC(std::string rst, const std::string &op, std::string op1, std::string op2)
{
	mcode t;
	t.num1 = op1;
	t.num2 = op2;
	t.op = op;
	t.rst = rst;
	Med::itmd_code.push_back(t);
}

void Med::is_operand_num(std::string &s, int *value)
{
	int num;
	try
	{
		num = std::stoi(s);
	}
	catch (const std::out_of_range&)
	{
		*value = INT_MAX;
		return;
	}
	catch (const std::invalid_argument&)
	{
		value = nullptr;
		return;
	}
	*value = num;
}

void Med::printIMC()
{
	for(auto iter = itmd_code.begin(); iter!= itmd_code.end(); iter++)
	{
		std::cout << std::right;
		std::cout << std::setw(14) << iter->rst << "  " << std::setw(10) << iter->op << "  "
			<< std::setw(14) << iter->num1 << "  " << std::setw(14) << iter->num2 << std::endl;
	}
}