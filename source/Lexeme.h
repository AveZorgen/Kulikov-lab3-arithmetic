#pragma once
#include <iostream>
#include "TypeElem.h"

using namespace std;

class Lexeme {
	string str;
	TypeElem type;
	int start;
public:
	Lexeme(string _str = "", TypeElem _type = NONE, int _start = -1) : str(_str), type(_type), start(_start) {}
	string getStr() { return str; }
	TypeElem getType() { return type; }
	friend ostream& operator<<(ostream& os, const Lexeme& l) {
		os << "{" << l.str << ", ";
		if (l.type == OP) os << "OP";
		if (l.type == UNOP) os << "UNOP";
		if (l.type == INT) os << "INT";
		if (l.type == DBL) os << "DBL";
		if (l.type == VAR) os << "VAR";
		if (l.type == EOE) os << "EOE";
		if (l.type == NONE) os << "NONE";
		os << ", " << l.start << "}";
		return os;
	}
	int getPriority() {
		if (type == OP) {
			if (str == "=") return -1;
			if (str == "(") return 0;
			if (str == ")") return 1;
			if (str == "+" || str == "-") return 2;
			if (str == "*" || str == "/") return 3;
		}
		if (type == UNOP) {
			if (str == "+" || str == "-") return 4;
		}
		if (type == EOE) {
			return -2;
		}
		return -3;
	}
};