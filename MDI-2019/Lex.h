#pragma once
#include "IT.h"
#include "LT.h"
#include "In.h"
namespace LEX
{
	void Create_LEX(In::IN in, IT::IdTable &it, LT::LexTable &lt);
}
int to_decimal(string a);
string to_binary(string a);