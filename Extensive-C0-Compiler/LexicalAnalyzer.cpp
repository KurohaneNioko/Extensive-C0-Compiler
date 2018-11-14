#include "Compiler.h"
#include "LexerHead.h"
#define BACK_1_CHAR		{if(linePointer!=0){linePointer -= 1;}else{Lex::LineCounter-=1;codeLine="\n";}}
#define isALPHA(c)		(('a'<=c && c<='z') || ('A'<=c && c<='Z') || (c=='_'))
#define isWHITE(c)		(c=='\t' || c==' ' || c=='\n')
#define isSGL_CHAR(c)	(c=='+' || c=='-' || c=='*' || c=='/' || isALPHA(c) || bool(isdigit(c)))
#define isSGL_QTE(c)	(c=='\'')
#define isDBL_QTE(c)	(c=='"')
std::size_t linePointer = 0;	//next char stars from s[i]
std::string codeLine = "";

char readCharFromLine()
{
	if (linePointer == codeLine.size())
	{
		if (std::getline(Lex::code_file, codeLine))
		{
			linePointer = 0;
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
	return codeLine[linePointer++];
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
			return Lex::RSVD_WD;
		}
		else
		{
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
			catch(const std::out_of_range& oor){
#if DEBUG
				std::cout << "int Overflow at Line: " << Lex::LineCounter << " Colomn: " << (linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
				return Lex::UNKNOWN;
			}
			Lex::curNum = num_from_cur;
			return Lex::UNSGN_INT;
		}
		else
		{
#if DEBUG
			std::cout << "Invalid int at Line: " << Lex::LineCounter << " Colomn: " << (linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
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
			return Lex::UNKNOWN;
		}
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
			Lex::curElmt += c;
		}
		/* TODO: err-> char in string invalid
					   miss right double quote */
		/* now curElmt = ""xxx"" */
		if (Lex::curElmt[Lex::curElmt.size() - 1] != '"')
		{
#if DEBUG
			std::cout << "Miss right double quote: Line " << Lex::LineCounter << " Colomn: " << (linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
			return Lex::UNKNOWN;
		}
		if (!char_in_string)	//with right double quote, but with invalid char
		{
			/* TODO: warning*/
#if DEBUG
			std::cout << "Invalid char in string: Line " << Lex::LineCounter << " Colomn: " << (linePointer + 1 - Lex::curElmt.size()) << std::endl;
#endif
			return Lex::STRING;
		}
		return Lex::STRING;		//all ok
	}
	else
	{
		if (c == '+' || c == '-' || c == '*' || c == '/' ||
			c == '(' || c == ')' || c == '[' || c == ']' ||
			c == '{' || c == '}' || c == ';' || c == ',' )
	 	{
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
			return Lex::RSVD_SYM;
		}
		else if (c == '!')
		{
			c = readCharFromLine();
			if (c == '=')
			{
				curElmt += c;
				return Lex::RSVD_SYM;
			}
			else
			{
				BACK_1_CHAR
			}
		}
	}
#if DEBUG
	std::cout << "UNKNOWN word at Line: " << Lex::LineCounter << " Colomn: "<< (linePointer+1-Lex::curElmt.size()) << std::endl;
#endif
	return Lex::UNKNOWN;
}

#if Lexical_Out
int main(int argc, char** argv)
{
	std::string code_path(argv[1]);
	//../Grammar-Analysis/16231246_test.txt
	Lex::code_file.open(code_path, std::ifstream::in);
	std::ofstream f_out("../Grammar-Analysis/16231246_Lex_out.txt", std::ios::trunc|std::ofstream::ate);
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