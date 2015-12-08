#include <iostream>
#include "stack.h"

//using namespace std;

const int width = 5;
const int height = 5;

const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {1, -1}};

// (0, 0) (1, 0) (2, 0) (2, 1) (2, 2) (2, 3) (2, 4) (3, 4) (4, 4)
int maze[width][height] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

struct Pos {
	int x, y;
	bool isIn() {
		return (x < width && x >= 0) && (y < height && y >= 0);
	}
	bool equals(Pos &p) {
		return x == p.x && y == p.y;
	}
} start, stop;

std::ostream &operator << (std::ostream &o, Pos p) {
	o << "(" <<p.x << ", " << p.y << ")";
	return o;
}


int main() {
	start.x = start.y = 0;
	stop.x = stop.y = 4;
	Stack<Pos> stack;
	stack.push(start);

	while (!stack.isEmpty()) {
		Pos p;
		p = stack.top();
		if (p.equals(stop)) {
			std::cout << "found!" << std::endl;
			std::cout << stack;
			return 0;
		}
		int i;
		for (i = 0; i < 4; ++i) {
			Pos next;
			next.x = p.x + dir[i][0];
			next.y = p.y + dir[i][1];
			if (next.isIn() && !maze[next.x][next.y]) {
				maze[next.x][next.y] = 1;
				stack.push(next);
				break;
			}
		}
		if (i == 4)
			stack.pop();
	}
	std::cout << "not found!" << std::endl;
	return 0;
}
