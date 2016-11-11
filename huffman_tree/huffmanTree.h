#pragma once
#include "minHeap.h"
#include <iostream>
#include <cstring>


template <class T>
struct HuffmanNode {
	T data;

	HuffmanNode *left, *right, *parent;
	HuffmanNode() : left(NULL), right(NULL), parent(NULL) {}
	HuffmanNode(T v, HuffmanNode *l = NULL, HuffmanNode *r = NULL, HuffmanNode *p = NULL) : left(l), right(r), parent(p), data(v) {}
	bool operator < (HuffmanNode &t) {
		return data < t.data;
	}
	friend std::ostream &operator << (std::ostream &o, HuffmanNode &n) {
		o << n.data;
		return o;
	}
	friend std::ostream &operator << (std::ostream &o, HuffmanNode *&n) {
		o << n->data;
		return o;
	}
};

template<class T>
class CmpPointer {
public:
	bool operator ()(T *a, T *b) {
		return *a < *b;
	}
};

template <class T>
class HuffmanTree {
public:
	HuffmanTree(T w[], int n) {
		MinHeap<HuffmanNode<T> *, CmpPointer<HuffmanNode<T>>> heap(n * n);
		for (int i = 0; i < n; ++i) {
			heap.insert(new HuffmanNode<T>(w[i]));
		}
		
		for (int i = 0; i < n - 1; ++i) {
			HuffmanNode<T> *p1, *p2;
			heap.removeMin(p1);
			heap.removeMin(p2);
			HuffmanNode<T> *p = new HuffmanNode<T>(p1->data + p2->data, p1, p2);
			p1->parent = p2->parent = p;
			heap.insert(p);
			root = p;
		}
	}
	~HuffmanTree() {
		deleteTree(root);
	}
	double getLength() {
		return root->data;
	}

	friend std::ostream &operator << (std::ostream &o, HuffmanTree &t) {
		t.dfs(o, t.root);
		return o;
	}

	void getCode(void(*callback)(char, int)) {
		dfs(root, callback);
	}

	void dfs(HuffmanNode<T> *n, void(*callback)(char, int), int level = 1) {
		if (!n) return;
		if (!n->left && !n->right) {
			callback(n->data.ch, level);
			return;
		}
		level <<= 1;
		dfs(n->left, callback, level);
		dfs(n->right, callback, level | 1);
	}
	void decode(std::ostream &o, const char *str) {
		HuffmanNode<T> *p = root;
		int l = strlen(str);
		for (int i = 0; i < l; ++i) {
			if (str[i] == '1') {
				p = p->right;
			}
			else {
				p = p->left;
			}
			if (p->data.ch != '!') {
				o << p->data.ch;
				p = root;
			}
		}
	}


protected:
	HuffmanNode<T> *root;
	void deleteTree(HuffmanNode<T> *t) {
		if (!t) return;
		deleteTree(t->left);
		deleteTree(t->right);
	}
	void dfs(std::ostream &o, HuffmanNode<T> *n, int level = 0) {
		if (!n) return;
		o.width(level * 6);
		o << *n << std::endl;
		dfs(o, n->left, level + 1);
		dfs(o, n->right, level + 1);
	}

};
