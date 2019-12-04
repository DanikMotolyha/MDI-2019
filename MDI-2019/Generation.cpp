#include "Generation.h"

#include "IT.h"
#include "LT.h"
#include "Log.h"
void Gen::Asm(LT::LexTable lt, Log::LOG log, IT::IdTable it)
{
	stack<string> stk;
	// шапка asm файла 
	*(log.stream) << ".586\n"
		<< ".model flat, stdcall\n"
		<< "includelib kernel32.lib\n"
		<< "includelib ASM_LIB.lib\n"
		<< "includelib libucrt.lib\n"
		<< "includelib msvcrt.lib \n\n"

		// описание функций 
		<< "ExitProcess PROTO :DWORD\n"
		<< "outc PROTO :DWORD\n"
		<< "outi PROTO :DWORD\n"
		<< "outid PROTO :DWORD\n"
		<< "outcd PROTO :DWORD\n"
		<< "Pow PROTO :DWORD, :DWORD\n"
		<< "Sqrt PROTO :DWORD\n";

	*(log.stream) << "\n.stack 4096\n";


	*(log.stream) << ".const\n";
	int j = 1;
	for (int i = 0; i < lt.size; i++)
	{
		if (lt.table[i].lexema == LEX_LITERAL)
		{
			if (atoi(&it.table[lt.table[i].idxTI].id[3]) == j)
			{
				j++;
				switch (it.table[lt.table[i].idxTI].iddatatype)
				{

				/*INT*/case 1: {
					*log.stream << it.table[lt.table[i].idxTI].id << "\tDWORD\t" 
						<< it.table[lt.table[i].idxTI].value.chislo.vint << endl;} break;

				/*STR*/case 2: {
					*log.stream << it.table[lt.table[i].idxTI].id << "\tByte\t\'";
					for (int j = 1; j <= it.table[lt.table[i].idxTI].value.vstr[0].len; j++)
					{
						*log.stream << it.table[lt.table[i].idxTI].value.vstr[j].str;
					}
					*log.stream << "\',0\n"; } break;

				/*BOOL*/case 3: {
					*log.stream << it.table[lt.table[i].idxTI].id << "\tDWORD\t"
						<< it.table[lt.table[i].idxTI].value.bool_value << endl; } break;
				}
			}
		}
	}

	*(log.stream) << ".data\n";
	string buf; char Buf[12];
	for (int i = 0; i < lt.size; i++)
	{
		if (lt.table[i].lexema == LEX_NEW && lt.table[i+2].lexema == LEX_ID)
		{
			*log.stream << it.table[lt.table[i + 2].idxTI].id << "  DWORD\t" << "?\n";
		}
	}

	*(log.stream) << "\n\n.code\n";

	bool Main_Flag = false;

	for (int i = 0; i < lt.size; i++)
	{
		switch (lt.table[i].lexema)
		{
		case LEX_EQUALLY:{
			for (int j = i + 1; lt.table[j].lexema != LEX_SEMICOLON; j++)
			{
				if (lt.table[j].lexema == LEX_ID || lt.table[j].lexema == LEX_LITERAL)
				{
					switch ((it.table[lt.table[j].idxTI].iddatatype))
					{
					/*INT*/case 1: {
						*(log.stream) << "\tpush " << it.table[lt.table[j].idxTI].id << endl;
						stk.push(it.table[lt.table[j].idxTI].id); } break;

					/*STR*/case 2: {
						*(log.stream) << "\tpush offset " << it.table[lt.table[j].idxTI].id << endl;
						stk.push(it.table[lt.table[j].idxTI].id); } break;

					/*BOOL*/case 3: {
						*(log.stream) << "\tpush " << it.table[lt.table[j].idxTI].id << endl;
						stk.push(it.table[lt.table[j].idxTI].id); } break;
					}
				}
				switch (lt.table[j].lexema) {
				case LEX_NEWPROC: {
					for (int j = 0; j < stk.size(); j++)
					{
						*log.stream << "\tpop edx\n";
					}
					int size = stk.size();
					for (int j = 0; j < size; j++)
					{
						*log.stream << "push " << stk.top().c_str() << endl;
						stk.pop();
					}
					*(log.stream) << "\t\tcall " <<
						it.table[lt.table[j].idxTI].id << "\npush eax\n\n";
				}break;
				case LEX_OPERATION: {
					switch (lt.table[j].value[0])
					{
					case OPERATION_PLUS: {
						*(log.stream) << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n"; } break;
					case OPERATION_MINUS: {
						*(log.stream) << "\tpop ebx\n\tpop eax\n\tsub eax, ebx\n\tpush eax\n"; } break;
					case OPERATION_DEL: {
						*(log.stream) << "\tpop ebx\n\tpop eax\n\tmov edx,0\n\tdiv ebx\n\tpush eax\n"; } break;
					case OPERATION_MULT: {
						*(log.stream) << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n"; } break;
					/*знак больше (сдвиговая операция >>)*/case OPERATION_BIGGER: {
						*log.stream << "\n\tpop ecx\n\tpop eax\n\tshr  AL, CL\n\tpush eax\n"; } break;
					/*знак меньше (сдвиговая операция <<)*/case OPERATION_SMALER: {
						*log.stream << "\n\tpop ecx\n\tpop eax\n\tshl  AL, CL\n\tpush eax\n"; } break;
					}
					while(!stk.empty()) { stk.pop(); }
				}break;
				}
			}
			*(log.stream) << "\tpop " << it.table[lt.table[i - 1].idxTI].id << "\n";
			int size = stk.size();
			for (int i = 0; i < size; i++) { *(log.stream) << "\tpop edx\n"; stk.pop(); }
		}break;
		case LEX_OUT:	{
			if (lt.table[i + 1].lexema == LEX_ID || lt.table[i + 1].lexema == LEX_LITERAL)
			{
				*log.stream << "\npush " << it.table[lt.table[i + 1].idxTI].id;
				switch (it.table[lt.table[i + 1].idxTI].iddatatype)
				{
				case 1: *log.stream <<  "\n\t\tcall outi\n"; break;
				case 2: *log.stream <<  "\n\t\tcall outc\n"; break;
				case 3: *log.stream <<  "\n\t\tcall outi\n"; break;
				}
			}
			else throw /*!!!!!!!!!!!!!!!!!! ошибка неправильного параметра вывода*/;
		}break;
		case LEX_NEW:	{
			if (lt.table[i + 2].lexema == LEX_FUNCTION)
			{
				strcpy(Buf, it.table[lt.table[i + 3].idxTI].id);
				*log.stream << it.table[lt.table[i + 3].idxTI].id << "  PROC\t";
				for (int j = i + 2; lt.table[j].lexema != LEX_RIGHTHESIS; j++)
				{
					switch (lt.table[j].lexema)
					{
					case LEX_INT: { *log.stream << it.table[lt.table[j + 1].idxTI].id << " :DWORD";	} break;
					case LEX_COMMA: *log.stream << LEX_COMMA; break;
					}
				}
				*log.stream << '\n';// i = i + (i - j);
			}
		}break;
		case LEX_MAIN:	{
			*log.stream << "main PROC\n"; Main_Flag = true;
		}break;
		case LEX_RETURN:{

			if (lt.table[i + 2].lexema == ';')	{	*log.stream << "\tpush "
				<< it.table[lt.table[i+1].idxTI].id << "\nret\n";	}
			else 
			{
				for (int j = i + 1; lt.table[j].lexema != LEX_SEMICOLON; j++)
				{
					if (lt.table[j].lexema == LEX_ID || lt.table[j].lexema == LEX_LITERAL)
					{
						switch ((it.table[lt.table[j].idxTI].iddatatype))
						{
						/*INT*/case 1: {
							*(log.stream) << "\tpush " << it.table[lt.table[j].idxTI].id << endl;
							stk.push(it.table[lt.table[j].idxTI].id); } break;

						/*STR*/case 2: {
							*(log.stream) << "\tpush offset " << it.table[lt.table[j].idxTI].id << endl;
							stk.push(it.table[lt.table[j].idxTI].id); } break;

						/*BOOL*/case 3: {
							*(log.stream) << "\tpush " << it.table[lt.table[j].idxTI].id << endl;
							stk.push(it.table[lt.table[j].idxTI].id); } break;
						}
					}
					switch (lt.table[j].lexema) {
					case LEX_NEWPROC: {
						for (int j = 1; j < stk.size(); j++)
						{
							*log.stream << "\tpop edx\n";
						}
						int size = stk.size();
						for (int j = 0; j < size; j++)
						{
							*log.stream << "push " << stk.top().c_str() << endl;
							stk.pop();
						}
						*(log.stream) << "\t\tcall " <<
							it.table[lt.table[j].idxTI].id << "\npush eax\n";
					}break;
					case LEX_OPERATION: {
						switch (lt.table[j].value[0])
						{
						case OPERATION_PLUS: {
							*(log.stream) << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n"; } break;
						case OPERATION_MINUS: {
							*(log.stream) << "\tpop ebx\n\tpop eax\n\tsub eax, ebx\n\tpush eax\n"; } break;
						case OPERATION_DEL: {
							*(log.stream) << "\tpop ebx\n\tpop eax\n\tmov edx,0\n\tdiv ebx\n\tpush eax\n"; } break;
						case OPERATION_MULT: {
							*(log.stream) << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n"; } break;
						/*знак больше (сдвиговая операция >>)*/case OPERATION_BIGGER: {
							*log.stream << "\n\tpop ecx\n\tpop eax\n\tshr  AL, CL\n\tpush eax\n"; } break;
						/*знак меньше (сдвиговая операция <<)*/case OPERATION_SMALER: {
							*log.stream << "\n\tpop ecx\n\tpop eax\n\tshl  AL, CL\n\tpush eax\n"; } break;
						}
					}break;
					}
				}
				*log.stream << "\nret\n";
			}
			*log.stream << Buf << " endp\n\n\n";
		}break;
		case LEX_TURN: {	} break;
		case LEX_IF: {	} break;
		case LEX_ELSE: {	} break;
		}
		
		



	}

	



	if (!Main_Flag) throw;/*ОШИБКА отсутствует MAIN*/

	*log.stream << "\npush 0\n"
					<< "\ncall ExitProcess\n"
					<< "main ENDP\n"
					<< "end main";
}
