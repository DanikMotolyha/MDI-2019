#pragma once
#include "IT.h"
#include "LT.h"
namespace PN
{
	int priority(char a);
	void PolishNotation(IT::IdTable &it, LT::LexTable &lt);
	void Conv_V(LT::LexTable* lextable, IT::IdTable* idtable, int lextable_pos);
}