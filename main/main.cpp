#include <queue>
#include <iostream>

#include "Stack.h"
#include "Exceptions.h"
#include "Arithmetic.h"

using namespace std;


int main() {
	string str = "a = 3 * 2-15;(-123 - +10)/-50 * \t- a; -5+(-1+b*2);"; //"2;3-5;" "2-3"  "-5+(-1+3)"  "(-123 - +10)/-50 * \t- 30" "((3 - -5) * (4-2))" "3 - * - 5" "-5+-1+3"
	queue<Lexeme> lex_res, synt_res;
	queue<double> res;
	Arithmetic a;
	try {
		lex_res = a.lex(str); print(lex_res); cout << endl;
		a.Validate(lex_res);
		synt_res = a.toModifiedPostfix(lex_res); print(synt_res); cout << endl;
		res = a.calculate(synt_res); print(res);
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
* 3+2;3-1; V
* abc=10; abc-2; V
* f(a,b): a+b; //некая польская запись с именем f /// f(10,20);f(10,40); X
* if E then <op>; X
*/