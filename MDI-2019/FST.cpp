#include "FST.h"

FST::RELATION::RELATION(char �, short nn)	// �����:������ -> ������� ����� ��������� ��
{
	symbol = �;			// ������ ��������
	nnode = nn;			// ����� ������� �������
};
FST::NODE::NODE()			// �� ���������  // ������� ����� ���������
{
	n_relation = 0;
	RELATION *relations = NULL;
}				

FST::FST * FST::automat()
{
FST *AT = new FST[FST_SIZE];
#pragma region 0	����������� ���� : ���������
	AT[0] = FST(nullptr, 7,
		NODE(1, RELATION('s', 1)),
		NODE(1, RELATION('t', 2)),
		NODE(1, RELATION('r', 3)),
		NODE(1, RELATION('i', 4)),
		NODE(1, RELATION('n', 5)),
		NODE(1, RELATION('g', 6)),
		NODE());
#pragma endregion
#pragma region 1	����������� ���� : ����������� �����
	AT[1] = FST(nullptr, 4,
		NODE(1, RELATION('i', 1)),
		NODE(1, RELATION('n', 2)),
		NODE(1, RELATION('t', 3)),
		NODE());
#pragma endregion
#pragma region 2	����������� ���� : �������
	AT[2] = FST(nullptr, 5,
		NODE(1, RELATION('b', 1)),
		NODE(1, RELATION('o', 2)),
		NODE(1, RELATION('o', 3)),
		NODE(1, RELATION('l', 4)),
		NODE());
#pragma endregion
#pragma region 3	����������� ������� function
	AT[3] = FST(nullptr, 9,
		NODE(1, RELATION('f', 1)),
		NODE(1, RELATION('u', 2)),
		NODE(1, RELATION('n', 3)),
		NODE(1, RELATION('c', 4)),
		NODE(1, RELATION('t', 5)),
		NODE(1, RELATION('i', 6)),
		NODE(1, RELATION('o', 7)),
		NODE(1, RELATION('n', 8)),
		NODE());
#pragma endregion
#pragma region 4	���������� new
	AT[4] = FST(nullptr, 4,
		NODE(1, RELATION('n', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('w', 3)),
		NODE());
#pragma endregion
#pragma region 5	����� ������� return
	AT[5] = FST(nullptr, 7,
		NODE(1, RELATION('r', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('t', 3)),
		NODE(1, RELATION('u', 4)),
		NODE(1, RELATION('r', 5)),
		NODE(1, RELATION('n', 6)),
		NODE());
#pragma endregion
#pragma region 6	����� out
	AT[6] = FST(nullptr, 4,
		NODE(1, RELATION('o', 1)),
		NODE(1, RELATION('u', 2)),
		NODE(1, RELATION('t', 3)),
		NODE());
#pragma endregion
#pragma region 7	������� ������� main
	AT[7] = FST(nullptr, 5,
		NODE(1, RELATION('m', 1)),
		NODE(1, RELATION('a', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE());
#pragma endregion
#pragma region 8	������ ;
	AT[8] = FST(nullptr, 2,
		NODE(1, RELATION(';', 1)),
		NODE());
#pragma endregion
#pragma region 9	������ ,
	AT[9] = FST(nullptr, 2,
		NODE(1, RELATION(',', 1)),
		NODE());
#pragma endregion
#pragma region 10	������ {
	AT[10] = FST(nullptr, 2,
		NODE(1, RELATION('{', 1)),
		NODE());
#pragma endregion
#pragma region 11	������ }
	AT[11] = FST(nullptr, 2,
		NODE(1, RELATION('}', 1)),
		NODE());
#pragma endregion
#pragma region 12	������ (
	AT[12] = FST(nullptr, 2,
		NODE(1, RELATION('(', 1)),
		NODE());
#pragma endregion
#pragma region  13	������ )
	AT[13] = FST(nullptr, 2,
		NODE(1, RELATION(')', 1)),
		NODE());
#pragma endregion
#pragma region 14	������ =
	AT[14] = FST(nullptr, 2,
		NODE(1, 
			RELATION('=', 1)),
		NODE());
#pragma endregion
#pragma region 15	�������� << >>
	AT[15] = FST(nullptr, 3,
		NODE(2, RELATION('<', 1), RELATION('>', 1)),
		NODE(2, RELATION('<', 2), RELATION('>', 2)),
		NODE());
#pragma endregion
#pragma region 16	�������� + * / -
	AT[16] = FST(nullptr, 2,
		NODE(4, RELATION('+', 1),
			RELATION('*', 1),
			RELATION('/', 1),
			RELATION('-', 1)),
		NODE());
#pragma endregion
#pragma region 17	��������� ==
	AT[17] = FST(nullptr, 3,
		NODE(1, RELATION('=', 1)),
		NODE(1, RELATION('=', 2)),
		NODE());
#pragma endregion
#pragma region 18	��������� !=
	AT[18] = FST(nullptr, 3,
		NODE(1, RELATION('!', 1)),
		NODE(1, RELATION('=', 2)),
		NODE());
#pragma endregion
#pragma region 19	��������� <=
	AT[19] = FST(nullptr, 3,
		NODE(1, RELATION('<', 1)),
		NODE(1, RELATION('=', 2)),
		NODE());
#pragma endregion
#pragma region 20	��������� >=
	AT[20] = FST(nullptr, 3,
		NODE(1, RELATION('>', 1)),
		NODE(1, RELATION('=', 2)),
		NODE());
#pragma endregion
#pragma region 21	��������� < >
	AT[21] = FST(nullptr, 2,
		NODE(2, RELATION('>', 1),
				RELATION('<', 1)),
		NODE());
#pragma endregion
#pragma region 22	���������� IF
	AT[22] = FST(nullptr, 3,
		NODE(1, RELATION('i', 1)),
		NODE(1, RELATION('f', 2)),
		NODE());
#pragma endregion
#pragma region 23	���������� else
	AT[23] = FST(nullptr, 5,
		NODE(1, RELATION('e', 1)),
		NODE(1, RELATION('l', 2)),
		NODE(1, RELATION('s', 3)),
		NODE(1, RELATION('e', 4)),
		NODE());
#pragma endregion
#pragma region 24	���������� turn
	AT[24] = FST(nullptr, 5,
		NODE(1, RELATION('t', 1)),
		NODE(1, RELATION('u', 2)),
		NODE(1, RELATION('r', 3)),
		NODE(1, RELATION('n', 4)),
		NODE());
#pragma endregion
#pragma region 25	������� INT 2-�� �.C
	AT[25] = FST(nullptr, 3,		// ������� int 2-��
		NODE(1, RELATION('2', 1)),
		NODE(1, RELATION('x', 2)),
		NODE(2, RELATION('1', 2), RELATION('0', 2)));
#pragma endregion
#pragma region 26	������� INT 10-�� �.C
	AT[26] = FST(nullptr, 1,		// ������� int 10-��
		NODE(10,
			RELATION('1', 0), RELATION('4', 0),
			RELATION('2', 0), RELATION('5', 0),
			RELATION('3', 0), RELATION('6', 0),
			RELATION('7', 0), RELATION('8', 0),
			RELATION('9', 0), RELATION('0', 0)));
#pragma endregion
#pragma region 27	������� INT 16-�� �.C
	AT[27] = FST(nullptr, 3,		// ������� int 16-��
		NODE(1, RELATION('0', 1)),
		NODE(1, RELATION('x', 2)),
		NODE(16,
			RELATION('1', 2), RELATION('4', 2),
			RELATION('2', 2), RELATION('5', 2),
			RELATION('3', 2), RELATION('6', 2),
			RELATION('7', 2), RELATION('8', 2),
			RELATION('9', 2), RELATION('A', 2),
			RELATION('B', 2), RELATION('C', 2),
			RELATION('D', 2), RELATION('E', 2), RELATION('F', 2)));
#pragma endregion
#pragma region 28	������� ������� : ������������ true false
	AT[28] = FST(nullptr, 6,
		NODE(2, RELATION('f', 1), RELATION('t', 1)),
		NODE(2, RELATION('a', 2), RELATION('r', 2)),
		NODE(2, RELATION('l', 3), RELATION('u', 3)),
		NODE(2, RELATION('s', 4), RELATION('e', 5)),
		NODE(1, RELATION('e', 5)),
		NODE());
#pragma endregion
#pragma region 29	������� ����������� ���������� pow
	AT[29] = FST(nullptr, 4,
		NODE(1, RELATION('p', 1)),
		NODE(1, RELATION('o', 2)),
		NODE(1, RELATION('w', 3)),
		NODE());
#pragma endregion
#pragma region 30	������� ����������� ���������� sqrt
	AT[30] = FST(nullptr, 5,
		NODE(1, RELATION('s', 1)),
		NODE(1, RELATION('q', 2)),
		NODE(1, RELATION('r', 3)),
		NODE(1, RELATION('t', 4)),
		NODE());
#pragma endregion
#pragma region 31	������� ��������� : ������������ [�...�] [�..�] {< > : ; - + / * ( ) { } _ = ! , ������} [0..9] [a..z] [A..Z] ������ � ����� ������ ' '
	AT[31] = FST(nullptr, 3,
		NODE(1,
			RELATION('\'', 1)),
		NODE(146,
			RELATION(' ', 1), RELATION('-', 1), RELATION('+', 1), RELATION('/', 1), RELATION('*', 1), RELATION('_', 1),
			RELATION('(', 1), RELATION(')', 1), RELATION('}', 1), RELATION('{', 1), RELATION(':', 1), RELATION(';', 1),
			RELATION('<', 1), RELATION('>', 1), RELATION('!', 1), RELATION('=', 1), RELATION(',', 1),

			RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),
			RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
			RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),
			RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
			RELATION('y', 1), RELATION('z', 1),

			RELATION('A', 1), RELATION('B', 1), RELATION('C', 1), RELATION('D', 1), RELATION('E', 1), RELATION('F', 1),
			RELATION('G', 1), RELATION('H', 1), RELATION('I', 1), RELATION('J', 1), RELATION('K', 1), RELATION('L', 1),
			RELATION('M', 1), RELATION('N', 1), RELATION('O', 1), RELATION('P', 1), RELATION('Q', 1), RELATION('R', 1),
			RELATION('S', 1), RELATION('T', 1), RELATION('U', 1), RELATION('V', 1), RELATION('W', 1), RELATION('X', 1),
			RELATION('Y', 1), RELATION('Z', 1),

			RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
			RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),

			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),

			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
			RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),

			RELATION('\'', 2)),
		NODE());
#pragma endregion
#pragma region 32	�������������� ����������� : [0..9] {_} [a..z] [A..Z]
	AT[32] = FST(nullptr, 1,		// ��������������
		NODE(63,
			
			RELATION('_', 0),

			RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),
			RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0), RELATION('0', 0),
						  									  									  
			RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0), RELATION('f', 0),
			RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0), RELATION('k', 0), RELATION('l', 0),
			RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0), RELATION('q', 0), RELATION('r', 0),
			RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0),
			RELATION('y', 0), RELATION('z', 0),
						 
			RELATION('A', 0), RELATION('B', 0), RELATION('C', 0), RELATION('D', 0), RELATION('E', 0), RELATION('F', 0),
			RELATION('G', 0), RELATION('H', 0), RELATION('I', 0), RELATION('J', 0), RELATION('K', 0), RELATION('L', 0),
			RELATION('M', 0), RELATION('N', 0), RELATION('O', 0), RELATION('P', 0), RELATION('Q', 0), RELATION('R', 0),
			RELATION('S', 0), RELATION('T', 0), RELATION('U', 0), RELATION('V', 0), RELATION('W', 0), RELATION('X', 0),
			RELATION('Y', 0), RELATION('Z', 0)));																	
#pragma endregion

return AT;
}
FST::NODE::NODE(short n, RELATION rel, ...) // � �����������
{
	n_relation = n;
	RELATION *p = &rel;
	relations = new RELATION[n];
	for (short i = 0; i < n; i++) relations[i] = p[i];
}
FST::FST::FST()
{
	string = nullptr;
}
FST::FST::FST(char* s, short ns, NODE n, ...)
{
	string = s;																				// ������� (������, ����������� 0x00)
	nstates = ns;																			// ���������� ��������� ��	
	nodes = new NODE[ns];																	// ���� ���������
	NODE *p = &n;																			// ���� ���������: [0] - ��������� ���������, [nstate-1] - �������
	for (int k = 0; k < ns; k++) nodes[k] = p[k];
	rstates = new short[nstates];															// ��������� ��������� �� ������������ �������
	memset(rstates, 0xff, sizeof(short)*nstates);
	rstates[0] = 0;
	position = -1;																			// ������ ������� ( �� � execute ����� ��������� � 0 ��������)
}
bool step(FST::FST &fst, short* &rstates)													//���� ��� ��������
{
	bool rc = false;
	std::swap(rstates, fst.rstates);														// ����� ��������	� ������ �������� -1 �� 0
	for (short i = 0; i < fst.nstates; i++)													// ������ ���� ��������� 
	{
		if (rstates[i] == fst.position)														// �������� ���������� ��������� � �������� � �������
			for (short j = 0; j < fst.nodes[i].n_relation; j++)								// ��� ��� ���� �� ��������� -> �� ������
			{																				// �� ������ ����� ���������
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])			// �������� ������� ����� � �������� �������
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;		// ����������� ���� ��� ���������� ���� �� ������� 
																							//������ ������ ��� ���������
					rc = true;
				};
			};
	};
	return rc;
};
bool FST::execute(FST &fst)
{
	short *rstates = new short[fst.nstates];
	memset(rstates, 0xff, sizeof(short)*fst.nstates);
	//----------------------------------------------------
	fst.rstates = new short[fst.nstates];															// ��������� ��������� �� ������������ �������
	memset(fst.rstates, 0xff, sizeof(short)*fst.nstates);
	fst.rstates[0] = 0;
	fst.position = -1;
	//----------------------------------------------------
	short lstring = strlen(fst.string);						// �� ����� ������� (��� ��������)
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++)
	{
		fst.position++;				// ���������� �������
		rc = step(fst, rstates);	// ���� ��� ��������
	};
	delete[] rstates;
	return(rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}
