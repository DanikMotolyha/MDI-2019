#include "In.h"
#include "Error.h"
#include "Parm.h"
#include <string>
#include <stack>
#include <fstream>
#include <iostream>
using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		int  index = 0; bool double_sep = 0, flag_text = 1;
		IN inn; inn.size = inn.ignor = 0; inn.lines = 1;
		unsigned char a; stack<string> stack;
		ifstream file(infile);
		string str, buf = ""; char dub = ' ';
		if (!file.is_open()) throw ERROR_THROW(110);
		while (getline(file, str))
		{
			for (int i = 0; i < str.length(); i++)
			{
				a = str[i];
				if (inn.code[a] == IN::I) { inn.ignor++; continue; }
				if (a == '\'')
				{
					if (index % 2 == 0)		flag_text = false;
					else					flag_text = true;
					index++;
				}
				if (flag_text && buf != "" && (inn.code[a] == IN::P || inn.code[a] == IN::S))
				{
					stack.push(buf);	 buf = "";
					if (inn.code[a] == IN::S) 
					{ 
						if (str[i] == '!' || str[i] == '=' || str[i] == '<' || str[i] == '>')
							if (double_sep)
							{
								if (dub == '!' && str[i] == '=' ||
									dub == '=' && str[i] == '=' ||
									(dub == '<' && (str[i] == '=' || str[i] == '<')) ||
									(dub == '>' && (str[i] == '=' || str[i] == '>')))

								{ buf += dub; buf += str[i]; stack.push(buf);  buf = ""; double_sep = 0; }
								else { buf = dub;  stack.push(buf); buf = str[i]; stack.push(buf); buf = ""; double_sep = 0; }
							}
							else {	double_sep = 1; dub = str[i]; }
						else
						{
							buf = str[i]; stack.push(buf); double_sep = 0; buf = "";
						}
					}
				}
				else if (inn.code[a] == IN::S && flag_text)
				{
					if (str[i] == '!' || str[i] == '=' || str[i] == '<' || str[i] == '>')
						if (double_sep)
						{
							if (dub == '!' && str[i] == '=' ||
								dub == '=' && str[i] == '=' ||
								dub == '<' && (str[i] == '=' || str[i] == '<') ||
								dub == '>' && (str[i] == '=' || str[i] == '>'))

							{
								buf += dub; buf += str[i]; stack.push(buf);  buf = ""; double_sep = 0;
							}
							else { buf = dub;  stack.push(buf); buf = str[i]; stack.push(buf); buf = ""; double_sep = 0; }
						}
						else { double_sep = 1; dub = str[i]; }
					else
					{
						if (dub != ' ') { string buff;  buff = dub; stack.push(buff); buff = ""; dub = ' '; }
						buf = str[i]; stack.push(buf); double_sep = 0; buf = "";
					}
				}
				else if (str[i] != ' ' || !flag_text) 
				{ if (double_sep) { buf = dub; stack.push(buf); buf = ""; dub = ' '; double_sep = 0; }buf += str[i]; }
				inn.size++;
			}
			if(buf != "")
			stack.push(buf); buf = "";
			inn.lines++; stack.push("|");
		}
		file.close();
		int size; size = stack.size();
		for (int i = 0; i < size; i++)
		{
			inn.stack.push(stack.top()); stack.pop();
		}/*
		size = inn.stack.size();
		stack = inn.stack;
		for (int i = 0; i < size; i++)
		{
			cout << stack.top() << ' '; stack.pop();
		}*/
		return inn;
	}
}
