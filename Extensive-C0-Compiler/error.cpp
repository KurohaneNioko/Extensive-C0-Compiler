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
};

void ER::writeERR(std::ofstream&o)
{
	for (auto i = err.begin(); i != err.end(); i++)
		o << "Line " << i->row << ", Column " << i->row
			<< ", near " << i->word << " : " << errcode2real[i->errtp] << std::endl;
}
