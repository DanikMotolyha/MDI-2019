#include <iostream>
#include "Error.h"  // ��������� ������
#include "In.h"		// ���� ��������� �����
#include "Log.h"	// ������ � ����������
#include "Parm.h"	// ��������� ����������
#include "LT.h"
#include "IT.h"
#include "Lex.h"
#include "GRB.h"
#include "MFST.h"
#include "Generation.h"
#include "PolishNotation.h"

// ������� :
/*
	1 / ������ ��������
	4 / ���������
*/


using namespace std;
int wmain(int agrc, wchar_t* agrv[])
{
	clock_t t0 = clock();
	setlocale(LC_ALL, "RUSSIAN");
	Log::LOG log = Log::INITLOG;
	Log::LOG Protocols = Log::INITLOG;
	try
	{
		//	1	-	�������� �� � �� 
		//			������ ������������ ����������� � ���������� log �����
		
		Parm::PARM parm = Parm::getparm(agrc, agrv);
		log = Log::getlog(parm.log);
		WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		LT::LexTable lt = LT::Create();
		IT::IdTable it = IT::Create();
		LEX::Create_LEX(in, it, lt);

		//	-	1

		//	2	-	������ ��������������� ����������� � 
		//			��������� ���������� � ������ � �������� .an

		Protocols = Log::getlog(parm.an);

		MFST::Write_to_An(lt, Protocols);
		

		//	- 2

		//	3	-	�������� ������ + ������ � �������� .table .lexical 
		
		PN::PolishNotation(it, lt);

		// ������ ��������� Lexical
		Protocols = Log::getlog(parm.Lexical);
		Log::WriteLT(lt, Protocols, in);

		Protocols = Log::getlog(parm.LexTable); // ������� �� � ��
		Log::WriteLT_ALL(lt, Protocols);
		Protocols = Log::getlog(parm.IdTable);
		Log::WriteIT_ALL(it, Protocols);
		//--------------
		//	-	3

		//	4	-	������ �������������� �����������

		//	-	4

		//	5	-	��������� � ��� ���������
		Protocols = Log::getlog(parm.out);
		Gen::Asm(lt, Protocols, it);

		//	-	5
		
		Log::End_of_MDI(log, t0);
		Log::Close(log);
		Log::Close(Protocols);
		cout << "��������� ���������� ��� ������!\n"; system("pause");
	}
	catch (Error::ERROR e)
	{
		if (e.id != 100)
			Log::WriteError(log, e);
		else
		{
			cout << "������ " << e.id << "  " << e.message << endl
				<< "---------------------------------------------------\n";
			system("pause");
		}
	}
}
