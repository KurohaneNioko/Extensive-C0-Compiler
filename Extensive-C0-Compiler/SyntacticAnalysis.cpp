#include "LexerHead.h"
#include "Compiler.h"

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
#define is_grater		(Lex::curElmt == ">")
#define is_grt_eql		(Lex::curElmt == ">=")
#define is_less			(Lex::curElmt == "<")
#define is_les_eql		(Lex::curElmt == "<=")
#define is_dbl_quote	(Lex::curElmt == "\"")
#define is_sgl_quote	(Lex::curElmt == "'")
#define is_comma		(Lex::curElmt == ",")
#define is_semicolon	(Lex::curElmt == ";") 

void _int()
{
	if()

}

void const_define()
{
	int r;		//ret value from getsym
	bool const_int = false;
	if (is_intsym)	//const int
	{
		const_int = true;	// define const int, then not allow const char
		r = Lex::getsym();
		if (r == Lex::IDEN)
		{
			/* TODO: search in symbolTable
						-> exist in the same layer(function, var, const) -> err
						-> not exist -> enSymbolTable
			*/
			Lex::getsym();
			if (is_assign)
			{
				Lex::getsym();

			}
			else
			{
				/* TODO: miss '=' after "const int x" */
			}
		}
		else
		{
			/* TODO: miss iden after "const int" */
		}
	}
	else if (is_charsym)	//const char
	{
		const_int = false;	//not allow const int
	}
}

void const_declare()
{
	do
	{
		Lex::getsym();
		if (is_constsym)
		{
			Lex::getsym();
			const_define();
		}
	} while (is_comma);
	
}

void variable_declaration()
{

}

void program()
{

}