#pragma once

#include <iomanip>
#define MFST_TRACE_START *log.stream << std::setw(4) << std::left<<"���" <<":" \
								   << std::setw(20) << std::left<<" �������" \
								   << std::setw(30) << std::left<<" ������� �����" \
								   << std::setw(20) << std::left<<" ����" \
								   << std::endl; 
int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];	// ������
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
typedef std::stack<short> MFSTSTSTACK;		// ���� ��������
namespace MFST
{
	struct MfstState				// ��������� �������� (��� ����������)
	{
		short lenta_position;		// ������� �� �����
		short nrule;				// ����� �������� �������
		short nrulechain;			// ����� ������� �������, �������� �������
		MFSTSTSTACK st;				// ���� ��������
		MfstState();
		MfstState(
			short pposition,			// ������� �� �����
			MFSTSTSTACK pst,			// ���� ��������
			short pnrulechain			// ����� ������� �������, �������� �������
		);
		MfstState(
			short pposition,			// ������� �� �����
			MFSTSTSTACK pst,			// ���� ��������
			short pnrule,				// ����� �������� �������
			short pnrulechain			// ����� ������� �������, �������� �������
		);
	};
	struct Mfst					// ���������� �������
	{
		enum RC_STEP {							// ��� �������� ������� step
			NS_OK,					// ������� ������� � �������, ������� �������� � ����
			NS_NORULE,				// �� ������� ������� ���������� (������ � ����������)
			NS_NORULLECHAIN,		// �� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,				// ����������� �������������� ������ ����������
			TS_OK,					// ���. ������ ����� == ������� �����, ������������ �����, ��� �����
			TS_NOK,					// ���. ������ ����� != ������� �����, �������������� ���������
			LENTA_END,				// ����� ������� ����� >= lenta_size
			SUPRISE					// ����������� ��� �������� (������ � step)
		};
		struct MfstDiagnosis				// �����������
		{
			short lenta_position;				// ������� �� �����
			RC_STEP rc_step;					// ��� ���������� ����
			short nrule;						// ����� �������
			short nrule_chain;					// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(					// �����������
				short plenta_position,			// ������� �� �����
				RC_STEP prc_step,				// ��� ���������� ����
				short pnrule,					// ����� �������
				short pnrule_chain				// ����� ������� �������
			);
		} diagnosis[MFST_DIAGN_NUMBER];				// ��������� ����� �������� ���������

		GRBALPHABET* lenta;						// ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;					// ������� ������� �� �����
		short nrule;							// ����� �������� �������
		short nrulechain;						// ����� ������� �������, �������� �������
		short lenta_size;						// ������ �����
		GRB::Greibach grebach;					// ��������� �������
		// ���� LEX::LEX lex;	
		LT::LexTable lextable;								// ��������� ������ ������������ �����������
		MFSTSTSTACK st;							// ���� ��������
		// ���� std::stack<MfstState> storestate;	
		std::stack<MfstState>	storestate;				// ���� ��� ���������� ���������
		Mfst();
		Mfst(
			//���� LEX::LEX plex
			LT::LexTable plex,			// ��������� ������������ �����������
			GRB::Greibach pgrebach  // ���������� �������
		);
		char* getCSt(char* buf);		// �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);		// ����� : n �������� � pos
		char* getDiagnosis(short n, char* buf);						// �������� n-�� ������ ����������� ��� 0x00
		bool savestate(Log::LOG log);											// ��������� ��������� ��������
		bool reststate(Log::LOG log);											// ������������ ��������� ��������
		bool push_chain(			// ��������� ������� ������� � ����
			GRB::Rule::Chain chain	// ������� �������
		);
		RC_STEP step(Log::LOG log);				// ��������� ��� ��������
		bool start(Log::LOG log);				// ��������� �������
		bool savediagnosis(
			RC_STEP pprc_step		// ��� ���������� ����	
		);
		void printrules(Log::LOG log);				// ������� ������������������ ������

		struct Deducation			// �����
		{
			short size;				// ���������� ����� � ������ 
			short* nrules;			// ������ ������ ����������
			short* nrulechains;		// ������ ������� ������ ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation();			// ��������� ������ ������
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
	// ����  Mfst::Mfst(LEX::LEX plex, GRB::Greibach pgrebach)
	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach)
	{
		grebach = pgrebach;
		lextable = plex;
		// ���� lenta = new short[lenta_size = lex.lextable.size];
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
			if (ISNS(st.top()))					// ���� �������� �� false 
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)		// ������������� ������� �� st.top
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						MFST_TRACE1
							savestate(log); st.pop();	// ��������� ��������� �������� + ������� ������� ������� � �����
						push_chain(chain); rc = NS_OK;	// ���������� ������� � ���� + ����� ����  - NS_OK ������� ������� � �������, ������� �������� � ����
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
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: ����� ����� %d, �������������� ������ �������� ��� ������", 0, lenta_size);
			*log.stream << std::setw(4) << std::left << 0 << ": ����� ����� " << lenta_size << ", �������������� ������ �������� ��� ������" << std::endl;
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
	char* Mfst::getCSt(char* buf)											// ������� ������� ��� ���������� T ��� �
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
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: ������ %d, %s", err.id, lextable.table[lpos].sn, err.message);
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
		MFST_TRACE_START				// �������
			MFST::Mfst mfst(lt, GRB::getGreibach());
		mfst.start(log);

		mfst.savededucation();

		mfst.printrules(log);
	}
}
