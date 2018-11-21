#pragma once
#include "LexerHead.h"
#include "Compiler.h"

#if DEBUG
#define Syn_Out 1
#else
#define Syn_Out 0
#endif

namespace Syn {
	// class of IDEN = {INT, CHAR, FUNC}
	extern constexpr auto INT_CLS = 1;
	extern constexpr auto CHA_CLS = 2;
	extern constexpr auto FUN_CLS = 3;
	// type of IDEN = {CONST, VAR, ARRAY}
	// about function type = num of params
	extern constexpr auto CONST_TYP = 1;
	extern constexpr auto VAR_TYP = 2;
	extern constexpr auto ARRAY_TYP = 3;
	// length of IDEN = 1 ~ inf, int|char-1, fun-1, array-len
	void program();
}
void expression();
void sentence();
void sentence_list();