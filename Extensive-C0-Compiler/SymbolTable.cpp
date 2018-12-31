#include "SymbolHead.h"
std::map<std::string, varinfo> ST::global_sym;
std::map<std::string, std::map<std::string, varinfo>> ST::func_sym;
std::map<std::string, int> ST::output_str_sym;

varinfo* ST::lookup(const std::string &curFunc, const std::string &name, bool local)
{
	if (curFunc != "")	// local
	{
		assert(func_sym.count(curFunc) > 0);	// curFunc must have been logged
		if (func_sym[curFunc].count(name) > 0)
		{
			return &func_sym[curFunc][name];
		}
		if (local)
		{
			if (curFunc == name)
			{
				return &global_sym[name];
			}
			return nullptr;
		}
	}
	//global
	if (global_sym.count(name) > 0)
		return &global_sym[name];
	else
		return nullptr;
}

bool ST::is_global_iden(const std::string &curFunc, std::string &s)
{
	if (*(s.begin()) == '#')
		return false;
	varinfo* t = lookup(curFunc, s, true);
	if (t == nullptr)
		return true;
	else
		return false;
}


std::map<std::string, varinfo> ST::lookup_func(const std::string &func_name)
{
	assert(func_sym.count(func_name) == 1);
	return func_sym[func_name];
}

varinfo* ST::lookup_para(std::map<std::string, varinfo> &func_symtab, int place)
{
	for (auto iter = func_symtab.begin(); iter != func_symtab.end(); ++iter)
	{
		if (iter->second.length == place && iter->second.type == ST::PARAM_TYP)
		{
			return &(iter->second);
		}
	}
	return nullptr;
}

/* length of IDEN = 0 ~ inf, int|char-0(const->value), fun-num_of_params, array-len */
void ST::addsym(std::string curFunc, std::string namae, int _class, int type, int length, int line)
{
	varinfo temp;
	temp.name = namae;
	temp.cls = _class;
	temp.type = type;
	temp.length = length;	//if param, length is relative addr of param, range(0, length_of_func)
	temp.defLine = line;
	if (curFunc == "")	//global
	{
		assert(global_sym.count(namae) == 0);	// must not exist
		global_sym.insert(std::pair<std::string, varinfo>(namae, temp));
		if (type == ST::FUN_TYP)		//FUN_TYP
		{
			std::map<std::string, varinfo> m;
			func_sym.insert(std::pair<std::string, std::map<std::string, varinfo>>(namae, m));
		}
	}
	else
	{
		assert(func_sym.count(curFunc) > 0);	//current function exists
		assert(func_sym[curFunc].count(namae) == 0);	// not exist
		assert(curFunc != namae);		// name of var != func name
		func_sym[curFunc].insert(std::pair<std::string, varinfo>(namae, temp));
	}
}

int str_sym_counter = 0;
int ST::addStr(std::string &s)
{
	if (output_str_sym.count(s) == 0)
	{
		ST::output_str_sym.insert(std::pair<std::string, int>(s, ++str_sym_counter));
		return str_sym_counter;
	}
	return output_str_sym[s];
}

#define SYM_CLS(x)	((x.cls == INT_CLS ? "int" : x.cls == CHA_CLS ? "char" : "void"))
#define SYM_TYP(x)	((x.type == CONST_TYP ? "const" : \
						x.type == VAR_TYP ? "var" : \
						x.type == ARRAY_TYP ? "array" : \
						x.type == FUN_TYP ? "func" : "para"))
void ST::printSym(std::ofstream&o)
{
	for (auto iter = output_str_sym.begin(); iter != output_str_sym.end(); iter++)
	{
		o << "string_" << std::to_string(iter->second)
			<< " : .asciiz " << iter->first << '"' << std::endl;
	}
	o << std::right;
	o << "global:" << std::endl;
	o << std::setw(14) << "name" << '|' <<
		std::setw(5) << "class" << '|' <<
		std::setw(6) << "type" << '|' <<
		std::setw(5) << "len" << '|' <<
		std::setw(5) << "def" << '|' <<
		std::setw(11) << "addr" << std::endl;
	for (auto iter = global_sym.begin(); iter != global_sym.end(); iter++)
	{
		o << std::dec << std::setw(14) << iter->first << '|' <<
			std::setw(5) << SYM_CLS(iter->second) << '|' <<
			std::setw(6) << SYM_TYP(iter->second) << '|' <<
			std::dec << std::setw(5) << iter->second.length << '|' <<
			std::dec << std::setw(5) << iter->second.defLine << '|'
			 << std::setw(11) << std::hex << iter->second.addr << '|'  << std::endl;
	}
	o << std::endl;
	for (auto iter = func_sym.begin(); iter != func_sym.end(); iter++)
	{
		if (iter->first != "main")
		{
			o << iter->first << ':' << std::endl;
			o << std::dec << std::setw(14) << "name" << '|' <<
				std::setw(5) << "class" << '|' <<
				std::setw(6) << "type" << '|' <<
				std::setw(5) << "len" << '|' <<
				std::setw(5) << "def" << '|' <<
				std::setw(11) << "addr" << '|' <<
				std::setw(3) << "reg" << std::endl;
			for (auto it2 = iter->second.begin(); it2 != iter->second.end(); it2++)
				o << std::setw(14) << it2->first << '|' <<
				std::setw(5) << SYM_CLS(it2->second) << '|' <<
				std::setw(6) << SYM_TYP(it2->second) << '|' <<
				std::dec << std::setw(5) << it2->second.length << '|' <<
				std::dec << std::setw(5) << it2->second.defLine << '|'
				  << std::setw(11) << std::hex << it2->second.addr << '|' <<
				std::dec << std::setw(3) << it2->second.reg << std::endl;
		}
	}
	o << std::endl << "main:" << std::endl;
	o << std::dec << std::setw(14) << "name" << '|' <<
		std::setw(5) << "class" << '|' <<
		std::setw(6) << "type" << '|' <<
		std::setw(5) << "len" << '|' <<
		std::setw(5) << "def" << '|' <<
		std::setw(11) << "addr" << '|' <<
		std::setw(3) << "reg" << std::endl;
	for (auto it2 = func_sym["main"].begin(); it2 != func_sym["main"].end(); it2++)
		o << std::setw(14) << it2->first << '|' <<
		std::setw(5) << SYM_CLS(it2->second) << '|' <<
		std::setw(6) << SYM_TYP(it2->second) << '|' <<
		std::dec << std::setw(5) << it2->second.length << '|' <<
		std::dec << std::setw(5) << it2->second.defLine << '|'
		  << std::setw(11) << std::hex << it2->second.addr << '|' << 
		std::dec << std::setw(3) << it2->second.reg << std::endl;
}

