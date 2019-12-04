#include "Parm.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include "FST.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
// написаны ошибки :
/*
	1 ошибка - превышение размера для ЛТ
	2 ошибка - превышение размера для ТИ
	3 ошибка - превышение размера идентификатора
	4 ошибка - не распознана лексема
	5 ошибка - превышение размера литерала(строка)
*/
namespace LT
{
	LexTable Create()
	{
		LexTable lt;
		lt.size = 0;
		lt.table = new Entry[LT_MAXSIZE];
		return lt;
	}
	void Add(LexTable& lt, Entry entry)
	{
		if (lt.size + 1 > LT_MAXSIZE) throw ERROR_THROW(106);
		lt.table[lt.size++] = entry;
	}


	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}
}
