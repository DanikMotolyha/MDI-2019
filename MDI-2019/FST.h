#pragma once
#include <iostream>
#define FST_SIZE 33

namespace FST
{	
	struct RELATION	// ребро:символ -> вершима графа переходов КА
	{
		char symbol;	// символ перехода
		short nnode;	// номер смежной вершины
		RELATION(
			char с = 0x00,	// символ перехода
			short ns = NULL	// новое состояние
		);
	};
	struct NODE // вершина графа переходов
	{
		short n_relation;	// количество инциндентных ребер
		RELATION *relations;	// инцидентные ребра
		NODE();
		NODE(
			short n,	// количество инциндентных ребер
			RELATION rel, ...	// список ребер
		);
	};
	struct FST			// недетерменированный конечный автомат
	{
		char* string;		// цепочка (строка, завершается 0x00)
		short position;		// текущая позиция в цепочке
		short nstates;		// количество состояний автомата
		NODE* nodes;		// граф переходов: [0] - начальное состояние, [nstate-1] - конечне
		short* rstates;		// возможные состояния автомата на данной позиции
		FST();
		FST(
			char* s,			// цепочка (строка, завершается 0x00)
			short ns,			// количество состояний автомата
			NODE n, ...);		// список состояний (граф переходов)
	};
	bool execute(		// выполнить распознавание цепочки
		FST &fst	// недетерминированный конечный автомат
	);
	FST * automat();
}

