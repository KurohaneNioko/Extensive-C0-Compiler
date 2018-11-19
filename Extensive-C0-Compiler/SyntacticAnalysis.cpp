#include "SyntaxHead.h"

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
#define is_grater		(Lex::curElmt == ">")
#define is_grt_eql		(Lex::curElmt == ">=")
#define is_less			(Lex::curElmt == "<")
#define is_les_eql		(Lex::curElmt == "<=")
#define is_dbl_quote	(Lex::curElmt == "\"")
#define is_sgl_quote	(Lex::curElmt == "'")
#define is_comma		(Lex::curElmt == ",")
#define is_semicolon	(Lex::curElmt == ";") 

std::string curFunc = "";	// "" means global

int _int()
{
	int r;
	int sign = 1;		// check whether - before num
	if (is_add || is_sub)
	{
		if (is_sub)
		{
			sign = -1;
		}
		r = Lex::getsym();	//unsigned int expected
	}
	if (r != Lex::UNSGN_INT)
	{
		/* TODO: not int after const int*/

	}
	return sign * Lex::curNum;
}

void const_define()
{
	int r;		//ret value from getsym
	bool const_int = false;
	if (is_intsym || is_charsym)	//const int|char
	{
		const_int = is_intsym;	// define const int, then not allow const char
		r = Lex::getsym();
		do
		{
			if (r == Lex::IDEN)
			{
				/* TODO: search in symbolTable
							-> exist in the same layer(function, var, const) -> err
							-> not exist -> enSymbolTable
				*/
				Lex::getsym();
				int val = 0;
				if (is_assign)
				{
					r = Lex::getsym();
					val = _int();
				}
				else
				{
					/* TODO: miss '=' after "const int|char x" ,use default val 0 */
				}
				/* TODO: fill in sym table */
				/* TODO: skip until ',' | ';' 
						if meet reservedwords, then 
						break with err"lack semi" */
				/* TODO: if is_comma then getsym(), IDEN expected*/
			}
			else
			{
				/* TODO: miss iden after "const int|char" */
				/* TODO: skip until ';' | IDEN, 
						if meet reservedwords, then 
						break with err"lack semi"*/
			}
		} while (!is_semicolon);
	}
	else 
	{
		/* TODO: expect int|char after const  */
		/* TODO: skip until ';'
				if meet reservedwords, then
				break with err"lack semi" */
	}
}

void variable_define()
{

}

void program()
{
	int r;
	r = Lex::getsym();
	while (is_constsym)
	{
		Lex::getsym();
		const_define();		//out: curE = ";" / reserved
		if (is_reserved)
		{
			break;
		}
		else if (is_semicolon)
		{
			Lex::getsym();	//const expeccted
		}
		else { assert(0); }		//my fault?
	}
	//tricky time
	/* int|char -> IDEN ->  [ -> var array
							, -> var next
					ban var	( -> para_func_def 
					ban var { -> no_para_func_def 
	   void -> main -> out:main_part
	  ban var  IDEN ->  ( -> para_func_def 
						{ -> no_para_func_def */
	if (is_intsym || is_charsym)	
	{

	}
}