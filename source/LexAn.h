#pragma once
#include <string>
#include <iostream>
#include <queue>

#include "TypeElem.h"
#include "Lexeme.h"
#include "Exceptions.h"

class LexAn {
public:
	queue<Lexeme> lex(string inp) {
		queue<Lexeme> res;
		inp = inp + " ";
		int i, start;
		string buff = "";
		string OPS = "+-*/()";
		string UNOPS = "+-";
		string sep = " \t\n";

		int st = 0; //cout << 0 << "\n";
		for (i = 0, start = 0; i < inp.size(); i++) {
			char c = inp[i];
			//cout << c << "| ";
			switch (st) {
			case 0:
				if (c >= '0' && c <= '9') {
					start = i;
					buff = c;
					st = 1;
					break;
				}
				if (c == '.') {
					start = i;
					buff = "0.";
					st = 3;
					break;
				}
				if (c == ')') {
					start = i;
					buff = c;
					res.push({ buff,OP,start });
					st = 0;
					break;
				}
				if (OPS.find(c) != string::npos) {
					start = i;
					buff = c;
					if (res.empty() && UNOPS.find(c) != string::npos) ////empty �� ������� ������ ;  "-2-3;3+2" = OK, "-2-3;-3+2" - �� ��
						res.push({ buff,UNOP,start });
					else
						res.push({ buff,OP,start });
					st = 2;
					break;
				}
				if (sep.find(c) != string::npos) {
					buff = "";
					break;
				}
				if (c == ';') {
					start = i;
					buff = c;
					res.push({ buff, EOE, start });
					st = 2;
					break;
				}
				throw new LexEx({ {c}, NONE, i }, "Unexpected lex");
			case 1:
				if (c >= '0' && c <= '9') {
					buff += c;
					break;
				}
				if (c == ')') {
					res.push({ buff, INT, start });
					start = i;
					buff = c;
					res.push({ buff, OP, start });
					st = 0;
					break;
				}
				if (OPS.find(c) != string::npos) {
					res.push({ buff, INT, start });
					start = i;
					buff = c;
					res.push({ buff, OP, start });
					st = 2;
					break;
				}
				if (sep.find(c) != string::npos) {
					res.push({ buff, INT, start });
					start = i;
					st = 0;
					break;
				}
				if (c == '.') {
					buff += c;
					st = 3;
					break;
				}
				if (c == ';') {
					res.push({ buff, INT, start });
					start = i;
					buff = c;
					res.push({ buff, EOE, start });
					st = 0;
					break;
				}
				throw new LexEx({ {c}, NONE, i }, "Unexpected lex");
			case 2: 
				if (c >= '0' && c <= '9') {
					start = i;
					buff = c;
					st = 1;
					break;
				}
				if (c == '.') {
					start = i;
					buff = "0.";
					st = 3;
					break;
				}
				if (UNOPS.find(c) != string::npos) {
					start = i;
					buff = c;
					res.push({ buff, UNOP, start });
					break;
				}
				else if (OPS.find(c) != string::npos) {
						start = i;
						buff = c;
						res.push({ buff, OP, start });
						st = 0;
						break;
					}
				if (sep.find(c) != string::npos) {
					buff = "";
					break;
				}
				if (c == ';') {
					start = i;
					buff = c;
					res.push({ buff, EOE, start });
					break;
				}
				throw new LexEx({ {c}, NONE, i }, "Unexpected lex");
			case 3:
				if (c >= '0' && c <= '9') {
					buff += c;
					st = 4;
					break;
				}
				throw new LexEx({ {c}, NONE, i }, "Unexpected lex");
			case 4:
				if (c >= '0' && c <= '9') {
					buff += c;
					break;
				}
				if (c == ')') {
					res.push({ buff, DBL, start });
					start = i;
					buff = c;
					res.push({ buff, OP, start });
					st = 0;
					break;
				}
				if (OPS.find(c) != string::npos) {
					res.push({ buff, DBL, start });
					start = i;
					buff = c;
					res.push({ buff, OP, start });
					st = 2;
					break;
				}
				if (sep.find(c) != string::npos) {
					res.push({ buff, DBL, start });
					start = i;
					st = 0;
					break;
				}
				if (c == ';') {
					res.push({ buff, DBL, start });
					start = i;
					buff = c;
					res.push({ buff, EOE, start });
					st = 0;
					break;
				}
			default:
				break;
			}
			//cout << st << "\n";
		}
		return res;
	}
};