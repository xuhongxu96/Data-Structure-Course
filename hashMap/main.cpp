#include <iostream>
#include <cstring>
#include "hashMap.h"
using namespace std;

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
