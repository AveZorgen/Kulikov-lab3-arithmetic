#pragma once
#include <queue>

#include "Stack.h"
#include "Lexeme.h"
#include "Exceptions.h"

template<typename T>
void print(queue<T> t) {
	cout << "Q| ";
	while (!t.empty()) {
		cout << t.front() << " ";
		t.pop();
	}
	cout << "\n";
}

template<typename T>
void printS(TVectorStack<T> t) {
	TVectorStack<T> c;
	cout << "S| ";
	while (!t.empty()) {
		c.push(t.top());
		t.pop();
	}
	while (!c.empty()) {
		cout << c.top() << " ";
		c.pop();
	}
	cout << "\n";
}


class SyntAn {
	queue<Lexeme> inf;

	void bracletsCheck() {
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
		if (o > c) throw new BracketEx({}, "Unclosed (");
	}

public:
	SyntAn(queue<Lexeme> _inf) : inf(_inf) {}

	queue<Lexeme> toPostfix() {
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

	queue<Lexeme> toPostfixE() {
		bracletsCheck();

		queue<Lexeme> res;
		TVectorStack<Lexeme> st;
		Lexeme lex, stLex;
		int o = 0, c = 0;
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
			stLex = st.top(); st.pop();
			res.push(stLex);
		}
		return res;
	}

};