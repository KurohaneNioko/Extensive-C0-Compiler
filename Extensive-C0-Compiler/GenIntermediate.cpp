#include "Intermediate.h"

std::vector<mcode> Med::itmd_code;

int temp_order = 0;
int label_order = 0;
int str_order = 0;

std::string gen_temp()
{
	return Med::temphd + std::to_string(++temp_order);
}

std::string gen_label()
{
	return Med::labelhd + std::to_string(++label_order);
}

std::string gen_str()
{
	return Med::strhd + std::to_string(++str_order);
}

