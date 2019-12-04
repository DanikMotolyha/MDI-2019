#pragma once
#include "In.h"
#define ID_MAXSIZE 12				// максимальное количество символов в идентификаторе
#define TI_MAXSIZE 4096				// максимальное количество строк в таблице идентивикаторов
#define TI_INT_DEFAULT 0x00000000	// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT 0x00			// значение по умолчанию дл€ типа string
#define TI_NULLIDX	   0xffffffff	// нет элемента таблицы идентификатора
#define TI_STR_MAXSIZE 255			// макс длина стр
#define TI_INT_MAXSIZE 0x7FFFFFFF;





namespace IT			// таблица идентификаторов
{
	enum IDDATATYPE { INT = 1, STR = 2, BOOL = 3 };		// типы данных идентификаторов : integer, string, bool
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };		// типы идентификаторов : переменна€, функци€, параметр, литерал
	enum IDINTTYPE { BIN = 2, DEC = 10, HEX = 16};
	struct Entry			// строка таблицы идентификаторов
	{
		int idxfirstLE;				// индекс первой строки в таблице лексем
		char id[ID_MAXSIZE];		// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype;		// тип данных
		IDTYPE idtype;				// тип идентификатора 
		union
		{
			short bool_value;
			struct
			{
				int vint;
				IDINTTYPE representation;
			} chislo;
			struct
			{
				short len;						// количество символов в string
				char str;						// символы string // зачем тут char str[TI_STR_MAXSIZE - 1];
			} vstr[TI_STR_MAXSIZE];				// значение string
		} value;						// значение идентификатора
	};

	struct IdTable			// экземпл€р таблицы идент
	{
		int size;			// текущий размер таблицы идент < maxsize 
		Entry* table;		// массив строк таблицы идент
	};

	IdTable Create(			// создать таблицу идентификаторов
	);

	void Add(			// добавить строку в таблицу идентификаторов
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		Entry entry);		// строка таблицы идентификаторов

	Entry GetEntry(		// получить строку таблицы идентификаторов
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		int n);				// номер получаемой строки

	int IsId(					  // возврат: номер строки(если есть), TI_NULLIDX(если нет)
		IdTable& idtable,	  // экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE]); // идентификатор	

	void Delete(IdTable& idtable);		// удалить таблицу лексем (освободить пам€ть)
}
