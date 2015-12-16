#include <iostream>
#include "tree.h"
using namespace std;

/*
 * Program: 5.27 & 5.37
 *
 * Description:
 *	我将 5.27 和 5.37 的作业内容编写在同一程序中，代价就是
 *	5.37 要求的一般树的缩进输出我实现成了二叉树的缩进输出，
 *	我认为原理类似，影响不大。毕竟所有功能实现在一起更加简
 *	洁和方便。请助教检阅！
 *
 */

int main() {
	Tree<int> tree;
	tree.setNullElementValue(-1);
	cin >> tree;
	cout << "0 degree node count: " << endl; // (3)
	cout << tree.countDegree(0) << endl << endl; 
	cout << "1 degree node count: " << endl; // (1)
	cout << tree.countDegree() << endl << endl;
	cout << "2 degree node count: " << endl; // (2)
	cout << tree.countDegree(2) << endl << endl;
	cout << "tree depth: " << endl; // (4)
	cout << tree.getDepth() << endl << endl;
	cout << "tree width: " << endl; // (5)
	cout << tree.getWidth() << endl << endl;
	cout << "tree tab graph: " << endl; // 5.37
	cout << tree << endl;
	cout << "max: " << tree.findMax() << endl; // (8)
	cout << "level of 8: " << tree.getLevel(8) << endl; // (7)
	cout << "preorder: " << endl; // (9)
	tree.preorder();
	tree.removeLeaves();
	cout << "after remove leaves: " << endl; // (6)
	cout << tree << endl;
	cout << "level of 5: " << tree.getLevel(5) << endl; 
	cout << "max: " << tree.findMax() << endl; // (8)
	cout << "preorder: " << endl; // (9)
	tree.preorder();

	return 0;
}
