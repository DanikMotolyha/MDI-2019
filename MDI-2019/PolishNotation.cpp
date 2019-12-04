#include "IT.h"
#include "LT.h"
#include "PolishNotation.h"
namespace PN
{
	int priority(char a)
	{
		if (a == '(' || a == ')')	    return 1;
		if (a == '>' || a == '<')		return 2;
		if (a == '-' || a == '+')		return 3;
		if (a == '*' || a == '/')		return 4;
	}
	void PolishNotation(IT::IdTable &it, LT::LexTable &lt)
	{
		for (int i = 0; i < lt.size; i++)
		{
			if (lt.table[i].lexema == LEX_EQUALLY || lt.table[i].lexema == LEX_RETURN)
			{
				Conv_V(&lt, &it, ++i);
			}
		}
	}
	void Conv_V(LT::LexTable* lextable, IT::IdTable* idtable, int lextable_pos)
	{
		std::stack<LT::Entry> st;
		LT::Entry outstr[200];
		int len = 0, lenout = 0, semicolonid;					
		char t, oper = ' '; int hesis = 0;
		int indoffunk;	bool flag_hesis = false;
		for (int i = lextable_pos; lextable->table[i].lexema != LEX_SEMICOLON; i++)
		{
			len = i;
			semicolonid = i + 1;
		}
		len++;
		for (int i = lextable_pos; i < len; i++)
		{
			t = lextable->table[i].lexema;
			if (lextable->table[i].lexema == 'v')
				oper = lextable->table[i].value[0];
			if (t == LEX_RIGHTHESIS)					
			{
				while (st.top().lexema != LEX_LEFTTHESIS)
				{
					outstr[lenout++] = st.top();			
					hesis++;
					st.pop();							
				}
				st.pop();									
			}
			if (t == LEX_ID || t == LEX_LITERAL)
			{
				if (lextable->table[i + 1].lexema == LEX_LEFTTHESIS)
				{
					indoffunk = i;
					i += 2;
					while (lextable->table[i].lexema != LEX_RIGHTHESIS)
					{								
						if (lextable->table[i].lexema != LEX_COMMA)
						{
							outstr[lenout++] = lextable->table[i++];
						}
						else
						{
							hesis++;
							i++;
						}
					}
					outstr[lenout++] = lextable->table[indoffunk];
					outstr[lenout - 1].lexema = LEX_NEWPROC;
					hesis += 2;
				}
				else
					outstr[lenout++] = lextable->table[i];
			}
			if (t == LEX_LEFTTHESIS)
			{
				flag_hesis = true;
				st.push(lextable->table[i]);							
				hesis++;
			}
			if (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '<' || oper == '>')
			{
				if (!st.size())
					st.push(lextable->table[i]);
				else {
					int pr; char id;
					if (st.top().lexema == '(' || st.top().lexema == ')')
						pr = 1;
					else {
						id = st.top().value[0];
						pr = priority(id);
					}
					if (priority(oper) > pr)								
						st.push(lextable->table[i]);													
					else
					{
						while (st.size())
						{
							if (st.top().lexema == 'v' && priority(oper) <= priority(st.top().value[0]))
							{
								outstr[lenout] = st.top();
								st.pop();
								lenout++;
							}
							else break;
							  //priority(oper) <= priority(st.top().lexema))
							}
						st.push(lextable->table[i]);
					}
				}
			}
			oper = NULL;	
		}
		while (st.size())
		{
			outstr[lenout++] = st.top();										
			st.pop();
		}
		for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++, k++)
		{
			lextable->table[i] = outstr[k];											
		}
		lextable->table[lextable_pos + lenout] = lextable->table[semicolonid];		
		for (int i = 0; i < hesis; i++)
		{
			for (int j = lextable_pos + lenout + 1; j < lextable->size; j++)				
			{
				lextable->table[j] = lextable->table[j + 1];
			}
			lextable->size--;
		}
		if (flag_hesis)
		{
			for (int i = 0; i < lextable->size; i++)
			{
				if (lextable->table[i].idxTI != -1)
				{
					idtable->table[lextable->table[i].idxTI].idxfirstLE = i;
				}
			}
		}
	}
	
}