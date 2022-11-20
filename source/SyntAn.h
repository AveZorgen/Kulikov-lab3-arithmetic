#pragma once
#include <queue>

#include "Stack.h"
#include "Lexeme.h"
#include "Exceptions.h"


class SyntAn {
	//to use with no ; need to del EOE check
	void Validate(queue<Lexeme> inf) {
		queue<Lexeme> ch(inf);
		int o = 0, c = 0;
		Lexeme lex;
		Lexeme prev;
		while (!ch.empty()) {
			lex = ch.front();

			if (lex.getStr() == "(") o++;
			else if (lex.getStr() == ")") c++;
			if (c > o) throw new BracketEx(lex, "Extra )");

			if (prev.getType() == UNOP && lex.getType() == OP) throw new OPConflict(lex, "OP after UNOP");
			//else if (prev.getType() == OP && lex.getType() == OP) throw new OPConflict(lex, "OP after OP"); //не считать () за OP

			prev = lex;
			ch.pop();
		}
		if (lex.getType() != EOE) throw new OPConflict(lex, "missing ;");
		if (o > c) throw new BracketEx({}, "Unclosed (");
	}

public:
	//; unsupported
	queue<Lexeme> toPostfix(queue<Lexeme> inf) {
		queue<Lexeme> res;
		TVectorStack<Lexeme> st;
		Lexeme lex, stLex;
		while (!inf.empty()) {
			lex = inf.front();
			if (lex.getType() == INT || lex.getType() == DBL) {
				res.push(lex);
			}
			if (lex.getStr() == "(") {
				st.push(lex);
			}
			else if (lex.getStr() == ")") {
				stLex = st.top(); st.pop();
				while (stLex.getStr() != "(") {
					res.push(stLex);
					stLex = st.top(); st.pop();
				}
			}
			else if (lex.getType() == OP || lex.getType() == UNOP) {
				while (!st.empty()) {
					stLex = st.top(); st.pop();
					if (lex.getPriority() <= stLex.getPriority()) {
						res.push(stLex);
					}
					else {
						st.push(stLex);
						break;
					}
				}
				st.push(lex);
			}
			inf.pop();
		}
		while (!st.empty()) {
			stLex = st.top(); st.pop();
			res.push(stLex);
		}
		return res;
	}

	//; unsupported
	queue<Lexeme> toPostfixE(queue<Lexeme> inf) {
		Validate(inf);

		queue<Lexeme> res;
		TVectorStack<Lexeme> st;
		Lexeme lex, stLex;
		while (!inf.empty()) {
			lex = inf.front();

			if (lex.getType() == INT || lex.getType() == DBL) {
				res.push(lex);
			}
			if (lex.getType() == OP || lex.getType() == UNOP) {
				if (lex.getStr() != "(")
					while (!st.empty()) {
						stLex = st.top(); st.pop();
						if (lex.getPriority() <= stLex.getPriority())
							res.push(stLex);
						else {
							if (stLex.getStr() != "(")
								st.push(stLex);
							break;
						}
					}
				if (lex.getStr()!=")")
					st.push(lex);
			}
			inf.pop();
		}
		while (!st.empty()) {
			cout << "here\n";
			printS(st);	print(res);
			stLex = st.top(); st.pop();
			res.push(stLex); 
		}
		return res;
	}

	queue<Lexeme> perform(queue<Lexeme> inf) {
		Validate(inf);

		queue<Lexeme> res;
		TVectorStack<Lexeme> st;
		Lexeme lex, stLex;

		while (!inf.empty()) {
			lex = inf.front();
			while (lex.getType() != EOE) {
				if (lex.getType() == INT || lex.getType() == DBL) {
					res.push(lex);
					//printS(st);	print(res);
				}
				if (lex.getType() == OP || lex.getType() == UNOP) {
					if (lex.getStr() != "(")
						while (!st.empty()) {
							stLex = st.top(); st.pop();
							if (lex.getPriority() <= stLex.getPriority()) {
								res.push(stLex);
								//printS(st);	print(res);
							}
							else {
								if (stLex.getStr() != "(")
									st.push(stLex);
								//printS(st);	print(res);
								break;
							}
						}
					if (lex.getStr() != ")")
						st.push(lex);
					//printS(st);	print(res);
				}
				inf.pop();
				lex = inf.front();
			}
			while (!st.empty()) {
				//cout << "here";
				//printS(st);	print(res);
				stLex = st.top(); st.pop();
				res.push(stLex); 
			}
			inf.pop();
			res.push(lex);
		}
		return res;
	}
};