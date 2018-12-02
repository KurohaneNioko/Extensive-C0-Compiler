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
std::string curFunc = "";	// "" means global

void skipTill(const std::set<std::string> symbols, const std::set<int> wordType)
{
	//symbol e.g. "," ";"	wordType e.g. Lex::RSVD_WD
	int r = -1;
	while (symbols.count(Lex::curElmt) == 0 && !CODEEOF)
	{
		r = Lex::getsym();
		if (wordType.count(r) == 1)
			break;
	}
}

// about var def
//	先进后读
int _int()		
{
	int r = Lex::getsym();
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
		/* TODO: not int after const int */

	}
#if Syn_Out
	std::cout << "int got: " << sign * Lex::curNum << std::endl;
#endif
	return sign * Lex::curNum;
}
//	先进后读
char single_char()		
{
	int r = Lex::getsym();

	if (r != Lex::SGL_CHARA)
	{
		/* TODO: not int after const int */

	}
	else {
#if Syn_Out
		std::cout << "char got: " << Lex::curElmt[1] << std::endl;
#endif
	}
	return Lex::curElmt[1];
}
//先读后进
void const_define()		
{
	int r;		//ret value from getsym
	bool const_int = false;
	if (is_intsym || is_charsym)	//const int|char
	{
		const_int = is_intsym;	// define const int, then not allow const char
		do
		{
			std::string name = "";
			r = Lex::getsym();
			if (r == Lex::IDEN)
			{
				name = Lex::curElmt;
				Lex::getsym();
				int val = 0;
				if (is_assign)
				{
					if (const_int)
					{
						val = _int();
					}
					else
					{
						val = '\0' + single_char();
					}
				}
				else
				{
					/* TODO: miss '=' after "const int|char x" ,use default val 0 */
				}
#if Syn_Out
				std::cout << "Line: "<< Lex::LineCounter 
					<< " const " << (const_int ? "int " : "char ") << "def" << std::endl;
#endif
				/* TODO: search in symbolTable
					-> exist in the same layer(function, var, const) -> err
					-> not exist -> enSymbolTable
				*/
				int _cls = const_int ? ST::INT_CLS : ST::CHA_CLS;
				int type = ST::CONST_TYP;
				if (ST::lookup(curFunc, name, true) == nullptr)
				{
					ST::addsym(curFunc, name, _cls, type, val, Lex::LineCounter);
				}
				else
				{
					/* TODO: re def */
				}
				Lex::getsym();
				/* TODO: skip until ',' | ';' 
						if meet reservedwords, then 
						break with err"lack semi" */
			}
			else
			{
				/* TODO: miss iden after "const int|char" */
				/* TODO: skip until ; , 
						if meet reservedwords, then 
						break with err"lack semi"*/
			}
		} while (is_comma);
	}
	else 
	{
		/* TODO: expect int|char after const  */
		/* TODO: skip until ';'
				if meet reservedwords, then
				break with err"lack semi" */
	}
}
//先读后进
void continuous_var_def(bool inttype)
{	
	//int r;
	do
	{	
		//curElmt is IDEN
		if (Lex::curCls == Lex::IDEN)
		{
			std::string key = Lex::curElmt;
			Lex::getsym();
			int _cls = inttype ? ST::INT_CLS : ST::CHA_CLS;
			if (is_comma || is_semicolon)
			{
				if (ST::lookup(curFunc, key, true) == nullptr)
				{
					ST::addsym(curFunc, key, _cls, ST::VAR_TYP, 0, Lex::LineCounter);
				}
				else
				{
					/* TODO: re def */
				}
#if Syn_Out
				std::cout << "Line: " << Lex::LineCounter
					<< " continuous var " << (inttype ? "int " : "char ") << "def" << std::endl;
#endif
			}
			else if (is_L_mid)
			{
				int length = _int();
				if (length <= 0)
				{
					/* TODO: length of array <= 0 */
					length = 1;
				}
				Lex::getsym();		// ']'
				if (!is_R_mid)
				{
					/* TODO: miss R_mid */
					/* skip until ","->continue_var | ";"->continue */
				}
				else
				{
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, _cls, ST::ARRAY_TYP, length, Lex::LineCounter);
					}
					else
					{
						/* TODO: re def */
					}
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " continuous array " << (inttype ? "int " : "char ") << "def" << std::endl;
#endif
					Lex::getsym();	// , | ;
				}
			}
			else
			{
				/* TODO: expect , | ; */
				/* skip until , | ; */
			}
		}
		else
		{
			/* TODO: expect IDEN after ',' */
			/* skip until ',' | ';'*/
		}
	} while (is_comma);
}
//先读后进
void var_def_complex()
{
	int r;
	if (is_intsym || is_charsym)
	{
		bool ret_int = is_intsym;	// func/var type (int|char)
		int _cls = ret_int ? ST::INT_CLS : ST::CHA_CLS;
		r = Lex::getsym();
		if (r == Lex::IDEN)
		{
			std::string key = Lex::curElmt;
			Lex::getsym();
			if (is_semicolon)
			{
				if (ST::lookup(curFunc, key, true) == nullptr)
				{
					ST::addsym(curFunc, key, _cls, ST::VAR_TYP, 0, Lex::LineCounter);
				}
				else
				{
					/* re def */
				}
#if Syn_Out
				std::cout << "Line: " << Lex::LineCounter
					<< " var " << (ret_int ? "int " : "char ") << "def" << std::endl;
#endif
				Lex::getsym();
				return;
			}
			else if (is_L_mid)
			{
				int length = _int();
				length = length > 0 ? length : 1;
				Lex::getsym();		// ']'
				if (!is_R_mid)
				{
					/* TODO: miss R_mid */
					/* skip until ","->continue_var | ";"->continue */
				}
				else
				{
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, _cls, ST::ARRAY_TYP, length, Lex::LineCounter);
					}
					else
					{
						/* re def */
					}

#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " array " << (ret_int ? "int " : "char ") << "def" << std::endl;
#endif
					Lex::getsym();
					if (is_comma)
					{
						Lex::getsym();
						continuous_var_def(ret_int);	//after it, ';'
					}
					if (is_semicolon)
					{
						Lex::getsym();

					}
					else
					{
						/* TODO: lack ; */
					}

				}
			}
			else if (is_comma)
			{
				if (ST::lookup(curFunc, key, true) == nullptr)
				{
					ST::addsym(curFunc, key, _cls, ST::VAR_TYP, 0, Lex::LineCounter);
				}
				else
				{
					/* re def */
				}
#if Syn_Out
				std::cout << "Line: " << Lex::LineCounter
					<< " var " << (ret_int ? "int " : "char ") << "def" << std::endl;
#endif
				Lex::getsym();
				continuous_var_def(ret_int);	//after it, ';'
				if (is_semicolon)
				{
					Lex::getsym();

				}
				else
				{
					/* TODO: lack ; */
				}

			}
			else
			{
				/* TODO: invalid word after int|char IDEN */
			}
		}
		else
		{
			/* TODO: IDEN expected */
		}
	}
	else
	{
		/* TODO: no var def, maybe no error */
		
	}
	
}

// about sentence
//先读后进
void value_param(std::string func_name)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " value_param " << "start" << std::endl;
#endif
	expression();
	while (is_comma)
	{
		Lex::getsym();
		expression();
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " value_param " << "over" << std::endl;
#endif
}
//先读后进
void factor(int &ret_cls, std::string &ret_val)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " factor " << "start" << std::endl;
#endif
	if (is_IDEN)
	{
		std::string name = Lex::curElmt;
		const varinfo *temp_iden = ST::lookup(curFunc, name, false);
		if (temp_iden == nullptr)
		{
			/* TODO: not def */
		}
		int factor_class = temp_iden->cls;
		Lex::getsym();
		if (is_L_mid)
		{
			if (temp_iden->type != ST::ARRAY_TYP)
			{
				/* TODO: use [ when IDEN is NOT array, escape */
			}
			Lex::getsym();
			//expr check type=int
			int temp_ret_cls;
			std::string temp_ret_val;
			expression(temp_ret_cls, temp_ret_val);
			if (temp_ret_cls != ST::INT_CLS)
			{
				/* expr return NOT INT */
			}
			//expr check val=num, avoid array out of index
			int *array_index = Med::is_operand_num(ret_val);
			if (array_index != nullptr)		// not nullptr <=> stoi success
			{
				if (!(*array_index >= 0 && *array_index < temp_iden->length))
				{
					/* TODO: index out of range */
				}
			}
			ret_val = Med::gen_temp();
			Med::addIMC(ret_val, OP::READ_ARR, name, std::to_string(*array_index));
			// expect ]
			if (is_R_mid)
			{
				Lex::getsym();

			}
			else {
				/* TODO: miss ] */
			}
		}
		else if (is_L_small) {
			Lex::getsym();
			value_param(name);
			if (is_R_small)
			{
				Lex::getsym();
			}
			else {
				/* TODO: miss ) */
			}
		}
		else {
			/* TODO: no_param_func / const|var(int / char) */
			//Lex::getsym();
		}
	}
	else if (is_L_small)
	{
		Lex::getsym();
		expression();
		if (is_R_small)
		{
			Lex::getsym();
		}
		else {
			/* TODO: miss ) */
		}
	}
	else{
		/* TODO: int | char  */
		//Lex::getsym();
		if (is_SGL_CHARA)
		{
			Lex::getsym();
		}
		else
		{
			int sign = 1;		// check whether - before num
			if (is_add || is_sub)
			{
				if (is_sub)
				{
					sign = -1;
				}
				Lex::getsym();	//unsigned int expected
			}
			if (is_UNSGN_INT)
			{
				Lex::getsym();
			}
			else
			{

			}
		}
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " factor " << "end" << std::endl;
#endif

}
//先读后进
void term()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " term " << "start" << std::endl;
#endif
	factor();
	while (is_mul || is_div)
	{
		Lex::getsym();
		factor();
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " term " << "over" << std::endl;
#endif

}
//先读后进
void expression(int &ret_class, std::string &value)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " expression " << "start" << std::endl;
#endif
	//int r;
	int symbol = 1;	// + | -
	if (is_add || is_sub)
	{
		symbol = is_add ? 1 : -1;
		Lex::getsym();
	}
	term();
	while (is_add || is_sub)
	{
		symbol = is_add ? 1 : -1;
		Lex::getsym();
		term();
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " expression " << "over" << std::endl;
#endif

}
//先读后进
void condition()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " conditon " << "start" << std::endl;
#endif

	expression();
	if (is_compare_op)
	{
		Lex::getsym();
		expression();
	}
#if Syn_Out
		std::cout << "Line: " << Lex::LineCounter
		<< " condition " << "end" << std::endl;
#endif

}
//先读后进
void if_sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " if " << "start" << std::endl;
#endif
	int r = Lex::getsym();
	if (is_L_small)
	{
		r = Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	condition();
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{

	}
	sentence();
	if (is_elsesym)
	{
		Lex::getsym();
		sentence();

	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " if " << "over" << std::endl;
#endif

}
//先读后进
void scanf_sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " scanf " << "start" << std::endl;
#endif

	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	if (is_IDEN)
	{

		Lex::getsym();
	}
	while (is_comma)
	{
		Lex::getsym();
		if (is_IDEN)
		{

			Lex::getsym();
		}
	}
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{

	}
#if Syn_Out
		std::cout << "Line: " << Lex::LineCounter
		<< " scanf " << "over" << std::endl;
#endif

}
//先读后进
void printf_sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " printf " << "start" << std::endl;
#endif

	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	if (is_STRING)
	{

		Lex::getsym();
		if (is_comma)
		{
			Lex::getsym();
		}
		else
		{
			if (is_R_small)
			{
				Lex::getsym();
			}
			else
			{

			}
#if Syn_Out
			std::cout << "Line: " << Lex::LineCounter
				<< " printf " << "over" << std::endl;
#endif
			return;
		}
	}
	expression();
	/* print */
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{

	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " printf " << "over" << std::endl;
#endif

}
//先读后进
void return_sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " return " << "start" << std::endl;
#endif

	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	expression();
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ) */
	}
	
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " return " << "over" << std::endl;
#endif

}
//先读后进
void while_sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " while " << "start" << std::endl;
#endif

	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	condition();
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ) */
	}
	sentence();
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " while " << "over" << std::endl;
#endif

}
//先读后进
void for_sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " for " << "start" << std::endl;
#endif
	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	if (is_IDEN)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss IDEN */
	}
	if (is_assign)
	{
		Lex::getsym();
	}
	else
	{
		/* miss = */
	}
	expression();
	if (is_semicolon)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss semi */
	}

	condition();
	if (is_semicolon)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss semi */
	}

	if (is_IDEN)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss IDEN */
	}
	if (is_assign)
	{
		Lex::getsym();
	}
	else
	{
		/* miss = */
	}
	if (is_IDEN)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss IDEN */
	}
	if (is_add || is_sub)
	{
		Lex::getsym();
	}
	else
	{
		/* miss + | - */
	}
	if (is_UNSGN_INT)
	{
		Lex::getsym();
	}
	else
	{
		/* miss unsigned int */
	}

	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ) */
	}
	sentence();
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " for " << "over" << std::endl;
#endif

}
//先读后进
void sentence()
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence " << "start" << std::endl;
#endif
	if (is_ifsym)
	{
		if_sentence();
	}
	else if (is_whilesym)
	{
		while_sentence();
	}
	else if (is_forsym)
	{
		for_sentence();
	}
	else if (is_L_big)
	{
		Lex::getsym();
		sentence_list();
		if (is_R_big)
		{
			Lex::getsym();
		}
		else
		{

		}
	}
	else if (is_IDEN)
	{
		std::string name = Lex::curElmt;
		Lex::getsym();
		if (is_semicolon)
		{
			Lex::getsym();
		}
		else if (is_L_small)
		{
			value_param(name);
			if (is_R_small)
			{
				Lex::getsym();
			}
			else 
			{

			}
			if (is_semicolon)
			{
				Lex::getsym();
			}
			else
			{
				/* TODO: miss ; */
			}
		}
		else if (is_L_mid)
		{
			Lex::getsym();
			expression();
			if (is_R_mid)
			{
				Lex::getsym();
			}
			else
			{
			
			}
			if (is_assign)
			{
				Lex::getsym();
			}
			else
			{

			}
			expression();
			if (is_semicolon)
			{
				Lex::getsym();
			}
		}
		else if (is_assign)
		{
			Lex::getsym();
			expression();
			if (is_semicolon)
			{
				Lex::getsym();
			}
		}
		else
		{
			/* TODO: miss ; */
		}
	}
	else if (is_scanfsym)
	{
		scanf_sentence();
		Lex::getsym();
		if (is_semicolon)
		{
			Lex::getsym();
		}
		else
		{

		}
	}
	else if (is_printfsym)
	{
		printf_sentence();
		if (is_semicolon)
		{
			Lex::getsym();
		}
		else
		{

		}

	}
	else if (is_semicolon)
	{
		Lex::getsym();
	}
	else if (is_returnsym)
	{
		return_sentence();
		if (is_semicolon)
		{
			Lex::getsym();
		}
		else
		{

		}

	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence " << "over" << std::endl;
#endif

}
//先读后进
void sentence_list()
{
	//int r = Lex::curCls;
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence_list " << "start" << std::endl;
#endif
	while (sent_head_rsvd || is_IDEN)
	{
		sentence();
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence_list " << "end" << std::endl;
#endif
}
//	先进后读
void complex_sentence()
{
	int r;
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " complex_sentence " << "end" << std::endl;
#endif
	do
	{
		r = Lex::getsym();
		if (is_constsym)
		{
			Lex::getsym();
			const_define();	//after it, curElmt = ";" bad->rsvd_wd
		}
		else
		{
			break;	
		}
		if (!is_semicolon)
		{
			/* TODO: lack ; */
		}
	} while (is_semicolon && !CODEEOF);
	if (is_semicolon)
	{
		r = Lex::getsym();		// int | char 
	}
	do
	{
		var_def_complex();
		if (is_semicolon)
		{
			r = Lex::getsym();		// int | char 
		}
	} while ((is_intsym || is_charsym) && !CODEEOF);
	
	if (is_semicolon)
	{
		r = Lex::getsym();		// sentence list start
	}
	sentence_list();		// before: new word, after: "}"
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " complex_sentence " << "end" << std::endl;
#endif

}

//about func def
//	先进后读
void param_list(std::string func_name)
{
	int r;
	do
	{
		r = Lex::getsym();
		if (is_intsym || is_charsym)
		{
			bool int_para = is_intsym;
			int _cls = int_para ? ST::INT_CLS : ST::CHA_CLS;
			r = Lex::getsym();
			if (r == Lex::IDEN)
			{
				std::string IDEN_name = Lex::curElmt;
#if Syn_Out
				std::cout << "Line: " << Lex::LineCounter << " Function "
					<< func_name << " param: " << (int_para ? "int " : "char ") << IDEN_name << std::endl;
#endif
				if (ST::lookup(func_name, IDEN_name, true) == nullptr)
				{
					ST::addsym(func_name, IDEN_name, _cls, ST::PARAM_TYP, 0, Lex::LineCounter);
					varinfo *finfo = ST::lookup("", func_name, false);
					assert(finfo != nullptr);
					++(finfo->length);	
				}
				else
				{
					/* TODO: re def */
				}
				Lex::getsym();
			}
			else
			{
				/* TODO: invalid IDEN after int|char */
			}
			
		}
		else
		{
			/* TODO: invalid param type */

		}
	} while (is_comma);
}
//	先进后读
void param_func_def_piece(std::string func_name)
{
	param_list(func_name);	//after it, curElmt = non-comma word
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: no ) */
	}
	if (!is_L_big)
	{
		/* TODO: no { */
	}
	complex_sentence();
	if (is_R_big)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: no } after func def */
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " param Function " << "def piece" << std::endl;
#endif
}
//	先进后读
void no_param_func_def_piece(std::string func_name)
{
	complex_sentence();
	if (is_R_big)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: no } after func def */
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " non-param Function " << "def piece" << std::endl;
#endif
}
//	先进后读
void main_piece()
{
	ST::addsym(curFunc, "main", ST::VOID_CLS, ST::FUN_TYP, 0, Lex::LineCounter);
	curFunc = "main";
	int r = Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ) */
	}
	if (!is_L_big)
	{
		/* TODO: miss {*/
	}

	complex_sentence();
	if (!is_R_big)
	{

	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " main piece over" << std::endl;
#endif
}

void Syn::program()
{
	int r;
	r = Lex::getsym();
	while (is_constsym && !CODEEOF)
	{
		Lex::getsym();
		const_define();		//out: curE = ";" / reserved
		if (is_semicolon)
		{
			Lex::getsym();
		}
		else
		{
			/*TODO: lack ; */
		}

		if (is_constsym)
		{
			continue;	// miss ;
		}
		if (is_reserved)
		{
			break;
		}
	}
	//tricky time
	/* int|char -> IDEN ->  [ -> var array
							, -> var next
							; -> var end
					ban var	( -> para_func_def 
					ban var { -> no_para_func_def 
	   void -> main -> out:main_part
	  ban var  IDEN ->  ( -> para_func_def 
						{ -> no_para_func_def */
	bool in_func_def = false;
	while (!CODEEOF) {
		if (is_intsym || is_charsym)
		{
			bool ret_int = is_intsym;	// func/var type (int|char)

			r = Lex::getsym();
			if (r == Lex::IDEN)
			{
				std::string key = Lex::curElmt;
				int _cls = ret_int ? ST::INT_CLS : ST::CHA_CLS;

				Lex::getsym();
				if (is_semicolon && !in_func_def)
				{
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " var " << (ret_int ? "int " : "char ") << "def" << std::endl;
#endif
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, _cls, ST::VAR_TYP, 0, Lex::LineCounter);
					}
					else
					{
						/* TODO: re def */
					}
					Lex::getsym();
					continue;
				}
				else if (is_L_mid && !in_func_def)
				{
					int length = _int();
					if (length <= 0)
					{
						/* TODO: length of array <=0 */
						length = 1;
					}
					Lex::getsym();		// ']'
					if (!is_R_mid)
					{
						/* TODO: miss R_mid */
						/* skip until ","->continue_var | ";"->continue */
					}
					else
					{
#if Syn_Out
						std::cout << "Line: " << Lex::LineCounter
							<< " array " << (ret_int ? "int " : "char ") << "def" << std::endl;
#endif
						if (ST::lookup(curFunc, key, true) == nullptr)
						{
							ST::addsym(curFunc, key, _cls, ST::ARRAY_TYP, length, Lex::LineCounter);
						}
						else
						{
							/* TODO: re def */
						}

						Lex::getsym();	// , | ;
						if (is_comma)
						{
							Lex::getsym();
							continuous_var_def(ret_int);	// in it, read word first
						}
						if (is_semicolon)
						{
							Lex::getsym();
						}
						else
						{
							/* TODO: lack ; */
						}
					}
				}
				else if (is_comma)
				{
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " var " << (ret_int ? "int " : "char ") << "def" << std::endl;
#endif
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, _cls, ST::VAR_TYP, 0, Lex::LineCounter);
					}
					else
					{
						/* TODO: re def */
					}
					Lex::getsym();
					continuous_var_def(ret_int);
					if (is_semicolon)
					{
						Lex::getsym();
					}
					else
					{
						/* TODO: lack ; */
					}

				}
				else if (is_L_small)
				{
					in_func_def = true;
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " para-function " << (ret_int ? "int " : "char ") << std::endl;
#endif
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, _cls, ST::FUN_TYP, 0, Lex::LineCounter);
					}		// modify length later
					else
					{
						/* TODO: re def */
					}
					curFunc = key;
					param_func_def_piece(key);
					curFunc = "";

				}
				else if (is_L_big)
				{
					in_func_def = true;
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " non-para-function " << (ret_int ? "int " : "char ") << std::endl;
#endif
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, _cls, ST::FUN_TYP, 0, Lex::LineCounter);
					}
					else
					{
						/* TODO: re def */
					}
					curFunc = key;
					no_param_func_def_piece(key);
					curFunc = "";
				}
				else
				{
					/* TODO: invalid word after int|char IDEN */
				}
			}
			else
			{
				/* TODO: IDEN expected */
			}
		}
		else if (is_voidsym)
		{
			in_func_def = true;
			r = Lex::getsym();
			if (r == Lex::IDEN)
			{
				std::string key = Lex::curElmt;
				Lex::getsym();
				if (is_L_small)
				{
					in_func_def = true;
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " para-function " << "void" << std::endl;
#endif
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, ST::VOID_CLS, ST::FUN_TYP, 0, Lex::LineCounter);
					}		// modify length later
					else
					{
						/* TODO: re def */
					}
					curFunc = key;
					param_func_def_piece(key);
					curFunc = "";

				}
				else if (is_L_big)
				{
					in_func_def = true;
#if Syn_Out
					std::cout << "Line: " << Lex::LineCounter
						<< " non-para-function " << "void" << std::endl;
#endif
					if (ST::lookup(curFunc, key, true) == nullptr)
					{
						ST::addsym(curFunc, key, ST::VOID_CLS, ST::FUN_TYP, 0, Lex::LineCounter);
					}
					else
					{
						/* TODO: re def */
					}
					curFunc = key;
					no_param_func_def_piece(key);
					curFunc = "";
				}
				else
				{

				}
			}
			else if(is_mainsym)
			{
#if Syn_Out
				std::cout << "Line: " << Lex::LineCounter
					<< " main start" << std::endl;
#endif
				break;		// to main
			}
			else
			{
				/* TODO: miss main/iden */
				
			}
		}
		else
		{
			/* TODO: int/char/void expected*/
			skipTill({ "int", "char", "void" }, { Lex::RSVD_WD });

		}
	}
	assert(is_mainsym);
	main_piece();
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " main over" << std::endl << std::endl;
#endif
}

#if Syn_Out
int main(int argc, char** argv)
{
	std::string code_path(argv[1]);
	//../Docs/16231246_test.txt
	Lex::code_file.open(code_path, std::ifstream::in);
	std::ofstream f_out("../Docs/16231246_Syn_out.txt", std::ios::trunc | std::ofstream::ate);
	//int r;
	if (!Lex::code_file || !f_out)
	{
		std::cout << "open failed";
		return -1;
	}
	unsigned long cnt = 0;
	Syn::program();
	ST::printSym();
	if (Lex::code_file.is_open())
	{
		Lex::code_file.close();
	}
	// system("pause");
	return 0;  
}
#endif