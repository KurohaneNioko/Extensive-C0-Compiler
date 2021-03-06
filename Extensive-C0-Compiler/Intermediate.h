#pragma once
#include "SymbolHead.h"
#include "Compiler.h"

#if DEBUG
#define IMC_Out 1
#else
#define IMC_Out 0
#endif


typedef struct
{
	int BBno=0;
	std::string rst;
	std::string op;
	std::string num1;
	std::string num2;
} mcode;

namespace OP
{
	constexpr auto ADD = "+";	//x + a  b
	constexpr auto SUB = "-";
	constexpr auto MUL = "*";	// mfhi, mflo
	constexpr auto DIV = "/";	// if *2 /2 use << >>

	constexpr auto EQU = "==";	// stl...
	constexpr auto NEQ = "!=";
	constexpr auto GRT = ">";
	constexpr auto GREQ = ">=";
	constexpr auto LES = "<";
	constexpr auto LESEQ = "<=";

	constexpr auto SAVE_ARR = "[]=";	// sw sb --> arr []= 3 t
	constexpr auto READ_ARR = "=[]";	// lw lb --> t =[] arr 5
	
	constexpr auto SCAN = "scanf";		//la li syscall
	constexpr auto PRINT = "print";		

	constexpr auto PUSH_PARA = "push";	// push para into stack --> value_param1 push 0 0
	constexpr auto CALL = "call";		// push reg into stack
	
	constexpr auto RET = "ret";			// jr $31
	constexpr auto FUNC_END = "func_end";	//jr $31
	constexpr auto GOTO = "goto";	// j
	constexpr auto FUNC_BEGIN = "func_begin";	// func label
	constexpr auto LABEL = "label";	//if for while label
	constexpr auto EXIT = "exit";	// met return in main
}

namespace Med
{
	/* temporary var head, #1, #2, ... */
	constexpr auto temphd = "#";
	/* string head, ~xxx, ~sakura, ~19260817 */
	constexpr auto strhd = "~";
	/* label head, %1, %2, ... */
	constexpr auto labelhd = "%";


	/* intermediate codes all here */
	extern std::vector<mcode> itmd_code;

	std::string gen_temp(std::string &curFunc, int &lc, int cls);
	std::string gen_label();
	extern int temp_order;
	//std::string gen_str();

	bool is_operand_num(std::string &s, int &value);
	void addIMC(std::string rst, const std::string &op, std::string op1, std::string op2);
	void printIMC(std::ofstream&o);

}