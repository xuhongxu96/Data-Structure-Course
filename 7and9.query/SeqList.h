#pragma once
#include <cstring>
#include <algorithm>

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 30
#endif

template <class T>
class SeqList {
public:
	~SeqList() {
		delete [] data;
	}
	SeqList(int sz = DEFAULT_SIZE) : size(sz), length(0) {
		data = new T[size];
	}
	SeqList(SeqList &list) {
		size = list.size;
		length = list.length;
		data = new T[size];
		memcpy(data, list.data, size * sizeof(T));
	}
	void insert(const T &x) {
		if (length >= size) {
			resize(size * 2);
		}
		data[length++] = x;
	}
	void resize(int sz) {
		T *newData = new T[sz];
		memcpy(newData, data, size * sizeof(T));
		size = sz;
		delete [] data;
		data = newData;
	}
	int getLength() {
		return length;
	}
	void sort(bool (*cmp)(const T &, const T &), int l = 0, int r = -1) {
		if (r == -1) r = length;
		std::sort(data + l, data + r, cmp);
	}
	T &operator [](int index) {
		return data[index];
	}
protected:
	T *data;
	int size;
	int length;
};
