#include "SyntaxHead.h"

std::string curFunc = "";	// "" means global
std::string zero = "0";		// fill op1, op2
std::string ret_val_mark = "RET_v0";

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
	bool const_int = true;
	if (is_intsym || is_charsym)	//const int|char
	{
		const_int = is_intsym;	// define const int, then not allow const char
		Lex::getsym();
	}
	else 
	{
		/* TODO: expect int|char after const, default int  */
		Lex::curElmt = "int";
	}
	
	bool comma_now;	// check if , exists and start next const
	do
	{
		std::string name = "";
		if (Lex::curCls == Lex::IDEN)
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
			std::cout << "Line: " << Lex::LineCounter
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
			
		}
		else
		{
			/* TODO: miss iden after "const int|char" */
			/* TODO: skip until ; ,
					if meet reservedwords, then
					break with err"lack semi"*/
		}
		comma_now = is_comma;
		if (comma_now)
			Lex::getsym();
	} while (comma_now);
}
//先读后进
void continuous_var_def(bool inttype)
{	
	//int r;
	do
	{	
		//curElmt is ,
		Lex::getsym();
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
						//Lex::getsym();
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
				//Lex::getsym();
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
//先进后读
void value_param(const varinfo *func_name)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " value_param " << "start" << std::endl;
#endif
	int para_count = 0;
	std::map<std::string, varinfo> func_symtab = ST::lookup_func(func_name->name);
	do
	{	// now is , or (
		Lex::getsym();
		// now is expr head
		std::string temp_param = std::string();
		int ret_cls;
		expression(ret_cls, temp_param);
		Med::addIMC(temp_param, OP::PUSH_PARA, zero, zero);
		//find the info of para
		auto *para = ST::lookup_para(func_symtab, para_count);
		if (para == nullptr)
		{
			/* TODO: too much para*/
		}
		if (ret_cls != para->cls)
		{
			/* cls not match: expect type(para->cls) get type(ret_cls)*/
		}
		++para_count;
	} while (is_comma);
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " value_param " << "over" << std::endl;
#endif
}
//先读后进, 语句返回类型/值
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
			/* TODO: not def, return */
			return;
		}
		ret_cls = temp_iden->cls;
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
			int array_index;
			Med::is_operand_num(temp_ret_val, &array_index);
			if (&array_index != nullptr)		// not nullptr <=> stoi success
			{
				if (!(array_index >= 0 && array_index < temp_iden->length))
				{
					/* TODO: index out of range */
				}
			}
			ret_val = Med::gen_temp();
			Med::addIMC(ret_val, OP::READ_ARR, name, temp_ret_val);
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
			//func call
			if (temp_iden->type != ST::FUN_TYP)
			{
				/* TODO: use ( when IDEN is NOT Function, return */
				
			}
			if (temp_iden->cls == ST::VOID_CLS)
			{
				/* TODO: no ret val */
			}
			//Lex::getsym();
			value_param(temp_iden);
			if (is_R_small)
			{
				Lex::getsym();
				Med::addIMC(name, OP::CALL, zero, zero);
				std::string move_ret_to = Med::gen_temp();
				Med::addIMC(move_ret_to, OP::ADD, ret_val_mark, zero);
				ret_val = move_ret_to;
			}
			else {
				/* TODO: miss ) */
			}
		}
		else {
			/* TODO: no_param_func / const|var(int / char) */
			switch (temp_iden->type)
			{
			case(ST::PARAM_TYP):
			case(ST::VAR_TYP):
			{
				ret_val = name;
				break;
			}
			case(ST::CONST_TYP):
			{
				ret_val = std::to_string(temp_iden->length);
				break;
			}
			case(ST::FUN_TYP):
			{
				if (temp_iden->length != 0)	//must be a no para func
				{
					/* TODO: expect no para func*/
				}
				Med::addIMC(name, OP::CALL, zero, zero);
				std::string move_ret_to = Med::gen_temp();
				Med::addIMC(move_ret_to, OP::ADD, ret_val_mark, zero);
				ret_val = move_ret_to;
				break;
			}
			default:
			{
				/* TODO: what the hell? */
			}
			}
		}
	}
	else if (is_L_small)
	{
		Lex::getsym();
		expression(ret_cls, ret_val);
		ret_cls = ST::INT_CLS;
		if (is_R_small)
		{
			Lex::getsym();
		}
		else {
			/* TODO: miss ) */
		}
	}
	else{
		/* TODO: int | char ,e.g. 3, '6' */
		//Lex::getsym();
		if (is_SGL_CHARA)
		{
			ret_cls = ST::CHA_CLS;
			ret_val = Lex::curElmt;	// with ' so i know its a char
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
				ret_val = sign == 1 ? Lex::curElmt : "-" + Lex::curElmt;
				ret_cls = ST::INT_CLS;
				Lex::getsym();
			}
			else
			{
				/* TODO: wrong facor */
			}
		}
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " factor " << "end" << std::endl;
#endif

}
//先读后进 语句返回类型/值
void term(int &ret_cls, std::string &ret_val)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " term " << "start" << std::endl;
#endif
	std::string factor1;
	factor(ret_cls, factor1);		// int char temp var para
	while (is_mul || is_div)
	{
		ret_cls = ST::INT_CLS;
		int cls = -1;
		bool mul = is_mul;
		std::string factor2;
		Lex::getsym();
		factor(cls, factor2);
		std::string factor3 = Med::gen_temp();
		Med::addIMC(factor3, mul ? OP::MUL : OP::DIV, factor1, factor2);
		factor1 = factor3;
	}
	ret_val = factor1;
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " term " << "over" << std::endl;
#endif

}
//先读后进 语句返回类型/值
void expression(int &ret_class, std::string &value)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " expression " << "start" << std::endl;
#endif
	//int r;
	int symbol = 1;	// + | -
	bool calculate = false;	// determine ret_cls = int / char
	if (is_add || is_sub)
	{
		symbol = is_add ? 1 : -1;
		calculate = true;
		Lex::getsym();
	}
	std::string term1;
	term(ret_class, term1);
	ret_class = calculate ? ST::INT_CLS : ret_class;
	if (symbol == -1)
	{
		std::string minus_term = Med::gen_temp();
		Med::addIMC(minus_term, OP::SUB, zero, term1);
		term1 = minus_term;
	}
	while (is_add || is_sub)
	{
		ret_class = ST::INT_CLS;	// must calc if in here
		symbol = is_add ? 1 : -1;
		int term_ret_cls; std::string term2;
		Lex::getsym();
		term(term_ret_cls, term2);
		std::string term3 = Med::gen_temp();
		Med::addIMC(term3, symbol == 1 ? OP::ADD : OP::SUB, term1, term2);
		term1 = term3;
	}
	value = term1;
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " expression " << "over" << std::endl;
#endif

}
//先读后进
void condition(std::string &label)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " conditon " << "start" << std::endl;
#endif
	int cls1; std::string expr1;
	expression(cls1, expr1);
	if (is_compare_op)
	{
		std::string compare_op = Lex::curElmt;
		int cls2; std::string expr2;
		Lex::getsym();
		expression(cls2, expr2);	// if condi then A <label1> --> if not condi branch label1
		if (compare_op == "==")		// if condi then A <label1> else B; <label2> C --> if not condi branch label 1,  
		{							//		at the end of A GOTO label2
			Med::addIMC(label, OP::NEQ, expr1, expr2);
		}
		else if (compare_op == "!=")
		{
			Med::addIMC(label, OP::EQU, expr1, expr2);
		}
		else if (compare_op == "<=")
		{
			Med::addIMC(label, OP::GRT, expr1, expr2);
		}
		else if (compare_op == "<")
		{
			Med::addIMC(label, OP::GREQ, expr1, expr2);
		}
		else if (compare_op == ">=")
		{
			Med::addIMC(label, OP::LES, expr1, expr2);
		}
		else if (compare_op == ">")
		{
			Med::addIMC(label, OP::LESEQ, expr1, expr2);
		}
	}
	else
	{
		Med::addIMC(label, OP::EQU, expr1, zero);
	}
#if Syn_Out
		std::cout << "Line: " << Lex::LineCounter
		<< " condition " << "end" << std::endl;
#endif

}
//先读后进，所在函数返回类型/值
void if_sentence(bool &value_return, const int &ret_cls, std::string name)
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
	// if condi then A <label1> --> if not condi branch label1
	// if condi then A (goto label2) <label1> else B; <label2> C --> if not condi branch label1,  
	//		at the end of A GOTO label2
	std::string label1 = Med::gen_label();
	condition(label1);
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{

	}
	sentence(value_return, ret_cls, name);
	if (is_elsesym)
	{
		std::string label2 = Med::gen_label();
		Med::addIMC(label2, OP::GOTO, zero, zero);
		Med::addIMC(label1, OP::LABEL, zero, zero);
		Lex::getsym();
		sentence(value_return, ret_cls, name);
		Med::addIMC(label2, OP::LABEL, zero, zero);
	}
	else		// no else
	{
		Med::addIMC(label1, OP::LABEL, zero, zero);
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
	bool comma_now;
	do
	{
		Lex::getsym();
		if (is_IDEN)
		{
			std::string name = Lex::curElmt;
			varinfo *temp_iden = ST::lookup(curFunc, name, false);
			if (temp_iden == nullptr)	// must def before use
			{
				/* TODO: undef iden*/
				Lex::getsym();
				continue;
			}
			if (temp_iden->type != ST::VAR_TYP && temp_iden->type != ST::PARAM_TYP)
			{	// var | param can be read
				/* expect var/param*/
			}
			if (temp_iden->cls == ST::INT_CLS)
			{
				Med::addIMC(name, OP::SCAN, "int", zero);
			}
			else if (temp_iden->cls == ST::CHA_CLS)
			{
				Med::addIMC(name, OP::SCAN, "char", zero);
			}
			else
			{
				std::cerr << "scanf wtf? " << temp_iden->cls;
				assert(false);
			}
			Lex::getsym();
		}
		else
		{
			/* lack iden */
		}
		comma_now = is_comma;
		if (comma_now)
			Lex::getsym();
	} while (comma_now);

	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* lack ) */
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
		int str_no = ST::addStr(Lex::curElmt);
		Lex::getsym();
		if (is_comma)
		{
			Med::addIMC(Med::strhd + std::to_string(str_no), OP::PRINT, zero, zero);
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
				/* miss ) */
			}
#if Syn_Out
			std::cout << "Line: " << Lex::LineCounter
				<< " printf " << "over" << std::endl;
#endif
			Med::addIMC(Med::strhd + std::to_string(str_no), OP::PRINT, zero, zero);
			return;
		}
	}
	int ret_cls = -1;
	std::string value;
	expression(ret_cls, value);
	if (ret_cls == ST::INT_CLS)
	{
		Med::addIMC(value, OP::PRINT, "int", zero);
	}
	else if (ret_cls == ST::CHA_CLS)
	{
		Med::addIMC(value, OP::PRINT, "char", zero);
	}
	/* print */
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: lack ) */
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " printf " << "over" << std::endl;
#endif

}
//先读后进，所在函数返回类型/值
void return_sentence(bool &value_return, const int &ret_cls, std::string func_name)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " return " << "start" << std::endl;
#endif

	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
		int expr_ret_cls = -1;
		std::string value;
		expression(expr_ret_cls, value);
		if (expr_ret_cls == ST::INT_CLS || expr_ret_cls == ST::CHA_CLS)
		{
			value_return = true;
		}
		if (ret_cls == ST::VOID_CLS)
		{
			/* TODO: return sth when void*/
		}
		else if (ret_cls != expr_ret_cls)
		{
			/* class(expr) != return class(func) */
		}
		else
		{
			Med::addIMC(ret_val_mark, OP::ADD, value, zero);
		}
		if (is_R_small)
		{
			Lex::getsym();
		}
		else
		{
			/* TODO: miss ) */
		}
		if (func_name != "main")
			Med::addIMC(zero, OP::RET, zero, zero);
		else
			Med::addIMC(zero, OP::EXIT, zero, zero);
		return;
	}
	if (ret_cls != ST::VOID_CLS)
	{
		/* TODO: miss (, need return sth */
	}
	if (func_name != "main")
		Med::addIMC(zero, OP::RET, zero, zero);
	else
		Med::addIMC(zero, OP::EXIT, zero, zero);
	return;	
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " return " << "over" << std::endl;
#endif

}
//先读后进，所在函数返回类型/值
void while_sentence(bool &value_return, const int &ret_cls, std::string func_name)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " while " << "start" << std::endl;
#endif
	// <label1> if condi then loopbody (goto label1) <label2>
	// <label1> ifnot condi branch label2 loopbody (goto label1) <label2>
	std::string label1 = Med::gen_label();
	Med::addIMC(label1, OP::LABEL, zero, zero);
	std::string label2 = Med::gen_label();
	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	condition(label2);
	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ) */
	}
	sentence(value_return, ret_cls, func_name);
	Med::addIMC(label1, OP::GOTO, zero, zero);
	Med::addIMC(label2, OP::LABEL, zero, zero);
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " while " << "over" << std::endl;
#endif

}
//先读后进，所在函数返回类型/值
void for_sentence(bool &value_return, const int &ret_cls, std::string func_name)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " for " << "start" << std::endl;
#endif
	/* init label <sentence> sth++ (if cond goto label)*/
	Lex::getsym();
	if (is_L_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ( */
	}
	if (is_IDEN)	// not allow array here
	{
		std::string name = Lex::curElmt;
		auto temp_id = ST::lookup(curFunc, name, false);
		if (temp_id != nullptr && (temp_id->type==ST::VAR_TYP || temp_id->type==ST::PARAM_TYP))
		{
			Lex::getsym();
			if (is_assign)
			{
				Lex::getsym();
			}
			else
			{
				/* miss = */
			}
			int exprt_ret_cls = -1; std::string value;
			expression(exprt_ret_cls, value);
			if (exprt_ret_cls == ST::INT_CLS && temp_id->cls == ST::CHA_CLS)
			{
				/* TODO: assign char with int */
			}
			Med::addIMC(name, OP::ADD, value, zero);
			if (is_semicolon)
			{
				Lex::getsym();
			}
			else
			{
				/* TODO: miss semi */
			}
		}
		else
		{
			/* TODO: unsupport iden, skip until ; */
		}		
	}
	else
	{
		/* TODO: miss IDEN */
	}

	std::string for_label = Med::gen_label();
	Med::addIMC(for_label, OP::LABEL, zero, zero);

	// if cond goto loop. DO NOT use condition()!!!
	int cls1; std::string expr1;
	int cls2; std::string expr2;
	std::string compare_op;
	expression(cls1, expr1);
	if (is_compare_op)	/* XXX expr1, expr2, label -> op just same */
	{
		compare_op = Lex::curElmt;
		Lex::getsym();
		expression(cls2, expr2);
	}
	else	/* bne expr zero label*/
	{
		compare_op = "!=";
		expr2 = zero;
	}
	if (is_semicolon)
	{
		Lex::getsym();
	}
	else 
	{
		/* TODO: miss semi */
	}

	/* iter ++/--*/
	std::string name1="", name2="", step_direc;
	int step;
	if (is_IDEN)
	{
		name1 = Lex::curElmt;
		auto temp_id = ST::lookup(curFunc, name1, false);
		if (!(temp_id != nullptr && (temp_id->type == ST::VAR_TYP || temp_id->type == ST::PARAM_TYP)))
		{
			/* unsupport IDEN in for*/
		}
		Lex::getsym();
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
			name2 = Lex::curElmt;
			auto temp_id = ST::lookup(curFunc, name1, false);
			if (!(temp_id != nullptr && (temp_id->type == ST::VAR_TYP || temp_id->type == ST::PARAM_TYP)))
			{
				/* unsupport IDEN in for */
			}
			Lex::getsym();
			step_direc = Lex::curElmt;
			if (is_add || is_sub)
			{
				step_direc = Lex::curElmt;
				Lex::getsym();
			}
			else
			{
				/* miss +/-, default +*/
				step_direc = "+";
			}
			if (Lex::curCls == Lex::UNSGN_INT)
			{
				step = Lex::curNum;
				Lex::getsym();
			}
			else
			{
				/* expect a int */
				step = 1;
			}
		}
		else
		{
			/* TODO: miss IDEN*/
		}
	}
	else
	{
		/* TODO: miss IDEN */
	}

	if (is_R_small)
	{
		Lex::getsym();
	}
	else
	{
		/* TODO: miss ) */
	}
	sentence(value_return, ret_cls, func_name);
	if (name1 != "" && name2 != "")
	{
		Med::addIMC(name1, (step_direc == "+" ? OP::ADD : OP::SUB), name2, std::to_string(step));
	}
	Med::addIMC(for_label, (compare_op == "!=" ? OP::NEQ :
							compare_op == "==" ? OP::EQU : 
							compare_op == ">" ? OP::GRT : 
							compare_op == ">=" ? OP::GREQ :
							compare_op == "<" ? OP::LES : OP::LESEQ), expr1, expr2);

#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " for " << "over" << std::endl;
#endif

}
//先读后进，所在函数返回类型/值
void sentence(bool &value_return, const int &ret_cls, std::string func_name)
{
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence " << "start" << std::endl;
#endif
	if (is_ifsym)
	{
		if_sentence(value_return, ret_cls, func_name);
	}
	else if (is_whilesym)
	{
		while_sentence(value_return, ret_cls, func_name);
	}
	else if (is_forsym)
	{
		for_sentence(value_return, ret_cls, func_name);
	}
	else if (is_L_big)
	{
		Lex::getsym();
		sentence_list(value_return, ret_cls, func_name);
		if (is_R_big)
		{
			Lex::getsym();
		}
		else
		{
			/* TODO: miss } */
		}
	}
	else if (is_IDEN)
	{
		std::string name = Lex::curElmt;
		varinfo *temp_iden = ST::lookup(func_name, name, false);
		if (temp_iden == nullptr)
		{
			/* TODO: undef iden*/
			return;
		}
		Lex::getsym();
		if (is_semicolon)
		{
			if (!(temp_iden->type == ST::FUN_TYP && temp_iden->length == 0))
			{
				/* TODO: expect no para func */
			}
			Med::addIMC(name, OP::CALL, zero, zero);
			Lex::getsym();
		}
		else if (is_L_small)
		{
			if (temp_iden->type != ST::FUN_TYP)
			{
				/* TODO: expect param func */
			}
			//Lex::getsym();
			value_param(temp_iden);
			Med::addIMC(name, OP::CALL, zero, zero);
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
			if (temp_iden->type != ST::ARRAY_TYP)
			{
				/* TODO: expect array */
			}
			int expr_ret_cls = -1;
			std::string value;
			Lex::getsym();
			expression(expr_ret_cls, value);
			int num;
			Med::is_operand_num(value, &num);
			if (&num != nullptr)
			{
				if (!(num >= 0 && num < temp_iden->length))
				{
					/* TODO: index out of range */
				}
			}
			if (is_R_mid)
			{
				Lex::getsym();
			}
			else
			{
				/* TODO: miss ]*/
			}
			if (is_assign)
			{
				Lex::getsym();
			}
			else
			{

			}
			int right_expr_ret_cls = -1;
			std::string right_value;
			expression(right_expr_ret_cls, right_value);
			if (temp_iden->cls == ST::CHA_CLS && right_expr_ret_cls == ST::INT_CLS)
			{
				/* TODO: unable to assign int to char */
			}
			Med::addIMC(name, OP::SAVE_ARR, value, right_value);
			if (is_semicolon)
			{
				Lex::getsym();
			}
			else
			{
				/* TODO: miss ;*/
			}
		}
		else if (is_assign)
		{
			if (temp_iden->type != ST::VAR_TYP && temp_iden->type != ST::PARAM_TYP)
			{
				/* TODO: expect var/param*/
			}
			Lex::getsym();
			int expr_ret_cls = -1;
			std::string value;
			expression(expr_ret_cls, value);
			if (temp_iden->cls == ST::CHA_CLS && expr_ret_cls == ST::INT_CLS)
			{
				/* TODO: unable assign char with int */
			}
			Med::addIMC(name, OP::ADD, value, zero);
			if (is_semicolon)
			{
				Lex::getsym();
			}
			else
			{
				/* TODO: miss ; */
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
		return_sentence(value_return, ret_cls, func_name);
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
//先读后进，所在函数返回类型/值
void sentence_list(bool &value_return, const int &ret_cls, std::string func_name)
{
	//int r = Lex::curCls;
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence_list " << "start" << std::endl;
#endif
	while (sent_head_rsvd || is_IDEN)
	{
		sentence(value_return, ret_cls, func_name);
	}
#if Syn_Out
	std::cout << "Line: " << Lex::LineCounter
		<< " sentence_list " << "end" << std::endl;
#endif
}
//	先进后读，所在函数返回类型/值
void complex_sentence(bool &value_return, const int &ret_cls, std::string func_name)
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
	sentence_list(value_return, ret_cls, func_name);		// before: new word, after: "}"
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
					varinfo *finfo = ST::lookup("", func_name, false);
					assert(finfo != nullptr);
					ST::addsym(func_name, IDEN_name, _cls, ST::PARAM_TYP, finfo->length, Lex::LineCounter);
					++(finfo->length);		// length of param: i th param, range(0, length_of_func)
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
void param_func_def_piece(const std::string func_name)
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
	bool with_return_value = false;
	auto func_info = ST::lookup("", func_name, false);
	Med::addIMC(func_name, OP::FUNC_BEGIN, zero, zero);
	complex_sentence(with_return_value, func_info->cls, func_name);
	if (is_R_big)
	{
		Lex::getsym();
		if (func_info->cls != ST::VOID_CLS)
		{	// need return sth but not
			/* TDOD: need return sth */

		}
		else if (func_info->cls == ST::VOID_CLS)
		{	// mustn't return sth but return sth
			/* TDOD: mustn't return sth */

		}

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
void no_param_func_def_piece(const std::string func_name)
{
	bool with_return_value = false;
	auto func_info = ST::lookup("", func_name, false);
	Med::addIMC(func_name, OP::FUNC_BEGIN, zero, zero);
	complex_sentence(with_return_value, func_info->cls, func_name);
	if (is_R_big)
	{
		Lex::getsym();
		if (!with_return_value && func_info->cls != ST::VOID_CLS)
		{	// need return sth but not
			/* TDOD: need return sth */

		}
		else if (with_return_value && func_info->cls == ST::VOID_CLS)
		{	// mustn't return sth but return sth
			/* TDOD: mustn't return sth */
			
		}
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
	Med::addIMC("main", OP::FUNC_BEGIN, zero, zero);
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
	bool with_return_value = false;
	complex_sentence(with_return_value, ST::VOID_CLS, curFunc);
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
							//Lex::getsym();
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
					//Lex::getsym();
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

#if Syn_Out | IMC_Out
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
	std::cout << std::endl;
	Med::printIMC();
	if (Lex::code_file.is_open())
	{
		Lex::code_file.close();
	}
	// system("pause");
	return 0;  
}
#endif
