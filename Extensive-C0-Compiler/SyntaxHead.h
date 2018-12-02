#pragma once
#include "SymbolHead.h"
#include "LexerHead.h"
#include "Intermediate.h"
#include "Compiler.h"

#if DEBUG
#define Syn_Out 1
#else
#define Syn_Out 0
#endif

namespace Syn {
	
	void program();
}
void expression(int &ret_class, std::string &value);
void sentence();
void sentence_list();