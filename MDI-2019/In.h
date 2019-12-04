#pragma once
#include <stack>
#include <string>
#include <iostream>
using namespace std;
#define IN_MAX_LEN_TEXT 1024*1024
//#define IN_CODE_ENDL '\n'

  /*   0   //  1  //  2  //  3  //  4  //  5  //  6  //  7  //  8  //  9  //  A  //  B  //  C  //  D  //  E  //  F  */
#define IN_CODE_TABLE {\
/*0*/IN::I, IN::I, IN::I, IN::P, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I,\
/*1*/IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I,\
/*2*/IN::P, IN::S, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::T, IN::S,\
/*3*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::T,\
/*4*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*5*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*6*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*7*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::T, IN::S, IN::T, IN::I,\
/*8*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*9*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::I, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*A*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*B*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*C*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*D*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*E*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*F*/IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
}
namespace In
{
	struct IN
	{
		enum { T = 1, S = 2, I = 3, P = 4 };
		int size;
		int lines;
		int ignor;

		stack<string>	stack;
		int code[256] = IN_CODE_TABLE;
	};
	IN getin(wchar_t infile[]);


	// для удаления
	void  Delete(IN&in);
}
