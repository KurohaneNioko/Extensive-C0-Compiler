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

}