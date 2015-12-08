#include <iostream>

const int MAXN = 1000;
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

Pos path[MAXN];
int d;

bool DFS (Pos &p, int depth = 0) {
	if (p.equals(stop)) {
		path[depth] = p;
		d = depth;
		return true;
	}
	for (int i = 0; i < 4; ++i) {
		Pos next;
		next.x = p.x + dir[i][0];
		next.y = p.y + dir[i][1];
		if (next.isIn() && !maze[next.x][next.y]) {
			maze[next.x][next.y] = 1;
			Pos old = path[depth];
			path[depth] = p;
			if (DFS(next, depth + 1)) {
				return true;
			}
			path[depth] = old;
			maze[next.x][next.y] = 0;
		}
	}
	return false;
}

int main() {
	start.x = start.y = 0;
	stop.x = stop.y = 4;
	if (DFS(start)) {
		std::cout << "found!" << std::endl;
		for (int i = 0; i <= d; ++i) {
			std::cout << path[i] << std::endl;
		}
	} else {
		std::cout << "not found!" << std::endl;
	}
}
