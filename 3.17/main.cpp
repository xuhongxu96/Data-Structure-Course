#include <iostream>
#include <cstring>

bool col[8], dia1[15], dia2[15];
int res[8];
int ct = 0;

void DFS(int row) {
	if (row == 8) {
		std::cout << "Sol. " << ++ct << std::endl;
		for (int i = 0; i < 8; ++i) {
			std::cout << i << " " << res[i] << std::endl;
		}
		std::cout << "----------------------" << std::endl;
		return;
	}
	for (int i = 0; i < 8; ++i) {
		if (col[i] || dia1[7 - row + i] || dia2[row + i]) continue;
		col[i] = true;
		dia1[7 - row + i] = true;
		dia2[row + i] = true;
		res[row] = i;
		DFS(row + 1);
		col[i] = false;
		dia1[7 - row + i] = false;
		dia2[row + i] = false;
	}
}

int main() {
	memset(col, 0, sizeof(col));
	memset(dia1, 0, sizeof(dia1));
	memset(dia2, 0, sizeof(dia2));
	DFS(0);
	return 0;
}
