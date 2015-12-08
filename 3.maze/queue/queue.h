#pragma once
#include <iostream>

template <class T>
class Queue {
public:
	Queue(int sz = 50) : front(0), rear(0), size(sz) {
		data = new T[sz];
	}
	void insert(const T &x) {
		if (isFull()) throw "no space";
		data[rear++] = x;
		rear %= size;
	}

	T &remove() {
		if (isEmpty()) throw "no element";
		T &res = data[front++];
		front %= size;
		return res;
	}

	T &getFront() {
		return data[front];
	}

	bool isEmpty() {
		return front == rear;
	}

	void empty() {
		front = rear = 0;
	}

	bool isFull() {
		return (rear + 1) % size == front;
	}

	int getSize() {
		return size;
	}

	~Queue() {
		delete [] data;
	}

	friend std::ostream &operator <<(std::ostream &o, Queue<T> &q) {
		for (int i = q.front; i != q.rear; i = (i + 1) % q.size) {
			o << q.data[i] << " ";
		}
		return o;
	}
private:
	T *data;
	int front, rear;
	int size;
};

