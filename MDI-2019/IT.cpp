#include "IT.h"
#include "Error.h"
#include <iostream>

namespace IT {
	IdTable Create()
	{
		IdTable it;
		it.size = 0;
		it.table = new Entry[TI_MAXSIZE];
		return it;
	}
	void Add(			// добавить строку в таблицу идентификаторов
		IdTable& it,	// экземпляр таблицы идентификаторов
		Entry entry)		// строка таблицы идентификаторов
	{
		if (it.size + 1 > TI_MAXSIZE) throw ERROR_THROW(105);
		it.table[it.size] = entry;
		it.size++;
	}
	Entry GetEntry(		// получить строку таблицы идентификаторов
		IdTable& idtable,	// экземпляр таблицы идентификаторов
		int n)				// номер получаемой строки
	{
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(id, idtable.table[i].id))
				return i;
		}
		return -1;
	}



	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}
}