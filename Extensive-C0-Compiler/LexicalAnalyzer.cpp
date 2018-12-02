#include "LexerHead.h"

#define BACK_1_CHAR		{if(Lex::linePointer!=0){Lex::linePointer -= 1;}else{Lex::LineCounter-=1;codeLine="\n";}}
#define isALPHA(c)		(('a'<=c && c<='z') || ('A'<=c && c<='Z') || (c=='_'))
#define isWHITE(c)		(c=='\t' || c==' ' || c=='\n')
#define isSGL_CHAR(c)	(c=='+' || c=='-' || c=='*' || c=='/' || isALPHA(c) || bool(isdigit(c)))
#define isSGL_QTE(c)	(c=='\'')
#define isDBL_QTE(c)	(c=='"')
std::string codeLine = "";

/* definition of head file */
std::ifstream Lex::code_file;
std::string Lex::curElmt;
int Lex::curNum = 0;
int Lex::curCls;
int Lex::LineCounter = 0;
std::size_t Lex::linePointer = 0;	//next char stars from s[i]
const std::map<std::string, std::string> Lex::reservedWords =
{
	{"const",	"CONST_SYM"},
	{"int",		"INT_SYM"},
	{"char",	"CHAR_SYM"},
	{"void",	"VOID_SYM"},
	{"main",	"MAIN_SYM"},
	{"if",		"IF_SYM"},
	{"else",	"ELSE_SYM"},
	{"for",		"FOR_SYM" },
	{"while",	"WHILE_SYM"},
	{"scanf",	"SCANF_SYM"},
	{"printf",	"PRINTF_SYM"},
	{"return",	"RET_SYM"}
};
const std::map<std::string, std::string> Lex::non_alpha_sym =
{
	{"+",	"ADD"},		{"-",	"SUB"},
	{"*",	"MUL"},		{"/",	"DIV"},
	{"(",	"L_SMALL"},	{")",	"R_SMALL"},
	{"[",	"L_MID"},	{"]",	"R_MID"},
	{"{",	"L_BIG"},	{"}",	"R_BIG"},
	{"=",	"ASSIGN"},
	{"!=",	"NOT_EQL"},	{"==",	"EQUAL"},
	{">",	"GREATER"},	{">=",	"GRT_EQL"},
	{"<",	"LESS"},	{"<=",	"LES_EQL"},
	{"\"",	"DBL_QUOTE"},{"'",	"SGL_QUOTE"},
	{",",	"COMMA"},	{";",	"SEMICOLON"}
};

char readCharFromLine()
{
	if (Lex::linePointer == codeLine.size())
	{
		if (std::getline(Lex::code_file, codeLine))
		{
			Lex::linePointer = 0;
			codeLine += '\n';		// add \n after a line, useful 4 judge
			Lex::LineCounter += 1;
		}
		else
		{
#if DEBUG
			std::cout << "EOF Reached" << std::endl;
#endif
			return 0;
		}

	}
	return codeLine[Lex::linePointer++];
}

int Lex::getsym()
{
	char c;
	Lex::curElmt = "";
	while (true)
	{
		c = readCharFromLine();
		if (c == 0)
		{
			return EOF;	
		}
		else if (isWHITE(c))
		{
			continue;
		}
		else
		{
			break;
		}
	}
	c = tolower(c);
	Lex::curElmt += c;
	if (isALPHA(c))
	{
		/* alpha first:
		 *		read alpha/digit until not alpha/digit, tolower
		 *		check iden/resered words
		 */
		while (true)
		{
			c = readCharFromLine();
			if (isALPHA(c) || isdigit(c))
			{
				Lex::curElmt += tolower(c);
			}
			else
			{
				BACK_1_CHAR
				break;
			}
		}
		if (Lex::reservedWords.count(Lex::curElmt))
		{
			Lex::curCls = Lex::RSVD_WD;
			return Lex::RSVD_WD;
		}
		else
		{
			Lex::curCls = Lex::IDEN;
			return Lex::IDEN;
		}
	}
	else if (isdigit(c))
	{
		/* number -> cut at not-alpha char 
				pure num->NUM, else UNKNOWN
		*/
		bool isPureNum = true;
		while (true)
		{
			c = readCharFromLine();
			if (isdigit(c))
			{
				Lex::curElmt += c;
			}
			else if (isALPHA(c))
			{
				Lex::curElmt += c;
				isPureNum = false;
			}
			else
			{
				BACK_1_CHAR
				break;
			}
		}
		/* TODO: string(num) -> int num*/
		if (isPureNum)
		{
			int num_from_cur = 0;
			try {
				num_from_cur = std::stoi(Lex::curElmt, nullptr);
			}
			catch(const std::out_of_range&){
#if DEBUG
				std::cout << "int Overflow at Line: " << Lex::LineCounter << " Colomn: " << (Lex::linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
				Lex::curNum = 0;		// support for fault

				Lex::curCls = Lex::UNSGN_INT;
				return Lex::UNSGN_INT;
			}
			Lex::curNum = num_from_cur;
			Lex::curCls = Lex::UNSGN_INT;
			return Lex::UNSGN_INT;
		}
		else
		{
#if DEBUG
			std::cout << "Invalid int at Line: " << Lex::LineCounter << " Colomn: " << (Lex::linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
			Lex::curCls = Lex::UNKNOWN;
			return Lex::UNKNOWN;
		}
	}
	else if (isSGL_QTE(c))
	{
		while (true)
		{
			c = readCharFromLine();
			if (c == '\n' || c == 0 || c == '\'')
			{
				if (c == '\'')
					Lex::curElmt += c;
				break;		//stop at '\n', deal with right single quote missed
			}
			Lex::curElmt += c;
		}
		/* TODO: err-> 0 char, 
					   not 2 char, 
					   char not '+' '-' '*' '/' '_' alpha digit,
					   miss right single quote*/
		/* now curElmt = "'xxx'" */
		if (Lex::curElmt.size() <= 1 || Lex::curElmt.size() != 3 || 
			!isSGL_CHAR(Lex::curElmt[1]) || Lex::curElmt[Lex::curElmt.size()-1]!='\'')
		{
			Lex::curElmt = '0';
			Lex::curCls = Lex::SGL_CHARA;
			return Lex::SGL_CHARA;
		}
		Lex::curCls = Lex::SGL_CHARA;
		return Lex::SGL_CHARA;
	}
	else if (isDBL_QTE(c))
	{
		bool char_in_string = true;
		while (true)
		{
			c = readCharFromLine();			
			if (char_in_string && !(32 <= c && c <= 126))	
			{
				char_in_string = false;
			}
			if (c == '\n' || c == 0 || c == '"')
			{
				if (c == '"')
				{
					Lex::curElmt += c;
				}
				break;
			}
			if (c == '\\')
			{
				Lex::curElmt += c;	// new: avoid \n->nwe_line, \t->tab
			}
			Lex::curElmt += c;
		}
		/* TODO: err-> char in string invalid
					   miss right double quote */
		/* now curElmt = ""xxx"" */
		if (Lex::curElmt[Lex::curElmt.size() - 1] != '"')
		{
#if DEBUG
			std::cout << "Miss right double quote: Line " << Lex::LineCounter << " Colomn: " << (Lex::linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
			Lex::curCls = Lex::STRING;
			return Lex::STRING;
		}
		if (!char_in_string)	//with right double quote, but with invalid char
		{
			/* TODO: warning*/
#if DEBUG
			std::cout << "Invalid char in string: Line " << Lex::LineCounter << " Colomn: " << (Lex::linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
			Lex::curCls = Lex::STRING;
			return Lex::STRING;
		}
		Lex::curCls = Lex::STRING;
		return Lex::STRING;		//all ok
	}
	else
	{
		if (c == '+' || c == '-' || c == '*' || c == '/' ||
			c == '(' || c == ')' || c == '[' || c == ']' ||
			c == '{' || c == '}' || c == ';' || c == ',' )
	 	{
			Lex::curCls = Lex::RSVD_SYM;
			return Lex::RSVD_SYM;
		}
		else if (c == '=')
		{
			c = readCharFromLine();
			if (c == '=')
			{
				Lex::curElmt += c;
			}
			else
			{
				BACK_1_CHAR
			}
			Lex::curCls = Lex::RSVD_SYM;
			return Lex::RSVD_SYM;
		}
		else if (c == '>' || c == '<')
		{
			c = readCharFromLine();
			if (c == '=')
			{
				curElmt += c;
			}
			else
			{
				BACK_1_CHAR
			}
			Lex::curCls = Lex::RSVD_SYM;
			return Lex::RSVD_SYM;
		}
		else if (c == '!')
		{
			c = readCharFromLine();
			if (c == '=')
			{
				curElmt += c;
				Lex::curCls = Lex::RSVD_SYM;
				return Lex::RSVD_SYM;
			}
			else
			{
				BACK_1_CHAR
			}
		}
	}
#if DEBUG
	std::cout << "UNKNOWN word at Line: " << Lex::LineCounter << " Colomn: "<< (Lex::linePointer+1-Lex::curElmt.size()) << std::endl;
#endif
	Lex::curCls = Lex::UNKNOWN;
	return Lex::UNKNOWN;
}

#if Lexical_Out
int main(int argc, char** argv)
{
	std::string code_path(argv[1]);
	//../Docs/16231246_test.txt
	Lex::code_file.open(code_path, std::ifstream::in);
	std::ofstream f_out("../Docs/16231246_Lex_out.txt", std::ios::trunc|std::ofstream::ate);
	int r;
	if (!Lex::code_file || !f_out)
	{
		std::cout << "open failed";
		return -1;
	}
	unsigned long cnt = 0;
	while (true)
	{
		r = Lex::getsym();
		if (r == EOF)
		{
			break;
		}
		std::string rem_sym =
			(r == Lex::RSVD_WD) ? Lex::reservedWords.find(Lex::curElmt)->second :
			(r == Lex::RSVD_SYM) ? Lex::non_alpha_sym.find(Lex::curElmt)->second :
			(r == Lex::UNKNOWN) ? "UNKNOWN" :
			(r == Lex::IDEN) ? "IDEN" :
			(r == Lex::UNSGN_INT) ? "UNSGN_INT" :
			(r == Lex::SGL_CHARA) ? "SGL_CHARA" : /* (r == Lex::STRING) ? */ "STRING";
		f_out << (++cnt) << ' ' << rem_sym << "\t\t\t";
		if (r == Lex::UNSGN_INT)
		{
			f_out << Lex::curNum << std::endl;
		}
		else
		{
			f_out << Lex::curElmt << std::endl;
		}
	}
	if (Lex::code_file.is_open())
	{
		Lex::code_file.close();
	}
	return 0;
}
#endif