
#include"LexerHead.h"
#include"SymbolHead.h"
#include"SyntaxHead.h"
//#include"Intermediate.h"
#include"ObjectCode.h"



int main(int argc, char** argv)
{
#if INCLASS
	std::string code_path;
	std::cout << "source code path: " << std::endl;
	std::cin >> code_path;
	std::string asm_path;
	std::cout << "asm path: " << std::endl;
	std::cin >> asm_path;
#else
	std::string code_path(argv[1]);
	std::string asm_path("../mipsr.asm");
#endif
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
	std::string symIR_path = code_path.replace(code_path.begin() + code_path.find_last_of('.'), code_path.end(), "-sym+IR.txt");
	std::ofstream symIRout(symIR_path);
	Syn::program();
	Med::printIMC(symIRout);
	symIRout << std::endl;
	OC::Med2Mips(asm_path);
	ST::printSym(symIRout);
	if (Lex::code_file.is_open())
	{
		Lex::code_file.close();
	}
	//system("pause");
	return 0;
}