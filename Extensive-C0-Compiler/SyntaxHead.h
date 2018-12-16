#pragma once
#include "SymbolHead.h"
#include "LexerHead.h"
#include "Intermediate.h"
#include "Error.h"
#include "Compiler.h"

#if DEBUG
#define Syn_Out 0
#else
#define Syn_Out 0
#endif

#define is_constsym		(Lex::curElmt == "const")
#define is_intsym		(Lex::curElmt == "int")
#define is_charsym		(Lex::curElmt == "char")
#define is_voidsym		(Lex::curElmt == "void")
#define is_mainsym		(Lex::curElmt == "main")
#define is_ifsym		(Lex::curElmt == "if")
#define is_elsesym		(Lex::curElmt == "else")
#define is_forsym		(Lex::curElmt == "for")
#define is_whilesym		(Lex::curElmt == "while")
#define is_scanfsym		(Lex::curElmt == "scanf")
#define is_printfsym	(Lex::curElmt == "printf")
#define is_returnsym	(Lex::curElmt == "return")
#define is_reserved		(is_constsym || is_intsym || is_charsym || is_voidsym || \
						 is_mainsym || is_ifsym || is_elsesym || is_forsym || \
						 is_whilesym || is_scanfsym || is_printfsym || is_returnsym )

#define is_add			(Lex::curElmt == "+")
#define is_sub			(Lex::curElmt == "-")
#define is_mul			(Lex::curElmt == "*")
#define is_div			(Lex::curElmt == "/")
#define is_L_small		(Lex::curElmt == "(")
#define is_R_small		(Lex::curElmt == ")")
#define is_L_mid		(Lex::curElmt == "[")
#define is_R_mid		(Lex::curElmt == "]")
#define is_L_big		(Lex::curElmt == "{")
#define is_R_big		(Lex::curElmt == "}")
#define is_assign		(Lex::curElmt == "=")
#define is_not_eql		(Lex::curElmt == "!=")
#define is_eql			(Lex::curElmt == "==")
#define is_greater		(Lex::curElmt == ">")
#define is_grt_eql		(Lex::curElmt == ">=")
#define is_less			(Lex::curElmt == "<")
#define is_les_eql		(Lex::curElmt == "<=")
#define is_dbl_quote	(Lex::curElmt == "\"")
#define is_sgl_quote	(Lex::curElmt == "'")
#define is_comma		(Lex::curElmt == ",")
#define is_semicolon	(Lex::curElmt == ";") 

#define sent_head_rsvd	(is_ifsym || is_forsym || is_semicolon || is_L_big || \
						 is_whilesym || is_scanfsym || is_printfsym || is_returnsym )
#define is_compare_op	(is_not_eql || is_eql || is_greater || is_grt_eql || is_less || is_les_eql)
#define is_IDEN			(Lex::curCls==Lex::IDEN)
#define is_STRING		(Lex::curCls==Lex::STRING)
#define is_UNSGN_INT	(Lex::curCls==Lex::UNSGN_INT)
#define is_SGL_CHARA	(Lex::curCls==Lex::SGL_CHARA)


namespace Syn {
	void program();
}
void expression(int &ret_class, std::string &value);
void sentence(bool &value_return, const int &ret_cls, std::string func_name);
void sentence_list(bool &value_return, const int &ret_cls, std::string func_name);