#include <iostream>
#include "ChainList.h"

int main() {

	try {

		ChainList<int> list;
		for (int i = 0; i < 10; ++i)
			list.insert(i);
		list.insert(0, 10);
		list.insert(0, 10);
		ChainNode<int> *v = list.locate(11);
		std::cout << (v == NULL ? NULL : v->val) << std::endl;
		list.output();
		std::cout << std::endl << "Max: " << list.max() << std::endl;
		std::cout << "Count of 10: " << list.number(10) << std::endl;

		ChainList<int> list2;
		int arr[] = {10, 2, 5, 3, 2, 12};
		list2.create(arr, 6);
		list2.output();

		std::cout << std::endl;

		ChainList<int> list3;
		int arr2[] = {1, 2, 2, 3, 3, 3, 4, 9};
		list3.create(arr2, 8);
		list3.tidyup();
		list3.output();
		std::cout << std::endl;
		list3.reverse();
		list3.output();

	} catch (const char *e) {

		std::cerr << e << std::endl;

	}
	return 0;
}
