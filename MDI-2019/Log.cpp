#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include <cstdlib>
#include <cwchar>
#include <iomanip>
#include <ctime>
using namespace std;
namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG lg;
		lg.stream = new std::wofstream(logfile);
		if (!lg.stream)
		{
			throw ERROR_THROW(112);
		}
		else
		{
			wcscpy_s(lg.logfile, logfile);
			return lg;
		}
	}
	/*
	void WriteLine(LOG log, const char* c, ...)
	{
		const char **ptr = &c;
		int k = 0;
		while (ptr[k] != "")
		{
			*log.stream << ptr[k];
			k++;
		}
	}*/
	//void WriteLine(LOG log, const wchar_t* c, ...)
	//{
	//	char p[100];
	//	const wchar_t **ptr = &c;
	//	int k = 0;
	//	while (ptr[k] != L"")
	//	{
	//		wcstombs(p, ptr[k], 50);
	//		*log.stream << p;
	//		k++;
	//	}
	//}
	void WriteLog(LOG log)
	{
		*log.stream << "---- Протокол по работе MDI-2019 -------- Дата: ";
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];                              // строка, в которой будет храниться текущее время
		time(&rawtime);						// текущая дата в секундах
		timeinfo = localtime(&rawtime);               // преобразование секунд в локальное время
		strftime(buffer, 20, "%x %X", timeinfo);      // преобразование даты в строку
		*log.stream << buffer;
		*log.stream << " ----\n";
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char *in = new char[IN_MAX_LEN_TEXT];
		char *out = new char[IN_MAX_LEN_TEXT];
		char *logg = new char[IN_MAX_LEN_TEXT];
		char *an = new char[IN_MAX_LEN_TEXT];
		char *IdTable = new char[IN_MAX_LEN_TEXT];
		char *LexTable = new char[IN_MAX_LEN_TEXT];
		char *Lexical = new char[IN_MAX_LEN_TEXT];
		int x = wcstombs(in, parm.in, wcslen(parm.in));		in[x] = '\0';
		x = wcstombs(out, parm.out, wcslen(parm.out));		out[x] = '\0';
		x = wcstombs(logg, parm.log, wcslen(parm.log));		logg[x] = '\0';
		x = wcstombs(an, parm.an, wcslen(parm.an));		an[x] = '\0';
		x = wcstombs(IdTable, parm.IdTable, wcslen(parm.IdTable));		IdTable[x] = '\0';
		x = wcstombs(LexTable, parm.LexTable, wcslen(parm.LexTable));		LexTable[x] = '\0';
		x = wcstombs(Lexical, parm.Lexical, wcslen(parm.Lexical));		Lexical[x] = '\0';
		*log.stream << "------ Параметры ----------\n"
			<< "-in: " << in << '\n';
		*log.stream << "------ Протоколы ----------\n"
			<< ".log  ->  " << logg << '\n'
			<< ".out  ->  " << out << '\n'
			<< ".an  ->  " << an << '\n'
			<< ".IdTable  ->  " << IdTable << '\n'
			<< ".LexTable  ->  " << LexTable << '\n'
			<< ".lexical  ->  " << Lexical << '\n';
		delete in;
		delete out;
		delete an;
		delete IdTable;
		delete LexTable;
		delete Lexical;
		delete logg;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- Исходные данные ----\n"
			<< "Количество символов: " << in.size
			<< "\nПроигнорировано: " << in.ignor
			<< "\nКоличество строк: " << in.lines << "\n\n";
	}
	void WriteLT(LT::LexTable lt, LOG log, In::IN in)
	{
		*log.stream << "Результат работы лексического анализатора по строкам ис-ходного кода\n";
		bool next = false;
		int i = 0;
		for (int index = 1; index < in.lines; index++)
		{
			if (index <= 9) *log.stream << "\n00" << index << " | ";
			if (index >= 10 && index <= 99) *log.stream << "\n0" << index << " | ";
			if (index > 100) *log.stream << '\n' << index << " | ";
			while (index == lt.table[i].sn)
			{
				if (lt.table[i].lexema=='v' || lt.table[i].lexema == 'c')
					*log.stream << lt.table[i].value;
				else *log.stream << lt.table[i].lexema;
				i++;
			}
		}
	}
	void WriteLT_ALL(LT::LexTable lt, LOG log)
	{
		*log.stream << "Протокол по работе ТЛ - Полная ТЛ ->\n\n"
			<< "---+----------------------+-----------------+--------------------------+---------+\n"
			<< " № | номер в табл идентиф |    лексема      |  номер в исходном коде   | значение \n"
			<< "---+----------------------+-----------------+--------------------------+---------+\n";
		for (int i = 0; i < lt.size; i++)
		{
			*log.stream << setw(3) << i << '|' << setw(22) << lt.table[i].idxTI << '|' << setw(17) << lt.table[i].lexema
				<< '|' << setw(26) << lt.table[i].sn << '|' << setw(8) << lt.table[i].value << endl;
		}
		*log.stream << "---+----------------------+-----------------+--------------------------+---------+\n";
	}
	void WriteIT_ALL(IT::IdTable it, LOG log)
	{
		char type[7]; char id_type[10]; char buf[3];
		*log.stream << "Протокол по работе ТИ - Полная ТИ ->\n\n"
			<< "---+----------------------+-----------------+---------------+--------------------+--------------\n"
			<< " № | инд первой стр в ТЛ  |  идентификатор  |  тип данных   | тип идентификатора |значение\n"
			<< "---+----------------------+-----------------+---------------+--------------------+\n";
		for (int i = 0; i < it.size; i++)
		{
			*log.stream << setw(3) << i << "|" << setw(22) << it.table[i].idxfirstLE << '|' << setw(17) << it.table[i].id
				<< '|';
			switch (it.table[i].iddatatype)
			{
			case IT::INT: *log.stream << setw(15) << "int"; break;
			case IT::STR: *log.stream << setw(15) << "string";; break;
			case IT::BOOL: *log.stream << setw(15) << "bool";;  break;
			}
			switch (it.table[i].idtype)
			{
			case IT::V: *log.stream << setw(21) << "variable" << '|'; break;
			case IT::F: *log.stream << setw(21) << "function" << '|'; break;
			case IT::P: *log.stream << setw(21) << "param" << '|';  break;
			case IT::L: *log.stream << setw(21) << "lex" << '|';  break;
			}
			switch (it.table[i].iddatatype)
			{
			case IT::INT:	{
				switch (it.table[i].value.chislo.representation)
				{
				case IT::BIN: *log.stream << "_BINARY ";  break;
				case IT::DEC: *log.stream << "_DECIMAL "; break;
				case IT::HEX: *log.stream << "_HEXADEMICAL "; break;
				}
				*log.stream << it.table[i].value.chislo.vint << '\n';
			}break;
			case IT::STR:	{
				*log.stream << '[' << it.table[i].value.vstr[0].len << ']';
				for (int j = 1; j <= it.table[i].value.vstr[0].len; j++)
				{
					*log.stream << it.table[i].value.vstr[j].str;
				}
				*log.stream << '\n';
			}break;
			case IT::BOOL:	{
				if(it.table[i].value.bool_value == 1)
				*log.stream << "(True) "<< it.table[i].value.bool_value;
				else if(it.table[i].value.bool_value == 0)
				*log.stream << "(False) "<< it.table[i].value.bool_value;
				*log.stream << '\n';
			}break;
			}
		}
		*log.stream << "---+----------------------+-----------------+---------------+--------------------+-------------------\n";
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "\nОшибка " << error.id << ": " << error.message;
		if (!error.inext.col == -1)
			*log.stream << ", строка: " << error.inext.line << ", позиция: " << error.inext.col;
		*log.stream << ", строка: " << error.inext.line;
	}

	void End_of_MDI(LOG log, clock_t t0)
	{
		clock_t t1 = clock();
		*log.stream << "Программа завершена за " << (double)(t1 - t0) / CLOCKS_PER_SEC << " секунд." << endl;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}
