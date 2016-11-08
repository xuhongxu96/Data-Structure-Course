#pragma once
#include <cstring>
#include <iostream>

#define DEFAULT_SIZE  10

template <class T>
class MinHeap {
	T *data;
	int size;
	void shiftDown(int start, int m) {
		int j = start * 2 + 1;
		T temp = data[start];
		while (j <= m) {
			if (j < m && data[j] > data[j + 1]) ++j;
			if (temp <= data[j]) break;
			data[start] = data[j];
			start = j;
			j = j * 2 + 1;
		}
		data[start] = temp;
	}
	void shiftUp(int start) {
		int i = (start - 1) / 2;
		T temp = data[start];
		while (start > 0) {
			if (temp >= data[i]) break;
			data[start] = data[i];
			start = i;
			i = (i - 1) / 2;
		}
		data[start] = temp;
	}
	void dfs(std::ostream &o, int index, int level = 0) {
		if (index >= size) return;
		o.width(level * 6);
		o << data[index] << std::endl;
		dfs(o, index * 2 + 1, level + 1);
		dfs(o, index * 2 + 2, level + 1);
	}
public:
	~MinHeap() {
		delete [] data;
	}
	MinHeap(int sz = DEFAULT_SIZE) : size(0) {
		data = new T[sz];
	}

	MinHeap(T arr[], int n) : size(n) {
		data = new T[n * 2];
		memcpy(data, arr, n * sizeof(T));
		int currentPos = (n - 2) / 2;
		while (currentPos >= 0) {
			shiftDown(currentPos, n - 1);
			--currentPos;
		}
	}
	void insert(const T &x) {
		data[size] = x;
		shiftUp(size);
		++size;
	}
	void removeMin(T &x) {
		x = data[0];
		data[0] = data[--size];
		shiftDown(0, size - 1);
	}
	bool isEmpty() const {
		return size == 0;
	}
	void empty() {
		size = 0;
	}
	friend std::ostream &operator <<(std::ostream &o, MinHeap<T> &heap) {
		heap.dfs(o, 0);
		return o;
	}
};
