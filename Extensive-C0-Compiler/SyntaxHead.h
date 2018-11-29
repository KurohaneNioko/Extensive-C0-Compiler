#pragma once
#include "LexerHead.h"
#include "Compiler.h"

#if DEBUG
#define Syn_Out 1
#else
#define Syn_Out 0
#endif

namespace Syn {
	
	void program();
}
void expression();
void sentence();
void sentence_list();