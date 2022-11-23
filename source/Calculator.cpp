#pragma once

#include <string>

#include "Stack.h"
#include "Operation.h"
#include "Exceptions.h"

#include "Arithmetic.h"

queue<double> Arithmetic::calculate(queue<Lexeme> post) {
		TVectorStack<double> st;
		queue<double> res;
		Lexeme lex;
		OPFactory OPF;
		Operation* op = OPF.op(" ");
		double lo, ro;
		Lexeme assignedLex; //if empty?
		if (!post.empty()) assignedLex = post.front();
		while (!post.empty()) {
			lex = post.front();

			switch (lex.getType()) {
			case OP:
				op = OPF.op(lex.getStr());
				if (st.empty()) throw new ArgsEx(lex, "Missing arg");
				ro = st.top(); st.pop();
				if (st.empty()) throw new ArgsEx(lex, "Missing arg");
				lo = st.top(); st.pop();
				if (lex.getStr() == "=") {
					store(assignedLex.getStr(), op->calc(lo, ro));
				}
				st.push(op->calc(lo, ro));
				post.pop();
				break;
			case UNOP:
				op = OPF.op(lex.getStr());
				if (st.empty()) throw new ArgsEx(lex, "Missing arg");
				ro = st.top(); st.pop();
				st.push(op->calc(0, ro));
				post.pop();
				break;
			case INT:
				st.push(stoi(lex.getStr()));
				post.pop();
				break;
			case DBL:
				st.push(stod(lex.getStr()));
				post.pop();
				break;
			case VAR:
				st.push(load(lex.getStr()));
				post.pop();
				break;
			case EOE:
				res.push(st.top());
				st.pop();
				post.pop();
				if (!post.empty()) assignedLex = post.front();
				break;
			default:
				post.pop();
				break;
			}
		}
		delete op; 
		if (!st.empty()) throw new ArgsEx(lex, "Missing operation");
		return res;
	}