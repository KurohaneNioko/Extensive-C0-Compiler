
#include"LexerHead.h"
#include"SymbolHead.h"
#include"SyntaxHead.h"
//#include"Intermediate.h"
#include"ObjectCode.h"


int main(int argc, char** argv)
{
	std::string code_path(argv[1]);
	//../Docs/16231246_test.txt
	Lex::code_file.open(code_path, std::ifstream::in);
	//std::ofstream f_out("../Docs/16231246_Syn_out.txt", std::ios::trunc | std::ofstream::ate);
	//int r;
	if (!Lex::code_file)// || !f_out)
	{
		std::cout << "open failed";
		return -1;
	}
	unsigned long cnt = 0;
	Syn::program();
	std::cout << std::endl;
	Med::printIMC();
	OC::Med2Mips();
	std::cout << std::endl;
	ST::printSym();
	if (Lex::code_file.is_open())
	{
		Lex::code_file.close();
	}
	//system("pause");
	return 0;
}