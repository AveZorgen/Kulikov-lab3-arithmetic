#pragma once

#include <queue>
#include <string>

#include "Stack.h"
#include "TypeElem.h"
#include "Lexeme.h"
#include "Operation.h"
#include "Exceptions.h"

class Calculator {
public:
	//to use with no ; need to res.push(st.top()); st.pop(); when post.empty
	queue<double> calculate(queue<Lexeme> post) {
		TVectorStack<double> st;
		queue<double> res;
		Lexeme lex;
		OPFactory OPF;
		Operation* op = OPF.op(" ");
		double lo, ro;
		while (!post.empty()) {
			lex = post.front();

			switch (lex.getType()) {
			case OP:
				op = OPF.op(lex.getStr());
				if (st.empty()) throw new ArgsEx(lex, "Missing arg");
				ro = st.top(); st.pop();
				if (st.empty()) throw new ArgsEx(lex, "Missing arg");
				lo = st.top(); st.pop();
				st.push(op->calc(lo, ro));
				break;
			case UNOP:
				op = OPF.op(lex.getStr());
				if (st.empty()) throw new ArgsEx(lex, "Missing arg");
				ro = st.top(); st.pop();
				st.push(op->calc(0, ro));
				break;
			case INT:
				st.push(stoi(lex.getStr()));
				break;
			case DBL:
				st.push(stod(lex.getStr()));
				break;
			case EOE:
				res.push(st.top());
				st.pop();
				break;
			default:
				break;
			}
			post.pop();
		}
		delete op; 
		if (!st.empty()) throw new ArgsEx(lex, "Missing operation");
		return res;
	}
};