#pragma once
#include "Compiler.h"

typedef struct
{
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

	constexpr auto SAVE_ARR = "[]=";	// sw sb
	constexpr auto READ_ARR = "=[]";	// lw lb --> t =[] arr 5
	
	constexpr auto SCAN = "scanf";		//la li syscall
	constexpr auto PRINT = "print";		

	constexpr auto PUSH_PARA = "push";	// push para into stack
	constexpr auto CALL = "call";		// push reg into stack
	constexpr auto RET = "ret";			// save ret_val to $v0, sp+, fp+
	
	constexpr auto GOTO = "goto";	// j
	constexpr auto FUNC_BEGIN = "func_begin";	// func label
	constexpr auto LABEL = "label";	//if for while label
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

	std::string gen_temp();
	std::string gen_label();
	std::string gen_str();

	int *is_operand_num(std::string &s);
	void addIMC(std::string rst, std::string op, std::string op1, std::string op2);

}