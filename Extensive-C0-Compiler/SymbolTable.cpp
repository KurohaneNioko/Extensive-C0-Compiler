#include "SymbolHead.h"
std::map<std::string, varinfo> global_sym;
std::map<std::string, std::map<std::string, varinfo>> func_sym;

varinfo *lookup(std::string curFunc, std::string name)
{
	if (curFunc != "")	// local
	{
		assert(func_sym.count(curFunc) > 0);	// curFunc must have been logged
		if (func_sym[curFunc].count(name) > 0)
		{
			return &func_sym[curFunc][name];
		}
	}
	//global
	if (func_sym[""].count(name) > 0)
		return &func_sym[""][name];
	else
		return nullptr;
}