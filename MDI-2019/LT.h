#pragma once
#include "IT.h"
#define LEXEMA_FIXSIZE 1			// фиксированный размер лексемы
#define LT_MAXSIZE 4096				// максимальное количество строк в таблице лексем
#define	LT_TI_NULLIDX 0xffffffff	// нет элемента таблицы идентификаторов
#define	LEX_NOT_OPERATION "--"		// нет элемента таблицы идентификаторов

#define END_OF_LEX '.'				// символ конца таблицы лексем

#define	LEX_IF 'q'						// инструкция if
#define	LEX_ELSE 'e'					// инструкция else
#define	LEX_TURN 'u'					// инструкция turn

#define LEX_TYPE 't'
#define LEX_INT 't'					// лексема для int
#define LEX_STRING 't'				// лексема для string
#define LEX_BOOL 't'				// лексема для bool

#define	LEX_ID 'i'					// лексема для идентификатора
#define LEX_LITERAL 'l'				// лексема для литерала

#define	LEX_FUNCTION 'f'			// лексема для function
#define	LEX_MAIN 'm'				// лексема для main
#define LEX_NEW 'n'					// лексема для new
#define LEX_RETURN 'r'				// лексема для return
#define LEX_OUT 'o'					// лексема для out


#define LEX_SEMICOLON ';'			// лексема для ;
#define LEX_COMMA ','				// лексема для ,
#define LEX_LEFTBRACE '{'			// лексема для {
#define LEX_BRACELET '}'			// лексема для }
#define LEX_LEFTTHESIS '('			// лексема для (
#define LEX_RIGHTHESIS ')'			// лексема для )
#define LEX_EQUALLY '='				// лексема для =
#define LEX_OPERATION 'v'			// общая лексема

#define OPERATION_PLUS '+'				// операция для +
#define OPERATION_MINUS '-'				// операция для -
#define OPERATION_DEL '/'				// операция для /
#define OPERATION_MULT '*'				// операция для *

#define OPERATION_LEFT_SHIFT "<<"				// операция для <<
#define OPERATION_RIGHT_SHIFT ">>"				// операция для >>


#define LEX_COMPARE 'c'			// лексема для == < > <= >= !=
#define OPERATION_BIGGER '>'				// операция для >
#define OPERATION_SMALER '<'				// операция для <
#define OPERATION_EQUALY "=="					// операция для ==
#define OPERATION_NOT_EQUALY "!="					// операция для ==
#define OPERATION_BIGGER_AND_EQUALY ">="					// операция для ==
#define OPERATION_SMALER_AND_EQUALY "<="					// операция для ==

#define NAME_IF "if"
#define NAME_ELSE "else"
#define NAME_TURN "turn"
#define LEX_NEWPROC '@'

namespace LT			// таблица лексем
{
	struct Entry		// строка таблицы лексем
	{
		char lexema;	// лексема
		int sn;		// номер строки в исходном тексте
		int idxTI;	// индекс в таблице идентификаторов или LT_LI_NULLIDX
		char value[3];	// для операций в другом случае LEX_NOT_OPERATION !!!!
	};

	struct LexTable			// экземпляр таблицы лексем
	{
		int size;			// текущий размер таблицы лексем 
		Entry* table;		// массив строк таблицы лексем
	};

	LexTable Create();// создать таблицу лексем
	void Add(		// добавить строку в таблицу лексем
		LexTable& lextable,			// экземпляр таблицы лексем
		Entry entry);				// строка таблицы лексем
	Entry GetEntry(						// получить строку таблицы лексем
		LexTable& lextable,				// экземпляр таблицы лексем
		int n							// номер получаемой строки
	);
	void Delete(LexTable& lextable);			// удалить таблицу лексем

}