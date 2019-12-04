#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "IT.h"
#include "LT.h"
#include <ctime>
namespace Log
{
	class PROTOCOL
	{
	private:
		wchar_t logfile[PARM_MAX_SIZE];
		std::wofstream* stream;
		PROTOCOL()
		{
			wcsncpy_s(logfile, L"", wcslen(logfile));
			stream = NULL;
		}

	};
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::wofstream* stream;
	};
	void WriteLT_ALL(LT::LexTable lt, LOG log);
	void WriteIT_ALL(IT::IdTable it, LOG log);
	void WriteLT(LT::LexTable lt, LOG log, In::IN in);
	static LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	//void WriteLine(LOG log, const char* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);
	//void WritetoLogFST(Log::LOG log, In::IN in);

	void End_of_MDI(LOG log, clock_t t0);

	void Close(LOG log);
}