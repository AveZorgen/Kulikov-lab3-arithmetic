#pragma once

#include <queue>
#include <string>

#include "Stack.h"
#include "TypeElem.h"
#include "Lexeme.h"
#include "Operation.h"
#include "Exceptions.h"

class Calculator {
	queue<Lexeme> post;
public:
	Calculator(queue<Lexeme> _post) : post(_post) {}

	double calculate() {
		TDynamicStack<double> st;
		Lexeme lex;
		OPFactory OPF;
		Operation* op = OPF.op(" ");
		double v;
		double lo, ro;
		while (!post.empty()) {
			lex = post.front();

			switch (lex.getType()) {
			case OP:
				op = OPF.op(lex.getStr());
				if (st.empty()) throw new ArgsEx(lex, "missing arg");
				ro = st.pop();
				if (st.empty()) throw new ArgsEx(lex, "missing arg");
				lo = st.pop();
				v = op->calc(lo, ro);
				break;
			case UNOP:
				op = OPF.op(lex.getStr());
				if (st.empty()) throw new ArgsEx(lex, "missing arg");
				ro = st.pop();
				v = op->calc(0, ro);
				break;
			case INT:
				v = stoi(lex.getStr());
				break;
			case DBL:
				v = stod(lex.getStr());
				break;
			default:
				break;
			}
			st.push(v);
			post.pop();
		}
		delete op;
		return st.pop();
	}
};