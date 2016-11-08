#include <iostream>
#include "huffmanTree.h"
using namespace std;

struct Character {
	char ch;
	int w;
	Character() : ch('!'), w(100000) {}
	Character(char c, int v) : ch(c), w(v) {}
	Character(const Character &c) : ch(c.ch), w(c.w) {}
	bool operator >= (Character &t) {
		return w >= t.w;
	}
	bool operator <= (Character &t) {
		return w <= t.w;
	}
	bool operator > (Character &t) {
		return w > t.w;
	}
	bool operator < (Character &t) {
		return w < t.w;
	}
	Character operator + (const Character &t) {
		Character ch('!', t.w + w);
		return ch;
	}
	friend ostream &operator << (ostream &o, Character &c) {
		o << c.ch << ":" << c.w;
		return o;
	}
};

Character ch[5];

void getCode(char ch, int code) {
	char t[50];
	char tt[50];
	int i = 0;
	while (code) {
		t[i++] = '0' + (code & 1);
		code >>= 1;
	}
	t[i - 1] = '\0';
	for (int j = i - 2; j >= 0; --j)
		tt[i - 2 - j] = t[j];
	tt[i - 1] = '\0';
	cout << ch << ":" << tt << endl;
}

int main() {
	ch[0].ch = 'a'; ch[0].w = 4;
	ch[1].ch = 'b'; ch[1].w = 7;
	ch[2].ch = 'c'; ch[2].w = 5;
	ch[3].ch = 'd'; ch[3].w = 2;
	ch[4].ch = 'e'; ch[4].w = 9;
	HuffmanTree<Character> tree(ch, 5);
	cout << tree;
	tree.getCode(getCode);
	tree.decode(cout, "1100011100010101");
	return 0;
}
