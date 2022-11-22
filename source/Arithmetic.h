#include <queue>

#include "Lexeme.h"


class Arithmetic {
public:
	//lexicaal analysis
	queue<Lexeme> lex(string inp);

	//syntax analysis
	void Validate(queue<Lexeme> inf);

	queue<Lexeme> toCanonicPostfix(queue<Lexeme> inf);  //E;E;E; => EpEpEp;;;
	queue<Lexeme> toModifiedPostfix(queue<Lexeme> inf); //E;E;E; => Ep;Ep;Ep;

	//calculate postfix form
	queue<double> calculate(queue<Lexeme> post);

	queue<double> perform(string inp) {
		queue<Lexeme> lex_res = lex(inp);
		Validate(lex_res);
		queue<Lexeme> synt_res = toModifiedPostfix(lex_res);
		queue<double> res = calculate(synt_res);
		return res;
	}
};