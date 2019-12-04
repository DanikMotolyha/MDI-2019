#include "Error.h"
#include "Lex.h"
#include "FST.h"
#include "IT.h"
#include "LT.h"
#include "In.h"
int to_decimal(string a)
{
	int decimal = 0; int pos = a.length()-1;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[pos] == '1') decimal += pow(2, i);
		pos--;
	}
	return decimal;
}
string to_binary(string a)
{
	string binary;
	for (int i = 0; i < a.length(); i++)
	{
		switch (a[i])
		{
		case '1': binary += "0001"; break;
		case '2': binary += "0010"; break;
		case '3': binary += "0011"; break;
		case '4': binary += "0100"; break;
		case '5': binary += "0101"; break;
		case '6': binary += "0110"; break;
		case '7': binary += "0111"; break;
		case '8': binary += "1000"; break;
		case '9': binary += "1001"; break;
		case 'A': binary += "1010"; break;
		case 'B': binary += "1011"; break;
		case 'C': binary += "1100"; break;
		case 'D': binary += "1101"; break;
		case 'E': binary += "1110"; break;
		case 'F': binary += "1111"; break;
		}
	}
	return binary;
}
	void LEX::Create_LEX(In::IN in, IT::IdTable &it, LT::LexTable &lt)
	{
		int size = in.stack.size(); string str; int lines = 1, INDEX = 1;
		FST::FST *a = FST::automat(); int Index_of_main = 0;
		bool lex_recognized = false;
		LT::Entry Lt;
		IT::Entry Id;

		stack<string> scope;		// область видимости в виде стека 



		bool fun = false;
		bool neew = false;
		bool params = false;
		bool type = false;
		bool new_identif = true;
		int end = 0;

		for (int i = 0; i < size; i++)
		{
			str = in.stack.top();
			if (in.stack.top() == "|")	{	lines++; in.stack.pop();	}
			else 
			{
				Lt.idxTI = LT_TI_NULLIDX;
				Lt.sn = lines;
				strcpy_s(Lt.value,LEX_NOT_OPERATION);
				Id.idxfirstLE = lt.size;
				for (int i = 0; i <= FST_SIZE; i++)
				{
					a[i].string = (char*)in.stack.top().c_str(); // . . .
					if (FST::execute(a[i]))
					{
						delete[] a[i].rstates;
						//cout << a[i].string << ' ';
						lex_recognized = true;
						switch (i)
						{
						case 0: { Id.iddatatype = IT::STR; type = true; Lt.lexema = LEX_STRING;	} break;
						case 1: { Id.iddatatype = IT::INT; type = true; Lt.lexema = LEX_INT; } break;
						case 2: { Id.iddatatype = IT::BOOL; type = true; Lt.lexema = LEX_BOOL; }	 break;
						case 3: {	Id.idtype = IT::F; fun = true;	Lt.lexema = LEX_FUNCTION; } break;
						case 4: {	neew = true;							Lt.lexema = LEX_NEW; } break;
						case 5:	Lt.lexema = LEX_RETURN; break;
						case 6: Lt.lexema = LEX_OUT; break;
						case 7: {	if (Index_of_main >= 1) throw /*ошибка main должен быть один*/;
								Index_of_main++; scope.push("main");			Lt.lexema = LEX_MAIN; }break;
						case 8: {	type = fun = neew = params = false; Lt.lexema = LEX_SEMICOLON; }break;
						case 9:	Lt.lexema = LEX_COMMA; break;
						case 10: {		fun = false;						Lt.lexema = LEX_LEFTBRACE; }break;
						case 11: {	if (!end)	scope.pop(); else end--;			Lt.lexema = LEX_BRACELET; } break;
						case 12: {	if(fun)	params = true;			Lt.lexema = LEX_LEFTTHESIS; } break;
						case 13: {	if(fun)	params = false;			Lt.lexema = LEX_RIGHTHESIS; } break;
						case 14: {								Lt.lexema = LEX_EQUALLY; }break;
						case 15: {	Lt.lexema = LEX_OPERATION;
								if(a[i].string[0] == OPERATION_SMALER && a[i].string[1] == OPERATION_SMALER)
									strcpy_s(Lt.value, (char*)OPERATION_LEFT_SHIFT);
								else strcpy_s(Lt.value, (char*)OPERATION_RIGHT_SHIFT);
						} break;
						case 16: {	Lt.lexema = LEX_OPERATION;
							if (a[i].string[0] == OPERATION_PLUS) { Lt.value[0] = OPERATION_PLUS; Lt.value[1] = '\0';}
							if (a[i].string[0] == OPERATION_MINUS) { Lt.value[0] = OPERATION_MINUS; Lt.value[1] = '\0'; }
							if (a[i].string[0] == OPERATION_DEL) { Lt.value[0] = OPERATION_DEL; Lt.value[1] = '\0'; }
							if (a[i].string[0] == OPERATION_MULT) { Lt.value[0] = OPERATION_MULT; Lt.value[1] = '\0'; }
						}break;
						case 17: {	strcpy_s(Lt.value, OPERATION_EQUALY);
									Lt.lexema = LEX_COMPARE; } break;
						case 18: {	strcpy_s(Lt.value, OPERATION_NOT_EQUALY);
									Lt.lexema = LEX_COMPARE; } break;
						case 19: {	strcpy_s(Lt.value, OPERATION_SMALER_AND_EQUALY);
									Lt.lexema = LEX_COMPARE; } break;
						case 20: {	strcpy_s(Lt.value, OPERATION_BIGGER_AND_EQUALY);
									Lt.lexema = LEX_COMPARE; } break;
						case 21: {	if(a[i].string == ">") Lt.value[0] = OPERATION_BIGGER;
									else Lt.value[0] = OPERATION_SMALER;
									Lt.lexema = LEX_COMPARE; } break;
						case 22: { end++; 	Lt.lexema = LEX_IF; } break;
						case 23: { end++; 	Lt.lexema = LEX_ELSE; } break;
						case 24: { end++;	Lt.lexema = LEX_TURN; }	 break;
						case 25: {
							Id.idtype = IT::L; char index[12]; bool Ind = true; char buf[5];
							itoa(INDEX, buf,10);
							Id.iddatatype = IT::INT;
							Id.idtype = IT::L;
							strcpy_s(Id.id, "LEX");
							strcat_s(Id.id, buf);
							a[i].string += (char)2;

							Id.value.chislo.vint = to_decimal(a[i].string);
							Id.value.chislo.representation = IT::BIN;

							for (int i = 0; i < it.size; i++)
							{
								if (it.table[i].value.chislo.vint == Id.value.chislo.vint)
								{
									strcpy_s(Id.id, it.table[i].id);
									Id.value.chislo.vint = it.table[i].value.chislo.vint;
									Id.value.chislo.representation = it.table[i].value.chislo.representation; 
									Ind = false; break;
								}
							}

							if (Ind) INDEX++;

							Lt.idxTI = it.size;
							Lt.lexema = LEX_LITERAL;
							IT::Add(it, Id);
						} break;
						case 26: {
							Id.idtype = IT::L; char index[12]; bool Ind = true; char buf[5];
							itoa(INDEX, buf, 10);
							Id.iddatatype = IT::INT;
							Id.idtype = IT::L;
							strcpy_s(Id.id, "LEX");
							strcat_s(Id.id, buf);

							Id.value.chislo.vint = atoi(a[i].string);
							Id.value.chislo.representation = IT::DEC;

							for (int i = 0; i < it.size; i++)
							{
								if(it.table[i].iddatatype == Id.iddatatype && it.table[i].idtype == Id.idtype)
								if (it.table[i].value.chislo.vint == Id.value.chislo.vint)
								{
									strcpy_s(Id.id, it.table[i].id);
									Id.value.chislo.vint = it.table[i].value.chislo.vint;
									Id.value.chislo.representation = it.table[i].value.chislo.representation;
									Ind = false; break;
								}
							}

							if (Ind) INDEX++;

							Lt.idxTI = it.size;
							Lt.lexema = LEX_LITERAL;
							IT::Add(it, Id);
						} break;
						case 27: {		
							Id.idtype = IT::L; char index[12]; bool Ind = true; char buf[5];
							itoa(INDEX, buf, 10);
							Id.iddatatype = IT::INT;
							Id.idtype = IT::L;
							strcpy_s(Id.id, "LEX");
							strcat_s(Id.id, buf);
							a[i].string += (char)2;

							Id.value.chislo.vint = to_decimal(to_binary(a[i].string));
							Id.value.chislo.representation = IT::HEX;

							for (int i = 0; i < it.size; i++)
							{
								if (it.table[i].iddatatype == Id.iddatatype && it.table[i].idtype == Id.idtype)
								if (it.table[i].value.chislo.vint == Id.value.chislo.vint)
								{
									strcpy_s(Id.id, it.table[i].id);
									Id.value.chislo.vint = it.table[i].value.chislo.vint;
									Id.value.chislo.representation = it.table[i].value.chislo.representation;
									Ind = false; break;
								}
							}

							if (Ind) INDEX++;

							Lt.idxTI = it.size;
							Lt.lexema = LEX_LITERAL;
							IT::Add(it, Id);
						} break;
						case 28: {	
							Id.idtype = IT::L; char index[12]; bool Ind = true; char buf[5];
							itoa(INDEX, buf, 10);
							Id.iddatatype = IT::BOOL;
							Id.idtype = IT::L;
							strcpy_s(Id.id, "LEX");
							strcat_s(Id.id, buf);
							if (a[i].string == "false")
								Id.value.bool_value = 0;
							else Id.value.bool_value = 1;

							for (int i = 0; i < it.size; i++)
							{
								if (it.table[i].iddatatype == Id.iddatatype && it.table[i].idtype == Id.idtype)
								if (it.table[i].value.bool_value == Id.value.bool_value)
								{
									strcpy_s(Id.id, it.table[i].id);
									Id.value.bool_value = it.table[i].value.bool_value;
									Ind = false; break;
								}
							}

							if (Ind) INDEX++;

							Lt.idxTI = it.size;
							Lt.lexema = LEX_LITERAL;
							IT::Add(it, Id);
						} break;
						case 29: { 
							Lt.lexema = LEX_ID;
							Id.iddatatype = IT::INT; Id.value.chislo.vint = 0; Id.value.chislo.representation = IT::DEC;
							Id.idtype = IT::F; Lt.idxTI = it.size;  strcpy_s(Id.id, "pow");IT::Add(it, Id);
						} break;
						case 30: { Lt.lexema = LEX_ID;
							Id.iddatatype = IT::INT; Id.value.chislo.vint = 0; Id.value.chislo.representation = IT::DEC;
							Id.idtype = IT::F; Lt.idxTI = it.size; strcpy_s(Id.id, "sqrt"); IT::Add(it, Id); } break;
						case 31: {
							char index[12]; bool Ind = true; char buf[5];
							itoa(INDEX, buf, 10);
							Id.iddatatype = IT::STR;
							Id.idtype = IT::L;
							strcpy_s(Id.id, "LEX");
							strcat_s(Id.id, buf);

							Id.value.vstr[0].len = strlen(a[i].string)-2;
							for (int j = 1; j < strlen(a[i].string) - 1; j++)
							{
								Id.value.vstr[j].str = a[i].string[j];
							}
							int equaly = 1;
							for (int i = 0; i < it.size; i++)
							{
								if (Id.iddatatype == it.table[i].iddatatype && it.table[i].idtype == Id.idtype)
								{
									for (int j = 1; j <= it.table[i].value.vstr[0].len; j++)
									{
										if (it.table[i].value.vstr[j].str == Id.value.vstr[j].str) equaly++;
										else break;
									}
									if (equaly == it.table[i].value.vstr[0].len)
									{
										strcpy_s(Id.id, it.table[i].id);
										Ind = false; break;
									}
								}equaly = 0;
								
							}

							if (Ind) INDEX++;

							Lt.idxTI = it.size;
							Lt.lexema = LEX_LITERAL;
							IT::Add(it, Id);
						} break;
						case 32: {
							Lt.idxTI = it.size;
							Lt.lexema = LEX_ID;
							if (neew)
							{
								if (!fun)
								{
									if (scope.empty()) throw ERROR_THROW(113) // Ошибка - Глобальные переменные не поддерживаются MDI-2019
									else
									{
										strcpy_s(Id.id, (char*)scope.top().c_str()); // . . .
										strcat_s(Id.id, a[i].string);
										Id.idtype = IT::V;
									}
								}
								else if (params && fun && neew)
								{
									Id.idtype = IT::P;
									strcpy_s(Id.id, (char*)scope.top().c_str()); // . . .
									strcat_s(Id.id, a[i].string);
								}
								else if (fun)
								{
									Id.idtype = IT::F;
									scope.push(a[i].string);
									strcpy_s(Id.id, a[i].string);
								}
								
							}
							else
							{
								strcpy_s(Id.id, a[i].string);
								for (int i = 0; i < it.size; i++)
								{
									if (!strcmp(Id.id, it.table[i].id))
									{
										Id = it.table[i];
										if (!params && it.table[i].idtype != IT::F) Id.idtype = IT::V; 
										IT::Add(it, Id);
										new_identif = false;
										break;
									}
								}
								if (new_identif)
								{
									strcpy_s(Id.id, (char*)scope.top().c_str()); // . . .
									strcat_s(Id.id, a[i].string);
									for (int i = 0; i < it.size; i++)
									{
										if (!strcmp(Id.id, it.table[i].id))
										{
											Id = it.table[i];
											if (!params && it.table[i].idtype != IT::F) Id.idtype = IT::V;
											IT::Add(it, Id);
											new_identif = false;
											break;
										}
									}
								}
							}
							
							if (new_identif)
							{
								switch (Id.iddatatype)
								{
								case IT::BOOL: Id.value.bool_value = 1;  break;
								case IT::STR: { Id.value.vstr[0].len = 0;} break;
								case IT::INT: { Id.value.chislo.representation = IT::DEC; Id.value.chislo.vint = 0; } break;
								}
								IT::Add(it, Id);
							}new_identif = true;
						} break;
						}
						LT::Add(lt,	Lt);
						break;
					}
					else delete[] a[i].rstates;
				}
				if (!lex_recognized) throw ERROR_THROW_IN(108, lines, -1);
				lex_recognized = false;
				in.stack.pop();
			}
		}
		Lt.lexema = END_OF_LEX; Lt.idxTI = LT_TI_NULLIDX; strcpy_s(Lt.value, LEX_NOT_OPERATION);
		LT::Add(lt, Lt);
	}