#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <utility>

using namespace std;

int *people = NULL;
int n, s, m;

void remove(int index) {
	cout << people[index] + 1 << endl;
	for (int i = index; i < n - 1; ++i) {
		people[i] = people[i + 1];
	}
	--n;
}

int main () {
	cin >> n >> s >> m;
	if (n <= 0) {
		cerr << "n must be greater than 0" << endl;
		return 1;
	}
	if (m <= 0) {
		cerr << "m must be greater than 0" << endl;
		return 2;
	}
	if (s > n || s <= 0) {
		cerr << "s must be between 1 and " << n << endl;
		return 3;
	}
	--s;
	people = new int[n];
	for (int i = 0; i < n; ++i) people[i] = i;
	int i = (s + m - 1) % n;
	while (n) {
		remove(i);
		if (n)
			i = (i + m - 1) % n;
	}
	delete [] people;
	return 0;
}

