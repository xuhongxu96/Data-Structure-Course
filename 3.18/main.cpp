#include <iostream>

const int N = 3;
const int S = 10;

int w[N] = {1, 5, 4};

bool knap(int s, int n) {
	if (s == 0) return true;
	if (s < 0 || (s > 0 && n < 1)) return false;
	return knap(s, n - 1) || knap(s - w[n - 1], n - 1);
}

int main() {
	std::cout << knap(S, N);
	return 0;
}
