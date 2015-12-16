#pragma once

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

#define max(a, b) (a > b ? a : b)
template <class T>
struct TreeNode {
	T data;
	TreeNode<T> *left, *right;
	TreeNode() : left(NULL), right(NULL) {}
	TreeNode(T x, TreeNode<T> *l = NULL, TreeNode<T> *r = NULL) : data(x), left(l), right(r) {}
};

template <class T>
class Tree {
protected:
	TreeNode<T> *root;
	T nullValue;
	void destroy(TreeNode<T> *root) {
		if (root == NULL) return;
		destroy(root->left);
		destroy(root->right);
		delete root;
	}
	void dfs(int *count, TreeNode<T> *p = NULL, int depth = 0) {
		if (!p) p = root;
		++count[depth];
		if (p->left)
			dfs(count, p->left, depth + 1);
		if (p->right)
			dfs(count, p->right, depth + 1);
	}
	void dfs(std::ostream &o, TreeNode<T> *p = NULL, int depth = 0) {
		if (!p) p = root;
		if (o) {
			o.width(depth * 3);
			o << p->data << std::endl;
		}
		if (p->left)
			dfs(o, p->left, depth + 1);
		if (p->right)
			dfs(o, p->right, depth + 1);
	}
	int dfs(int val, TreeNode<T> *p, int depth = 1) {
		if(!p) return 0;
		if(p->data == val) return depth;
		return dfs(val, p->left, depth + 1) | dfs(val, p->right, depth + 1);
	}
public:
	Tree() : root(NULL) {}
	Tree(Tree<T> &t) : root(t.root) {}
	~Tree() {destroy(root);}

	void setNullElementValue(T null) {
		nullValue = null;
	}
	void fromArray(T *arr, int n) {
		if (n<0) return;
		TreeNode<T> **nodes = new TreeNode<T>*[n];

		for (int i = n - 1; i >= 0; --i) {
			TreeNode<T> *l = NULL, *r = NULL;
			if (arr[i] == nullValue) {
				nodes[i] = NULL;
				continue;
			}
			
			if (2 * i + 1 < n) {
				l = nodes[2 * i + 1];
				if (2 * i + 2 < n) {
					r = nodes[2 * i + 2];
				}
			}
			
			nodes[i] = new TreeNode<T>(arr[i], l, r);
		}
		root = nodes[0];
		delete [] nodes;
	}

	int countDegree(int degree = 1, TreeNode<T> *p = NULL) {
		if (!p) p = root;
		return (p->left ? countDegree(degree, p->left) : 0)
			+ (p->right ? countDegree(degree, p->right) : 0)
			+ ((p->left ? 1 : 0) + (p->right ? 1 : 0) == degree);
	}

	int getDepth(TreeNode<T> *p = NULL) {
		if (!p) p = root;
		int ret = 1;
		if (p->left)
			ret = max(ret, 1 + getDepth(p->left));
		if (p->right)
			ret = max(ret, 1 + getDepth(p->right));
		return ret;
	}

	int getWidth() {
		int d = getDepth();
		int *count = new int[d];
		memset(count, 0, d);
		dfs(count);
		int w = count[0];
		for (int i = 1; i < d; ++i) {
			w = max(w, count[i]);
		}
		delete [] count;
		return w;
	}

	void removeLeaves(TreeNode<T> **pp = NULL) {
		if (!pp) pp = &root;
		TreeNode<T> *p = *pp;
		if (!p->left && !p->right) {
			if (p == root) return;
			delete p;
			*pp = NULL;
			return;
		}
		if (p->left)
			removeLeaves(&(p->left));
		if (p->right)
			removeLeaves(&(p->right));

	}

	int getLevel(T val) {
		return dfs(val, root);
	}

	T findMax(TreeNode<T> **pp = NULL) {
		if (!pp) pp = &root;
		TreeNode<T> *p = *pp;
		if (!p->left && !p->right) {
			return p->data;
		}
		T m, n;
		if (p->left)
			m = findMax(&(p->left));
		if (p->right)
			n = findMax(&(p->right));
		return max(m, max(p->data, n));
	}

	void preorder(TreeNode<T> **pp = NULL, int depth = 1) {
		if (!pp) pp = &root;
		TreeNode<T> *p = *pp;
		std::cout << p->data << " [" << depth << "]" << std::endl;
		if (p->left)
			preorder(&(p->left), depth + 1);
		if (p->right)
			preorder(&(p->right), depth + 1);
	}
	
	friend std::istream &operator >>(std::istream &in, Tree<T> &tree) {
		int n;
		in >> n;
		int *m = new int[n];
		for (int i = 0; i < n; ++i) in >> m[i];
		tree.fromArray(m, n);
		return in;
	}

	friend std::ostream &operator <<(std::ostream &o, Tree<T> &tree) {
		tree.dfs(o);
		return o;
	}

};
