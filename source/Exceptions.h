#pragma once
#include <string>
#include <iostream>

#include "Lexeme.h"
using namespace std;

class IException {
public:
	virtual void show() = 0;
};

class LexEx : public IException {
	Lexeme lex;
	string message;
public:
	LexEx(Lexeme l, string m = "LexEx") : lex(l), message(m) {}
	void show() override {
		cout << message << " at " << lex << endl;
	}
};

class BracketEx : public IException {
	Lexeme lex;
	string message;
public:
	BracketEx(Lexeme l, string m = "BracketEx") : lex(l), message(m) {}
	void show() override {
		cout << message << " at " << lex << endl;
	}
};

class OPConflict : public IException {
	Lexeme lex;
	string message;
public:
	OPConflict(Lexeme l, string m = "OPConflict") : lex(l), message(m) {}
	void show() override {
		cout << message << " at " << lex << endl;
	}
};

class ArgsEx : public IException {
	Lexeme lex;
	string message;
public:
	ArgsEx(Lexeme l, string m = "ArgsEx") : lex(l), message(m) {}
	void show() override {
		cout << message << " at " << lex << endl;
	}
};