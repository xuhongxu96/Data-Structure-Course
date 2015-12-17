#include <iostream>
#include <cstring>
#include "hashMap.h"
using namespace std;

int val(const int *p) {
	if (p) return *p;
	return -1;
}

int hashf(const char *const &k, int d) {
	int ret = 0;
	for (int i = 0; k[i]; ++i) {
		if (k[i] < 0) ret += -k[i] % d;
		else ret += k[i] % d;
		ret <<= d;
	}
	return ret % d;
}

bool equalf(const char *const &k, const char *const &k2) {
	return strcmp(k, k2) == 0;
}

int main() {
	HashMap<const char *, int> map(hashf, equalf);
	map.insert("北京", 0);
	map.insert("上海", 1);
	map.insert("济南", 3);
	cout << val(map.find("济南")) << endl;
	cout << val(map.find("北京")) << endl;
	cout << val(map.find("上海")) << endl;
	cout << val(map.find("南京")) << endl;
	return 0;
}
