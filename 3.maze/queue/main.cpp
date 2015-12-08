#include <iostream>
#include "queue.h"

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

Pos prev[width][height];
Pos path[MAXN];

int main() {
	start.x = start.y = 0;
	stop.x = stop.y = 4;
	prev[0][0].x = prev[0][0].y = -1;
	Queue<Pos> queue;
	queue.insert(start);

	while (!queue.isEmpty()) {
		try {
			Pos p = queue.remove();
			if (p.equals(stop)) {
				std::cout << "found" << std::endl;
				int i = 0;
				path[i] = p;
				while (path[i].x != -1) {
					p = path[i];
					path[++i] = prev[p.x][p.y];
				}
				for (int j = i - 1; j >= 0; --j) {
					std::cout << path[j] << std::endl;
				}
				return 0;
			}

			Pos next;
			for (int i = 0; i < 4; ++i) {
				next.x = p.x + dir[i][0];
				next.y = p.y + dir[i][1];
				if (next.isIn() && !maze[next.x][next.y]) {
					maze[next.x][next.y] = 1;
					prev[next.x][next.y] = p;
					queue.insert(next);
				}
			}
		} catch (const char *e) {
			std::cerr << e <<std::endl;
		}
	}
	std::cout << "not found!" << std::endl;
}
