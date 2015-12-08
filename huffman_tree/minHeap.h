#include <cstring>
template <class T>
class MinHeap {
	const int DEFAULT_SIZE = 10;
	T *data;
	int head;
	int tail;
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
		data[j] = temp;
	}
	void shiftUp(int start) {
		int i = (start - 1) / 2;
		T temp = data[start];
		while (i >= 0) {
			if (temp >= data[i]) break;
			data[start] = data[i];
			start = i;
			i = (i - 1) / 2;
		}
		data[i] = temp;
	}
public:
	MinHeap(int sz = DEFAULT_SIZE) : head(0), tail(0), size(sz) {
		data = new T[sz];
	}

	MinHeap(T arr[], int n) : head(0), tail(n - 1), size(n) {
		data = new T[n];
		memcpy(data, T, n);
		int currentPos = (n - 2) / 2;
		while (currentPos >= 0) {
			shiftDown(currentPos, n - 1);
			--currentPos;
		}
	}
	~MinHeap() {
		delete [] data;
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
}
