#pragma once
#include <iostream>

template <class T>
class Stack {
public:
	Stack(int sz = 50) : topEl(0), size(sz) {
		data = new T[sz];
	}
	~Stack() {
		delete [] data;
	}
	void push(const T &x) {
		if (topEl == size) throw "Stack was full";
		data[topEl++] = x;
	}
	T &pop() {
		if (!topEl) throw "Stack has no element";
		return data[--topEl];
	}
	T &top() {
		if (!topEl) throw "Stack has no element";
		return data[topEl - 1];
	}
	bool isEmpty() {
		return !topEl;
	}
	int length() {
		return topEl + 1;
	}
	void empty() {
		topEl = 0;
	}
	friend std::ostream &operator << (std::ostream &o, Stack<T> &s) {
		for (int i = 0; i < s.topEl; ++i) {
			o << s.data[i] << " ";
		}
		o << std::endl;
		return o;
	}
private:
	T *data;
	int topEl;
	int size;
};

