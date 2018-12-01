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
	constexpr auto ADD = "+";
	constexpr auto SUB = "-";
	constexpr auto MUL = "*";
	constexpr auto DIV = "/";
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
}