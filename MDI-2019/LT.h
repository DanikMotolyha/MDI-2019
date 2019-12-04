#pragma once
#include "IT.h"
#define LEXEMA_FIXSIZE 1			// ������������� ������ �������
#define LT_MAXSIZE 4096				// ������������ ���������� ����� � ������� ������
#define	LT_TI_NULLIDX 0xffffffff	// ��� �������� ������� ���������������
#define	LEX_NOT_OPERATION "--"		// ��� �������� ������� ���������������

#define END_OF_LEX '.'				// ������ ����� ������� ������

#define	LEX_IF 'q'						// ���������� if
#define	LEX_ELSE 'e'					// ���������� else
#define	LEX_TURN 'u'					// ���������� turn

#define LEX_TYPE 't'
#define LEX_INT 't'					// ������� ��� int
#define LEX_STRING 't'				// ������� ��� string
#define LEX_BOOL 't'				// ������� ��� bool

#define	LEX_ID 'i'					// ������� ��� ��������������
#define LEX_LITERAL 'l'				// ������� ��� ��������

#define	LEX_FUNCTION 'f'			// ������� ��� function
#define	LEX_MAIN 'm'				// ������� ��� main
#define LEX_NEW 'n'					// ������� ��� new
#define LEX_RETURN 'r'				// ������� ��� return
#define LEX_OUT 'o'					// ������� ��� out


#define LEX_SEMICOLON ';'			// ������� ��� ;
#define LEX_COMMA ','				// ������� ��� ,
#define LEX_LEFTBRACE '{'			// ������� ��� {
#define LEX_BRACELET '}'			// ������� ��� }
#define LEX_LEFTTHESIS '('			// ������� ��� (
#define LEX_RIGHTHESIS ')'			// ������� ��� )
#define LEX_EQUALLY '='				// ������� ��� =
#define LEX_OPERATION 'v'			// ����� �������

#define OPERATION_PLUS '+'				// �������� ��� +
#define OPERATION_MINUS '-'				// �������� ��� -
#define OPERATION_DEL '/'				// �������� ��� /
#define OPERATION_MULT '*'				// �������� ��� *

#define OPERATION_LEFT_SHIFT "<<"				// �������� ��� <<
#define OPERATION_RIGHT_SHIFT ">>"				// �������� ��� >>


#define LEX_COMPARE 'c'			// ������� ��� == < > <= >= !=
#define OPERATION_BIGGER '>'				// �������� ��� >
#define OPERATION_SMALER '<'				// �������� ��� <
#define OPERATION_EQUALY "=="					// �������� ��� ==
#define OPERATION_NOT_EQUALY "!="					// �������� ��� ==
#define OPERATION_BIGGER_AND_EQUALY ">="					// �������� ��� ==
#define OPERATION_SMALER_AND_EQUALY "<="					// �������� ��� ==

#define NAME_IF "if"
#define NAME_ELSE "else"
#define NAME_TURN "turn"
#define LEX_NEWPROC '@'

namespace LT			// ������� ������
{
	struct Entry		// ������ ������� ������
	{
		char lexema;	// �������
		int sn;		// ����� ������ � �������� ������
		int idxTI;	// ������ � ������� ��������������� ��� LT_LI_NULLIDX
		char value[3];	// ��� �������� � ������ ������ LEX_NOT_OPERATION !!!!
	};

	struct LexTable			// ��������� ������� ������
	{
		int size;			// ������� ������ ������� ������ 
		Entry* table;		// ������ ����� ������� ������
	};

	LexTable Create();// ������� ������� ������
	void Add(		// �������� ������ � ������� ������
		LexTable& lextable,			// ��������� ������� ������
		Entry entry);				// ������ ������� ������
	Entry GetEntry(						// �������� ������ ������� ������
		LexTable& lextable,				// ��������� ������� ������
		int n							// ����� ���������� ������
	);
	void Delete(LexTable& lextable);			// ������� ������� ������

}