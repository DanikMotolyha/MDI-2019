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
	void Add(			// �������� ������ � ������� ���������������
		IdTable& it,	// ��������� ������� ���������������
		Entry entry)		// ������ ������� ���������������
	{
		if (it.size + 1 > TI_MAXSIZE) throw ERROR_THROW(105);
		it.table[it.size] = entry;
		it.size++;
	}
	Entry GetEntry(		// �������� ������ ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		int n)				// ����� ���������� ������
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