#pragma once

#include <iomanip>
#define MFST_TRACE_START *log.stream << std::setw(4) << std::left<<"Шаг" <<":" \
								   << std::setw(20) << std::left<<" Правило" \
								   << std::setw(30) << std::left<<" Входная лента" \
								   << std::setw(20) << std::left<<" Стек" \
								   << std::endl; 
int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];	// печать
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

#define MFST_TRACE1		*log.stream	<< std::setw(4)<<std::left<< ++FST_TRACE_n << ": " \
									<< std::setw(20)<<std::left<< rule.getCRule(rbuf,nrulechain)  \
									<< std::setw(30)<<std::left<< getCLenta(lbuf, lenta_position) << ": " \
									<< std::setw(20)<<std::left<< getCSt(sbuf) \
									<< std::endl; 

#define MFST_TRACE2		*log.stream	<< std::setw(4)<<std::left<< FST_TRACE_n << ": " \
									<< std::setw(20)<<std::left<< " "  \
									<< std::setw(30)<<std::left<< getCLenta(lbuf, lenta_position) << ": " \
									<< std::setw(20)<<std::left<< getCSt(sbuf) \
									<< std::endl;  

#define MFST_TRACE3		*log.stream	<< std::setw(4)<<std::left<< ++FST_TRACE_n << ": " \
									<< std::setw(20)<<std::left<< " "  \
									<< std::setw(30)<<std::left<< getCLenta(lbuf, lenta_position) << ": " \
									<< std::setw(20)<<std::left<< getCSt(sbuf) \
									<< std::endl;  

#define MFST_TRACE4(c)		*log.stream	<< std::setw(4)<<std::left<< ++FST_TRACE_n << ": " \
									<< std::setw(20)<<std::left<< c << std::endl;

#define MFST_TRACE5(c)		*log.stream << std::setw(4)<<std::left<< FST_TRACE_n << ": " \
									<< std::setw(20)<<std::left<< c << std::endl;

#define MFST_TRACE6(c,k)	*log.stream	<< std::setw(4)<<std::left<< FST_TRACE_n << ": " \
									<< std::setw(20)<<std::left<< c << k << std::endl;

#define MFST_TRACE7			*log.stream	<< std::setw(4)<<std::left<< state.lenta_position << ": " \
									<< std::setw(20)<<std::left<< rule.getCRule(rbuf,state.nrulechain) << std::endl;






#include <stack>
#include "Error.h"
#include "LT.h"
#include "Log.h"
#include "GRB.h"
#define MFST_DIAGN_MAXSIZE	2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;		// стек автомата
namespace MFST
{
	struct MfstState				// состояние автомата (для сохранения)
	{
		short lenta_position;		// позиция на ленте
		short nrule;				// номер текущего правила
		short nrulechain;			// номер текущей цепочки, текущего правила
		MFSTSTSTACK st;				// стек автомата
		MfstState();
		MfstState(
			short pposition,			// позиция на ленте
			MFSTSTSTACK pst,			// стек автомата
			short pnrulechain			// номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition,			// позиция на ленте
			MFSTSTSTACK pst,			// стек автомата
			short pnrule,				// номер текущего правила
			short pnrulechain			// номер текущей цепочки, текущего правила
		);
	};
	struct Mfst					// магазинный автомат
	{
		enum RC_STEP {							// код возврата функции step
			NS_OK,					// найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,				// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULLECHAIN,		// не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,				// неизвестный нетерминальный символ грамматики
			TS_OK,					// тек. символ ленты == вершине стека, продвинулась лента, рор стека
			TS_NOK,					// тек. символ ленты != вершине стека, восстановленно состояние
			LENTA_END,				// текущ позиция ленты >= lenta_size
			SUPRISE					// неожиданный код возврата (ошибка в step)
		};
		struct MfstDiagnosis				// диагностика
		{
			short lenta_position;				// позиция на ленте
			RC_STEP rc_step;					// код завершения шага
			short nrule;						// номер правила
			short nrule_chain;					// номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(					// диагностика
				short plenta_position,			// позиция на ленте
				RC_STEP prc_step,				// код завершения шага
				short pnrule,					// номер правила
				short pnrule_chain				// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];				// последние самые глубокие сообщения

		GRBALPHABET* lenta;						// перекодированная (TS/NS) лента (из LEX)
		short lenta_position;					// текущая позиция на ленте
		short nrule;							// номер текущего правила
		short nrulechain;						// номер текущей цепочки, текущего правила
		short lenta_size;						// размер ленты
		GRB::Greibach grebach;					// грмматика грейбах
		// было LEX::LEX lex;	
		LT::LexTable lextable;								// результат работы лексического анализатора
		MFSTSTSTACK st;							// стек автомата
		// было std::stack<MfstState> storestate;	
		std::stack<MfstState>	storestate;				// стек для сохранения состояний
		Mfst();
		Mfst(
			//было LEX::LEX plex
			LT::LexTable plex,			// результат лексического анализатора
			GRB::Greibach pgrebach  // грамматика Грейбах
		);
		char* getCSt(char* buf);		// получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);		// лента : n символов с pos
		char* getDiagnosis(short n, char* buf);						// получить n-ую строку диагностики или 0x00
		bool savestate(Log::LOG log);											// сохранить состояние автомата
		bool reststate(Log::LOG log);											// ввостановить состояние автомата
		bool push_chain(			// поместить цепочку правила в стек
			GRB::Rule::Chain chain	// цепочка правила
		);
		RC_STEP step(Log::LOG log);				// выполнить шаг автомата
		bool start(Log::LOG log);				// запустить автомат
		bool savediagnosis(
			RC_STEP pprc_step		// код завершения шага	
		);
		void printrules(Log::LOG log);				// вывести последовательность правил

		struct Deducation			// вывод
		{
			short size;				// количество шагов в выводе 
			short* nrules;			// номера правил грамматики
			short* nrulechains;		// номера цепочек правил грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation();			// сохранить дерево вывода
	};
	MfstState::MfstState()
	{
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
	};
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short  pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	};
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrule = pnrule;
		nrulechain = pnrulechain;
	};
	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SUPRISE;
		nrule = -1;
		nrule_chain = -1;
	};
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	};
	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; };
	// было  Mfst::Mfst(LEX::LEX plex, GRB::Greibach pgrebach)
	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach)
	{
		grebach = pgrebach;
		lextable = plex;
		// было lenta = new short[lenta_size = lex.lextable.size];
		//for (int k = 0; k < lenta_size; k++) lenta[k] = TS(lex.lextable.table[k].lexema);
		lenta = new short[lenta_size = lextable.size];
		for (int k = 0; k < lenta_size; k++) lenta[k] = TS(lextable.table[k].lexema);
		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
	}
	Mfst::RC_STEP Mfst::step(Log::LOG log)
	{
		RC_STEP rc = SUPRISE;
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top()))					// если терминал то false 
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)		// присваивается правило по st.top
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						MFST_TRACE1
							savestate(log); st.pop();	// сохраняет состояние автомата + удаляет верхний элемент в стеке
						push_chain(chain); rc = NS_OK;	// закидывает цепочку в стек + конец хода  - NS_OK найдено правило и цепочка, цепочка записана в стек
						MFST_TRACE2
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE")
							savediagnosis(NS_NORULLECHAIN); rc = reststate(log) ? NS_NORULLECHAIN : NS_NORULE;
					};
				}
				else rc = NS_ERROR;
			}
			else if ((st.top() == lenta[lenta_position]))
			{
				lenta_position++;	st.pop(); nrulechain = -1; rc = TS_OK;
				MFST_TRACE3
			}
			else { MFST_TRACE4("TS_NOK/NS_NORULECHAIN") rc = reststate(log) ? TS_NOK : NS_NORULLECHAIN; };
		}
		else { rc = LENTA_END; MFST_TRACE4("LENTA_END") };
		return rc;
	};
	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		for (int k = chain.size - 1; k >= 0; k--) st.push(chain.nt[k]);
		return true;
	}
	bool Mfst::savestate(Log::LOG log)
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain));
		MFST_TRACE6("SAVESTATE:", storestate.size());
		return true;
	}
	bool Mfst::reststate(Log::LOG log)
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			MFST_TRACE5("RESSTATE");
			MFST_TRACE2
		};
		return rc;
	};
	bool Mfst::savediagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) diagnosis[j].lenta_position = -1;
		};
		return rc;
	}
	bool Mfst::start(Log::LOG log)
	{
		bool rc = false;
		RC_STEP rc_step = SUPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(log);
		while (rc_step == NS_OK || rc_step == NS_NORULLECHAIN || rc_step == TS_OK || rc_step == TS_NOK) rc_step = step(log);

		switch (rc_step)
		{
		case LENTA_END: MFST_TRACE4("------->LENTA_END")
			*log.stream << "---------------------------------------------------------------  ----" << std::endl;
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
			*log.stream << std::setw(4) << std::left << 0 << ": всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок" << std::endl;
			rc = true;
			break;
		case NS_NORULE: MFST_TRACE4("------->NS_NORULE");
			*log.stream << "---------------------------------------------------------------  ----" << std::endl;
			*log.stream << getDiagnosis(0, buf) << std::endl;
			*log.stream << getDiagnosis(1, buf) << std::endl;
			*log.stream << getDiagnosis(2, buf) << std::endl;
			break;
		case NS_NORULLECHAIN:	MFST_TRACE4("------->NS_NORULENORULECHAIN") break;
		case NS_ERROR:			MFST_TRACE4("------->NS_ERROR") break;
		case SUPRISE:			MFST_TRACE4("------->SUPRISE") break;
		};
		return rc;
	}
	char* Mfst::getCSt(char* buf)											// главная функция она определяет T или Н
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = st._Get_container()[k];
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		};
		buf[st.size()] = 0x00;
		return buf;
	};
	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++) buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}
	char* Mfst::getDiagnosis(short n, char* buf)
	{
		char* rc = (char*)"";
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::ERROR err = Error::geterror(errid);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lextable.table[lpos].sn, err.message);
			rc = buf;
		};
		return rc;
	};
	void Mfst::printrules(Log::LOG log)
	{
		MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			rule = grebach.getRule(state.nrule);
			MFST_TRACE7
		};
	};
	bool Mfst::savededucation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		};
		return true;
	};
	void Write_to_An(LT::LexTable lt, Log::LOG log)
	{
		MFST_TRACE_START				// отладка
			MFST::Mfst mfst(lt, GRB::getGreibach());
		mfst.start(log);

		mfst.savededucation();

		mfst.printrules(log);
	}
}
