#include <iostream>
#include "huffmanTree.h"
using namespace std;

struct Character {
	char ch;
	int w;
	Character() : ch('\0'), w(0) {}
	Character(char c, int v) : ch(c), w(v) {}
	Character(Character &c) : ch(c.ch), w(c.w) {}
	bool operator <= (Character &t) {
		return w <= t.w;
	}
	bool operator > (Character &t) {
		return w > t.w;
	}
	bool operator < (Character &t) {
		return w < t.w;
	}
};

Character ch[5];

int main() {
	ch[0].ch = 'a'; ch[0].w = 4;
	ch[1].ch = 'b'; ch[1].w = 7;
	ch[2].ch = 'c'; ch[2].w = 5;
	ch[3].ch = 'd'; ch[3].w = 2;
	ch[4].ch = 'e'; ch[4].w = 9;
	HuffmanTree<Character> tree(ch, 5);
	return 0;
}
