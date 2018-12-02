#include "SymbolHead.h"
std::map<std::string, varinfo> ST::global_sym;
std::map<std::string, std::map<std::string, varinfo>> ST::func_sym;

varinfo* ST::lookup(std::string curFunc, std::string name, bool local)
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

#define SYM_CLS(x)	((x.cls == INT_CLS ? "int" : x.cls == CHA_CLS ? "char" : "void"))
#define SYM_TYP(x)	((x.type == CONST_TYP ? "const" : \
						x.type == VAR_TYP ? "var" : \
						x.type == ARRAY_TYP ? "array" : \
						x.type == FUN_TYP ? "func" : "para"))

inline const std::map<std::string, varinfo> ST::lookup_func(const std::string &func_name)
{
	assert(func_sym.count(func_name) == 1);
	return func_sym[func_name];
}

const varinfo* ST::lookup_para(const std::map<std::string, varinfo> func_symtab, int place)
{
	for (auto iter = func_symtab.begin(); iter != func_symtab.end(); ++iter)
	{
		if (iter->second.length == place)
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


void ST::printSym()
{
	std::cout << std::right;
	std::cout << "global:" << std::endl;
	for (auto iter = global_sym.begin(); iter != global_sym.end(); iter++)
	{
		std::cout << std::setw(14) << iter->first << '|' <<
			std::setw(5) << SYM_CLS(iter->second) << '|' <<
			std::setw(6) << SYM_TYP(iter->second) << '|' <<
			std::setw(5) << iter->second.length << '|' <<
			std::setw(5) << iter->second.defLine << '|'
			/* << std::setw(11) << std::hex << iter->second.addr << '|' */ << std::endl;
	}
	std::cout << std::endl;
	for (auto iter = func_sym.begin(); iter != func_sym.end(); iter++)
	{
		if (iter->first != "main")
		{
			std::cout << iter->first << ':' << std::endl;
			for (auto it2 = iter->second.begin(); it2 != iter->second.end(); it2++)
				std::cout << std::setw(14) << it2->first << '|' <<
				std::setw(5) << SYM_CLS(it2->second) << '|' <<
				std::setw(6) << SYM_TYP(it2->second) << '|' <<
				std::setw(5) << it2->second.length << '|' <<
				std::setw(5) << it2->second.defLine << '|'
				/*  << std::setw(11) << std::hex << it2->second.addr << '|' */ << std::endl;

		}
	}
	std::cout << std::endl << "main:" << std::endl;
	for (auto it2 = func_sym["main"].begin(); it2 != func_sym["main"].end(); it2++)
		std::cout << std::setw(14) << it2->first << '|' <<
		std::setw(5) << SYM_CLS(it2->second) << '|' <<
		std::setw(6) << SYM_TYP(it2->second) << '|' <<
		std::setw(5) << it2->second.length << '|' <<
		std::setw(5) << it2->second.defLine << '|'
		/*  << std::setw(11) << std::hex << it2->second.addr << '|' */ << std::endl;
}