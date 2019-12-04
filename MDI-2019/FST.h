#pragma once
#include <iostream>
#define FST_SIZE 33

namespace FST
{	
	struct RELATION	// �����:������ -> ������� ����� ��������� ��
	{
		char symbol;	// ������ ��������
		short nnode;	// ����� ������� �������
		RELATION(
			char � = 0x00,	// ������ ��������
			short ns = NULL	// ����� ���������
		);
	};
	struct NODE // ������� ����� ���������
	{
		short n_relation;	// ���������� ������������ �����
		RELATION *relations;	// ����������� �����
		NODE();
		NODE(
			short n,	// ���������� ������������ �����
			RELATION rel, ...	// ������ �����
		);
	};
	struct FST			// ������������������� �������� �������
	{
		char* string;		// ������� (������, ����������� 0x00)
		short position;		// ������� ������� � �������
		short nstates;		// ���������� ��������� ��������
		NODE* nodes;		// ���� ���������: [0] - ��������� ���������, [nstate-1] - �������
		short* rstates;		// ��������� ��������� �������� �� ������ �������
		FST();
		FST(
			char* s,			// ������� (������, ����������� 0x00)
			short ns,			// ���������� ��������� ��������
			NODE n, ...);		// ������ ��������� (���� ���������)
	};
	bool execute(		// ��������� ������������� �������
		FST &fst	// ������������������� �������� �������
	);
	FST * automat();
}

