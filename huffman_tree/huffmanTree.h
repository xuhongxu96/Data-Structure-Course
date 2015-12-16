#pragma once
#include "minHeap.h"

template <class T>
struct HuffmanNode {
	T data;
	HuffmanNode *left, *right, *parent;
	HuffmanNode() : left(NULL), right(NULL), parent(NULL) {}
	HuffmanNode(T v, HuffmanNode *l = NULL, HuffmanNode *r = NULL, HuffmanNode *p = NULL) : left(l), right(r), parent(p), data(v) {}
	bool operator <= (HuffmanNode &t) {
		return data <= t.data;
	}
	bool operator > (HuffmanNode &t) {
		return data > t.data;
	}
	bool operator < (HuffmanNode &t) {
		return data < t.data;
	}
};

template <class T>
class HuffmanTree {
public:
	HuffmanTree(T w[], int n) {
		MinHeap<HuffmanNode<T> *> heap(n * n);
		for (int i = 0; i < n; ++i) {
			heap.insert(new HuffmanNode<T>(w[i]));
		}
		for (int i = 0; i < n - 1; ++i) {
			HuffmanNode<T> *p1, p2;
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
protected:
	HuffmanNode<T> *root;
	void deleteTree(HuffmanNode<T> *t) {
		if (!t) return;
		deleteTree(t->left);
		deleteTree(t->right);
	}
};
