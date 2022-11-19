#pragma once


template<typename T>
class TDynamicStack {
	int top;
	size_t memSize;
	T* pMem;
public:
	TDynamicStack(size_t _memSize = 10) : top(-1), memSize(_memSize), pMem(new T[memSize]) {}
	~TDynamicStack() { delete[] pMem; }
	size_t size() const { return top + 1; }
	bool empty() const { return top == -1; }
	T pop() { return pMem[top--]; }
	void push(const T& val) {
		if (top == memSize - 1) {
			T* tmpMem = new T[memSize * 2];
			std::copy(pMem, pMem + memSize, tmpMem);
			delete[] pMem;
			pMem = tmpMem;
			memSize = memSize * 2;
		}
		pMem[++top] = val;
	}
};


#include <vector>
template<typename T>
class TVectorStack {
	int Itop;
	std::vector<T> mem;
public:
	TVectorStack() : Itop(-1) {}
	size_t size() const { return Itop + 1; }
	bool empty() const { return Itop == -1; }
	T top() { return mem.back(); }
	void pop() { mem.pop_back(); Itop--; }
	void push(const T& val) { mem.push_back(val); Itop++; }
};

#include <queue>
using namespace std;

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