#include "Parm.h"
#include "Error.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

using namespace std;
namespace Parm
{

	PARM getparm(int argc, wchar_t* agrv[])
	{
		//cout << argc << endl; char buf[300];
		//for (int i = 0; i < argc; i++)
		//{
		//	wcstombs(buf,agrv[i],wcslen(agrv[i]));
		//	buf[wcslen(agrv[i])] = '\0'; cout << buf << endl;
		//}/*
		bool in = 0, out = 0, log = 0;
		wchar_t ini[PARM_MAX_SIZE] = L"";
		PARM e;
		if (argc == 1) throw ERROR_THROW(100);
		for (int i = 1; i < argc; ++i)
		{
			*agrv = agrv[i];
			if (wcslen(*agrv) > ERROR_MAXSIZE_MESSAGE) throw ERROR_THROW(104)
				int size = wcslen(*agrv);

			if (wcsstr(*agrv, PARM_IN))
			{
				in = true;
				wchar_t *a = *agrv + (wchar_t)4;
				wcsncpy_s(e.in, a, wcslen(a));
				int i = wcslen(a);
				while (a[i] != '\\') { a[i] = '\0'; i--; }
				wchar_t mass[300];
				wcsncpy_s(mass, a, wcslen(a));
				wcsncat_s(mass, L"Protocol\\", 9);

				fs::create_directories(mass);

				wcsncpy_s(e.log, mass, wcslen(mass)); wcsncat_s(e.log, L"Protocol.log", 12);
				wcsncpy_s(e.an, mass, wcslen(mass)); wcsncat_s(e.an, L"Protocol.an", 11);
				wcsncpy_s(e.out, L"..\\ASM\\ASM.asm", 14);
				wcsncpy_s(e.LexTable, mass, wcslen( mass)); wcsncat_s(e.LexTable, L"Protocol.LexT", 13);
				wcsncpy_s(e.IdTable,  mass, wcslen( mass)); wcsncat_s(e.IdTable, L"Protocol.IdT", 12);
				wcsncpy_s(e.Lexical,  mass, wcslen( mass)); wcsncat_s(e.Lexical, L"Protocol.lexical", 16);
			}

		}
		if (!in) throw ERROR_THROW(100);
		return e;
	}
}
