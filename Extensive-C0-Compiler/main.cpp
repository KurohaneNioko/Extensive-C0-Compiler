#include"LexerHead.h"
#include"SymbolHead.h"
#include"SyntaxHead.h"
//#include"Intermediate.h"
#include"ObjectCode.h"

#if OPTIMIZE
#include"OptimzeHead.h"
#endif // OPT

int main(int argc, char** argv)
{
#if INCLASS
	std::string code_path;
	std::cout << "source code path: " << std::endl;
	std::cin >> code_path;
#else
	std::string code_path(argv[1]);
	
#endif
	std::string asm_path("../mipsr.asm");
	//../Docs/16231246_test.txt
	Lex::code_file.open(code_path, std::ifstream::in);
	//std::ofstream f_out("../Docs/16231246_Syn_out.txt", std::ios::trunc | std::ofstream::ate);
	if (!Lex::code_file)// || !f_out)
	{
		std::cout << "open failed";
		system("pause");
		return -1;
	}
	std::string cp = code_path;
	std::string symIR_path = code_path.replace(code_path.begin() + code_path.find_last_of('.'), code_path.end(), "-sym+IR.txt");
	Syn::program();
	std::ofstream symIRout(symIR_path);
	if (!with_error)
	{
#if OPTIMIZE
		std::string cp_ = cp;
		OPT::optinfofile = cp_.replace(cp_.begin() + cp_.find_last_of('.'), cp_.end(), "-optInfo.txt");
		OPT::allOptimize();
#endif
		Med::printIMC(symIRout);
		symIRout << std::endl;
		OC::Med2Mips(asm_path);
		ST::printSym(symIRout);
	}
	else
	{
		ER::writeERR(symIRout);
		std::cout << "Compile ERROR!" << std::endl;
		ST::printSym(symIRout);
		system("pause");
	}
	if (Lex::code_file.is_open())
		Lex::code_file.close();
	return 0;
}