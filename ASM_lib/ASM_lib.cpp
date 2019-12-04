#include "stdafx.h"
#include <iostream>
#include <Windows.h>
extern"C"
{
	int __stdcall outi(int a)
	{
		std::cout << a << std::endl;
		return 0;
	}

	int __stdcall outc(char* value)
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		setlocale(LC_CTYPE, "Russian");
		std::cout << value << std::endl;
		return 0;
	}

	int __stdcall Pow(int k, int size)
	{
		int output = k;
		for (int i = 1; i < size; i++) k *= output;
		//if (-1 > k || k > 255) return -1; else
		return k;
	}

	int __stdcall Sqrt(int value)
	{
		for (int i = 1; i < 16; i++) { if (i*i == value) { return i; } else i++; }
		// return -1;
	}
}