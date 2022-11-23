#pragma once

#include <iostream>
#include "Exceptions.h"

using namespace std;

class Operation {
public:
	virtual double calc(double r, double l) = 0;
};

class add : public Operation {
public:
	double calc(double l, double r) override { return l + r; }
};

class sub : public Operation {
public:
	double calc(double l, double r) override { return l - r; }
};

class mul : public Operation {
public:
	double calc(double l, double r) override { return l * r; }
};

class divO : public Operation {
public:
	double calc(double l, double r) override { if (r == 0) throw new ArgsEx({}, "Zero division");  return l / r; }
};

class none : public Operation {
public:
	double calc(double l, double r) override { return r; }
};

class asg : public Operation {
public:
	double calc(double l, double r) override { return r; }
};


class OPFactory {
public:
	Operation* op(string str) {
		if (str == "+") return new add;
		if (str == "-") return new sub;
		if (str == "*") return new mul;
		if (str == "/") return new divO;
		if (str == "=") return new asg;
		return new none;
	}
};