#pragma once

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cassert>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<set>
#include<stack>

#define DEBUG 1
#define INCLASS 1

constexpr auto data_seg_base = 0x10000000;
constexpr auto data_base = 0x10010000;		// string .etc starts from here
constexpr auto stack_pointer_init = 0x7fffeffc;
extern bool with_error;