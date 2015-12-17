#include <iostream>
#include <cstring>
using namespace std;

const int N = 16;

struct Flight {
	char id[10], start[20], end[20];
	int startTime, endTime;
	int fee;
	Flight(
			const char *i,
			const char *s, 
			const char *e, 
			int st,
			int et,
			int f
			) : startTime(st), endTime(et), fee(f) {
		strcpy(id, i);
		strcpy(start, s);
		strcpy(end, e);
	}
};

int time(int m, int s) {
	return m * 24 + s;
}

const Flight flights[N] = {
	Flight( "6320" , "北京"     , "上海"     , time(16, 20) , time(17, 25) , 680  ),
	Flight( "6320" , "上海"     , "北京"     , time(18, 0 ) , time(19, 5 ) , 680  ),
	Flight( "2104" , "乌鲁木齐" , "北京"     , time(8 , 0 ) , time(9 , 55) , 1150 ),
	Flight( "2104" , "北京"     , "乌鲁木齐" , time(10, 45) , time(11, 40) , 1150 ),
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

const char *cities[] = {"北京", "上海", "乌鲁木齐", "拉萨", "广州", "西安", "昆明", "武汉"};

int main() {
	return 0;
}
