#pragma once
#define DEBUG 1
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cassert>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<set>

constexpr auto data_seg_base = 0x10000000;
constexpr auto data_base = 0x10010000;		// string .etc starts from here
constexpr auto stack_pointer_init = 0x7fffeffc;