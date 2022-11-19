#include <queue>
#include <iostream>

#include "Stack.h"
#include "LexAn.h"
#include "SyntAn.h"
#include "Calculator.h"
#include "Exceptions.h"

using namespace std;


int main() {
	string str = "2-.5"; //"2-3"  "-5+(-1+3)"  "(-123 - +10)/-50 * \t- 30" "((3 - -5) * (4-2))" "3 - * - 5"
	cout << .2 << endl;
	cout << str << endl << endl;
	queue<Lexeme> lex_res, synt_res;
	double res = 0;
	LexAn LA(str);
	try {
		lex_res = LA.lex(); print(lex_res); cout << endl;
		SyntAn SA(lex_res);
		synt_res = SA.toPostfixE(); print(synt_res); cout << endl;
		Calculator C(synt_res);
		res = C.calculate(); cout << res;
	}
	catch (IException* e) {
		e->show();
	}

	return 0;
}

/*
* лекс V
* синт V
* ошибки V
* double V
* 3+2;3-1; X
* abc-10; abc-2; X
* f(a,b): a+b; //некая польская запись с именем f /// f(10,20);f(10,40); X
* if E then <op>; X
*/