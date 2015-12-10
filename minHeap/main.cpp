#include <iostream>
#include "minHeap.h"
using namespace std;

int main() {
	int arr[] = {1, 43, 54, 32, 45, 2, 54, 3, 6, 8};
	cout << "array of int: " << endl;
	for (int i = 0; i < 10; ++i) cout << arr[i] << " ";
	cout << endl;

	MinHeap<int> minHeap(arr, 10);
	cout << "initial: " << endl << minHeap << endl;
	minHeap.insert(48);
	cout << "insert 48: " << endl << minHeap << endl;

	int m;
	minHeap.removeMin(m);
	cout << "remove min: " << endl << m << endl;
	minHeap.removeMin(m);
	cout << "remove min: " << endl << m << endl;
	cout << "then MinHeap looks like: " << endl << minHeap << endl;

	return 0;
}
