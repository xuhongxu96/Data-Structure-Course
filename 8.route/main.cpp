#include <iostream>
#include <cstring>
#include <utility>
#include "hashMap.h"
#include "ChainList.h"
#include "minHeap.h"
using namespace std;

/*
 * Constant
 *
 */

const int N = 16;
const int M = N * (N - 1) / 2;

/*
 * Flight Structure
 * and Data
 *
 */
struct Flight {
	char id[10], start[20], end[20];
	int startTime, endTime;
	int startID, endID;
	int fee;
	Flight(
	    const char *i,
	    const char *s,
	    const char *e,
	    int st,
	    int et,
	    int f
	) : startTime(st), endTime(et), fee(f),
		startID(-1), endID(-1) {
		strcpy(id, i);
		strcpy(start, s);
		strcpy(end, e);
	}
};

int time(int h, int m) {
	return h * 60 + m;
}

Flight flights[N] = {
	Flight( "6320" , "北京"     , "上海"     , time(16, 20) , time(17, 25) , 680  ),
	Flight( "6320" , "上海"     , "北京"     , time(18, 0 ) , time(19, 5 ) , 680  ),
	Flight( "2104" , "北京"     , "乌鲁木齐" , time(8 , 0 ) , time(9 , 55) , 1150 ),
	Flight( "2104" , "乌鲁木齐" , "北京"     , time(10, 45) , time(11, 40) , 1150 ),
	Flight( "201"  , "北京"     , "西安"     , time(15, 25) , time(17, 0 ) , 930  ),
	Flight( "201"  , "西安"     , "北京"     , time(12, 35) , time(14, 15) , 930  ),
	Flight( "2323" , "西安"     , "广州"     , time(7 , 15) , time(9 , 35) , 1320 ),
	Flight( "2323" , "广州"     , "西安"     , time(10, 15) , time(11, 35) , 1320 ),
	Flight( "173"  , "拉萨"     , "昆明"     , time(10, 20) , time(11, 45) , 830  ),
	Flight( "173"  , "昆明"     , "拉萨"     , time(12, 35) , time(14, 0 ) , 830  ),
	Flight( "3304" , "拉萨"     , "武汉"     , time(14, 15) , time(15, 45) , 890  ),
	Flight( "3304" , "武汉"     , "拉萨"     , time(16, 25) , time(17, 55) , 890  ),
	Flight( "82"   , "乌鲁木齐" , "昆明"     , time(9 , 30) , time(12, 15) , 1480 ),
	Flight( "82"   , "昆明"     , "乌鲁木齐" , time(13, 5 ) , time(15, 50) , 1480 ),
	Flight( "4723" , "武汉"     , "广州"     , time(7 , 5 ) , time(8 , 45) , 810  ),
	Flight( "4723" , "广州"     , "武汉"     , time(11, 25) , time(13, 5 ) , 810  )
};

/*
 * Variables
 *
 */

HashMap<const char *, int> map(hashf, equalf);
char cityID[N][30];

char startCity[30], endCity[30];
int method; // 0: min time; 1: min fee; 2: min trans

ChainList<int> G[N];
int m = 0;

int d[N];
int path[N];
MinHeap<pair<int, int> > heap;

/*
 * Functions
 *
 */

// Map Chinese City to ID Number
void mapCities() {
	for (int i = 0, j = 0; i < N; ++i) {
		if (map.insert(flights[i].start, j)) {
			strcpy(cityID[j], flights[i].start);
			++j;
		}
		if (map.insert(flights[i].end, j)) {
			strcpy(cityID[j], flights[i].end);
			++j;
		}
	}

	for (int i = 0, j = 0; i < N; ++i) {
		flights[i].startID = *map.find(flights[i].start);
		flights[i].endID = *map.find(flights[i].end);
	}
}

// Build Graph
void buildGraph() {
	for (int i = 0; i < N; ++i) {
		G[flights[i].startID].insert(i);
	}
}

// foreach
bool each(int &i) {
	Flight flight = flights[i];
	int u = flight.startID;
	int v = flight.endID;
	//cout << flight.start << " " << flight.end << endl;
	switch (method) {
		case 0:
			{
				if (d[v] == -1 || d[v] > d[u] + flight.endTime - flight.startTime) {
					d[v] = d[u] + flight.endTime - flight.startTime;
					path[v] = u;
					heap.insert(make_pair(d[v], v));
				}
			}
			break;
		case 1:
			{
				if (d[v] == -1 || d[v] > d[u] + flight.fee) {
					d[v] = d[u] + flight.fee;
					path[v] = u;
					heap.insert(make_pair(d[v], v));
				}
			}
			break;
		case 2:
			{
				if (d[v] == -1 || d[v] > d[u] + 1) {
					d[v] = d[u] + 1;
					path[v] = u;
					heap.insert(make_pair(d[v], v));
				}
			}
			break;
	}
	
	return false;
}

// ShortestPath
void Dijkstra(int start) {
	for (int i = 0; i < N; ++i) path[i] = d[i] = -1;
	d[start] = 0;
	heap.empty();
	heap.insert(make_pair(d[start], start));
	while (!heap.isEmpty()) {
		pair<int, int> p;
		heap.removeMin(p);
		try {
			G[p.second].foreach(each);
		} catch (const char *e) {
			cout << e <<endl;
		}
	}
}

int main()
{
	mapCities();
	//map.dfs();
	buildGraph();

	while (1) {
		cout << "请输入始发地：" << endl;
		cin >> startCity;
		cout << "请输入目的地：" << endl;
		cin >> endCity;
		cout << "请输入计算方式：\n\t0) 飞行时间最短\n\t1) 费用最少\n\t2) 中转次数最少" << endl;
		cin >> method;
		int *start = map.find(startCity);
		int *end = map.find(endCity);

		if (!start || !end) {
			cout << "没有找到城市" << endl;
			continue;
		}

		Dijkstra(*start);
		switch (method) {
			case 0:
				{
					int timeAmount = d[*end]; 
					cout << timeAmount / 60 << "小时" << timeAmount % 60 << "分钟" << endl;
				}
				break;
			case 1:
				cout << d[*end] << "元" << endl;
				break;
			case 2:
				cout << d[*end] << "次" << endl;
				break;
		}
		int p = path[*end];
		cout << endCity << endl;
		while (p != -1) {
			cout << cityID[p] << endl;
			p = path[p];
		}

	}

	return 0;
}
