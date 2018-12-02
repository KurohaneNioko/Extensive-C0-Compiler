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

void Med::addIMC(std::string rst, std::string op, std::string op1, std::string op2)
{
	mcode t;
	t.num1 = op1;
	t.num2 = op2;
	t.op = op;
	t.rst = rst;
	Med::itmd_code.push_back(t);
}

int* Med::is_operand_num(std::string &s)
{
	int num;
	try
	{
		num = std::stoi(s);
	}
	catch (const std::out_of_range& oor)
	{
		num = INT_MAX;
		return &num;
	}
	catch (const std::invalid_argument& ia)
	{
		return nullptr;
	}
	return &num;
}