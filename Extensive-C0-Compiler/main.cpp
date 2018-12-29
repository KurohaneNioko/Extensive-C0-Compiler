//#define _CRT_SECURE_NO_WARNINGS
#include"LexerHead.h"
#include"SymbolHead.h"
#include"SyntaxHead.h"
//#include"Intermediate.h"
#include"ObjectCode.h"

#if OPTIMIZE
#include"OptimzeHead.h"
#endif // OPT
/*
const int zero = 0;
const int one = 1, minus_two = -0002;
const char renn = '0';
const char first_alpha = 'a', first_captical = 'A';
int yyy[7], xxxx, x, zzzzzzz;
char testchar1, testchar2;
int fact(int t)
{
	if (t < 3)
		return(t);
	else
		return(fact(t - 1)*t);
}
int rt15()
{
	const int zero = 1;
	return(3 * 5 / one + one - zero);
}
char fun2(int a, int b, int c, int d, int e, int f)
{
	printf("%d", a + b * c*d / e - f);
	return('A');
}
void main()
{
	const int b = +01, c = 2, d = 3, e = 4;
	char ar[2];
	int r, m1[8];
	int aa, a;

	x = +-1;
	printf("%d", x);
	r = -4;
	printf("%d", r);
	aa = 6;
	printf("!@#$%%abcd114514ABCD963287~;: %d", fact(aa));
	ar[d*e + 6 * (minus_two + b - 1)] = fun2(x - r, aa, b, e, c, minus_two);
	printf("%c",(ar[zero / fact(4)]));
	ar[1] = '0';
	aa = -b * (ar[1] + rt15()) + (c - e * 9) + 2 * 'm';
	printf("%d", aa);
	a = aa;
	scanf("%d %d", &a, &x);
	if (a > 0)
	{
		printf("1 hit ");
		if (x <= 0) {
			r = a / x * a;
			printf("%d", r);
			printf("2 hit");
		}
		r = r + aa;
		printf("%d", r);
	}
	if (x != 0)
	{
		printf("3 hit ");
		if (a == -4)
		{
			r = r + 1;
			printf("%d", r);
			printf("4 hit ");
		}
	}
	if (a < 0)
	{
		printf("5 hit ");
		if (x >= 0)
		{
			r = r + a;
			printf("%d", r);
			printf("6 hit ");
		}
	}
	else
	{
		r = r * -1;
		printf("%d", r);
	}
	for (a = -2; a < d; a = a + 1)
	{
		x = x + e;
	}
	printf("%d", x);
}
*/


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
		Med::printIMC(symIRout);
#if OPTIMIZE
		std::string cp_ = cp;
		OPT::optinfofile = cp_.replace(cp_.begin() + cp_.find_last_of('.'), cp_.end(), "-optInfo.txt");
		OPT::allOptimize();
#endif
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