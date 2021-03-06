#include"Error.h"

bool with_error = false;
std::vector<errInfo> err;
void ER::logER(int ertype)
{
	struct errInfo ei;
	ei.errtp = ertype;
	ei.row = Lex::LineCounter;
	ei.column = Lex::linePointer + 1 - Lex::curElmt.size();
	ei.word = Lex::curElmt;
	err.push_back(ei);
	with_error = true;
}

std::map<int, std::string> errcode2real = 
{
	{ERT::UNKNOWN_WORD, "UNKNOWN_WORD"},
	{ERT::INT_OVERFLOW, "INT_OVERFLOW"},
	{ERT::CHAR_TOO_SHORT, "CHAR_TOO_SHORT"},
	{ERT::CHAR_TOO_LONG, "CHAR_TOO_LONG"},
	{ERT::MISS_SINGLE_QUOTE, "MISS_SINGLE_QUOTE"},
	{ERT::UNSUPPORTED_CHAR, "UNSUPPORTED_CHAR"},
	{ERT::MISS_DOUBLE_QUPTE, "MISS_DOUBLE_QUPTE"},
	{ERT::EXPECT_INT_CONSTANT, "EXPECT_INT_CONSTANT"},
	{ERT::EXPECT_CHAR_CONSTANT, "EXPECT_CHAR_CONSTANT"},
	{ERT::EXPECT_TYPE_NAME, "EXPECT_TYPE_NAME"},
	{ERT::NO_IDEN_AFTER_TYPE_NAME, "NO_IDEN_AFTER_TYPE_NAME"},
	{ERT::EXPECT_ASSIGN, "EXPECT_ASSIGN"},
	{ERT::IDEN_REDEFINITION, "IDEN_REDEFINITION"},
	{ERT::INVALID_ARRAY_LENGTH, "INVALID_ARRAY_LENGTH"},
	{ERT::EXPECT_RIGHT_BRACKET, "EXPECT_RIGHT_BRACKET"},
	{ERT::EXPECT_SEMICOLON, "EXPECT_SEMICOLON"},
	{ERT::EXPECT_COMMA, "EXPECT_COMMA"},
	{ERT::TYPE_DISMATCH, "TYPE_DISMATCH"},
	{ERT::NOT_ENOUGH_FUNCTION_PARAM, "NOT_ENOUGH_FUNCTION_PARAM"},
	{ERT::TOO_MANY_FUNCTION_PARAMS, "TOO_MANY_FUNCTION_PARAMS"},
	{ERT::IDEN_NO_DEFINITION, "IDEN_NO_DEFINITION"},
	{ERT::WRONG_FACTOR, "WRONG_FACTOR"},
	{ERT::MISS_RIGHT_PARENT, "MISS_RIGHT_PARENT"},
	{ERT::INVALID_TYPE, "INVALID_TYPE"},
	{ERT::EXPECT_ARRAY, "EXPECT_ARRAY"},
	{ERT::EXPECT_INT, "EXPECT_INT"},
	{ERT::INDEX_OUT_OF_RANGE, "INDEX_OUT_OF_RANGE"},
	{ERT::EXPECT_RIGHT_BRACE, "EXPECT_RIGHT_BRACE"},
	{ERT::EXPECT_FUNCTION, "EXPECT_FUNCTION"},
	{ERT::EXPECT_FUNCTION_WITH_RETURN_VALUE, "EXPECT_FUNCTION_WITH_RETURN_VALUE"},
	{ERT::EXPECT_NO_PARA_FUNCTION, "EXPECT_NO_PARA_FUNCTION"},
	{ERT::DIVIDE_ZERO, "DIVIDE_ZERO"},
	{ERT::MISS_LEFT_PARENT, "MISS_LEFT_PARENT"},
	{ERT::INVALID_SENTENCE, "INVALID_SENTENCE"},
	{ERT::EXPECT_VAR_OR_PARAM, "EXPECT_VAR_OR_PARAM"},
	{ERT::EXPECT_IDEN, ""},
	{ERT::RETURN_VALUE_NOT_ALLOW, "RETURN_VALUE_NOT_ALLOW"},
	{ERT::NO_RETURN_VALUE, "NO_RETURN_VALUE"},
	{ERT::EXPECT_ADD_OR_SUB, "EXPECT_ADD_OR_SUB"},
	{ERT::NO_MAIN_FUNCTION, "NO_MAIN_FUNCTION"},
	{ERT::MISS_LEFT_BRACKET, "MISS_LEFT_BRACKET"},
	{ERT::EXPECT_PARA_FUNCTION, "EXPECT_PARA_FUNCTION"}
};

void ER::writeERR(std::ofstream&o)
{
	for (auto i = err.begin(); i != err.end(); i++)
		o << "Line " << i->row << ", Column " << i->column
			<< ", near " << i->word << " : " << errcode2real[i->errtp] << std::endl;
}
