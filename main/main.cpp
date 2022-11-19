#include <queue>
#include <iostream>

#include "Stack.h"
#include "LexAn.h"
#include "SyntAn.h"
#include "Calculator.h"
#include "Exceptions.h"

using namespace std;


int main() {
	string str = "(-123 - +10)/-50 * \t- 30; ((3 - -5) * (4-2));"; //"2;3-5;" "2-3"  "-5+(-1+3)"  "(-123 - +10)/-50 * \t- 30" "((3 - -5) * (4-2))" "3 - * - 5" "-5+-1+3"
	//str = "2 4 -;";// �� ��� �����������, �� � �������� ��������� ���������
	//cout << str << endl << endl;
	queue<Lexeme> lex_res, synt_res;
	queue<double> res;
	LexAn LA;
	SyntAn SA;
	Calculator C;
	try {
		lex_res = LA.lex(str); print(lex_res); cout << endl;
		synt_res = SA.perform(lex_res); print(synt_res); cout << endl;
		res = C.calculate(synt_res); print(res);
	}
	catch (IException* e) {
		e->show();
	}

	//print(LA.lex(" - - 2"));
	//print(LA.lex(" - 2"));
	//print(LA.lex(" 3 - 2"));
	//print(LA.lex(" 3 + - 2"));
	//print(LA.lex(" 3 ) - - 2"));
	//print(LA.lex(" 3 * - 2"));
	//print(LA.lex(" 3 ) * - 2"));
	//print(LA.lex(" 3 ) - 2"));

	return 0;
}

/*
* ���� V
* ���� V
* ������ V
* double V
* 3+2;3-1; X
* abc-10; abc-2; X
* f(a,b): a+b; //����� �������� ������ � ������ f /// f(10,20);f(10,40); X
* if E then <op>; X
*/