#pragma once
#include"Compiler.h"
#include"LexerHead.h"

struct errInfo
{
	int errtp;
	int row;
	int column;
	std::string word;
};
extern std::vector<errInfo> err;
extern std::map<int, std::string> errcode2real;
namespace ER
{
	void logER(int ertype);
	void writeERR(std::ofstream&o);
}
namespace ERT
{
	constexpr auto UNKNOWN_WORD = 0;
	constexpr auto INT_OVERFLOW = 1;
	constexpr auto CHAR_TOO_SHORT = 2;
	constexpr auto CHAR_TOO_LONG = 3;
	constexpr auto MISS_SINGLE_QUOTE = 4;
	constexpr auto UNSUPPORTED_CHAR = 5;
	constexpr auto MISS_DOUBLE_QUPTE = 6;

	constexpr auto EXPECT_INT_CONSTANT = 7;
	constexpr auto EXPECT_CHAR_CONSTANT = 8;
	constexpr auto EXPECT_TYPE_NAME = 9;
	constexpr auto NO_IDEN_AFTER_TYPE_NAME = 10;
	constexpr auto EXPECT_ASSIGN = 11;
	constexpr auto IDEN_REDEFINITION = 12;
	constexpr auto INVALID_ARRAY_LENGTH = 13;
	constexpr auto EXPECT_RIGHT_BRACKET = 14;
	constexpr auto EXPECT_SEMICOLON = 15;
	constexpr auto EXPECT_COMMA = 16;
	constexpr auto TYPE_DISMATCH = 17;
	constexpr auto NOT_ENOUGH_FUNCTION_PARAM = 18;
	constexpr auto TOO_MANY_FUNCTION_PARAMS = 19;
	constexpr auto IDEN_NO_DEFINITION = 20;
	constexpr auto WRONG_FACTOR = 21;
	constexpr auto MISS_RIGHT_PARENT = 22;
	constexpr auto INVALID_TYPE = 23;
	constexpr auto EXPECT_ARRAY = 24;
	constexpr auto EXPECT_INT = 25;
	constexpr auto INDEX_OUT_OF_RANGE = 26;
	constexpr auto EXPECT_RIGHT_BRACE = 27;
	constexpr auto EXPECT_FUNCTION = 28;
	constexpr auto EXPECT_FUNCTION_WITH_RETURN_VALUE = 29;
	constexpr auto EXPECT_NO_PARA_FUNCTION = 30;
	constexpr auto DIVIDE_ZERO = 31;
	constexpr auto MISS_LEFT_PARENT = 32;
	constexpr auto INVALID_SENTENCE = 33;
	constexpr auto EXPECT_VAR_OR_PARAM = 34;
	constexpr auto EXPECT_IDEN = 35;
	constexpr auto RETURN_VALUE_NOT_ALLOW = 36;
	constexpr auto NO_RETURN_VALUE = 37;
	constexpr auto EXPECT_ADD_OR_SUB = 38;
	constexpr auto NO_MAIN_FUNCTION = 39;
	constexpr auto MISS_LEFT_BRACKET = 40;
	constexpr auto EXPECT_PARA_FUNCTION = 41;

}