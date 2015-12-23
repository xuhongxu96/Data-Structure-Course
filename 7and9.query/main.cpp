#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "SeqList.h"
#include "hashMap.h"
using namespace std;

const int MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct AirQuality {
	char id[10];
	char city[30];
	char pollution[50];
	int aqi;
	char level[10];
	char state[30];
	int year, month, date;
	AirQuality(char *i, char *c,char *p, int a, char *l, char *s, int y, int m, int d) {
		aqi = a;
		year = y;
		month = m;
		date = d;
		strcpy(id, i);
		strcpy(city, c);
		strcpy(pollution, p);
		strcpy(level, l);
		strcpy(state, s);
	}
	AirQuality() : aqi(0), year(0), month(0), date(0) {
		id[0] = city[0] = pollution[0] = level[0] = state[0] = '\0';
	}
	friend ostream &operator <<(ostream &o, AirQuality q) {
		o << q.id << " " << q.city << " " << q.pollution << " " << q.aqi << " " << q.level << " ";
		o << q.state << " " << q.year << " " << q.month << " " << q.date << endl;
		return o;
	}
	friend istream &operator >>(istream &in, AirQuality &q) {
		in >> q.id >> q.city >> q.pollution >> q.aqi >> q.level;
		in >> q.state >> q.year >> q.month >> q.date;
		return in;
	}
};

SeqList<AirQuality> qualities;

struct RecordPointer {
	int start, end;
	RecordPointer(int s, int e) : start(s), end(e) {}
	RecordPointer() : start(-1), end(0) {}
	friend ostream &operator <<(ostream &o, RecordPointer rp) {
		for (int i = rp.start; i <= rp.end; ++i) {
			cout << qualities[i];
		}
		return o;
	}
};

HashMap<const char *, RecordPointer> map(hashf, equalf, 131, 300);
HashMap<const char *, RecordPointer> mapById(hashf, equalf, 131, 300);
int N = 0;



void inputData() {
	AirQuality quality;
	fstream fs("data.txt", fstream::in);

	while (fs >> quality) {
		qualities.insert(quality);
	}

	N = qualities.getLength();
}

void mapCities() {

	char *lastCity = qualities[0].city;
	char *lastId = qualities[0].id;
	int start = 0;
	int j  = 0;
	for (int i = 1; i < N; ++i) {
		if (strcmp(lastCity, qualities[i].city) != 0) {
			//cout << ++j << ", "<< lastCity << endl;
			map.insert(lastCity, RecordPointer(start, i - 1));
			mapById.insert(lastId, RecordPointer(start, i - 1));
			start = i;
			lastCity = qualities[i].city;
			lastId = qualities[i].id;
		}
	}
	map.insert(lastCity, RecordPointer(start, N - 1));
	mapById.insert(lastId, RecordPointer(start, N - 1));
	//cout << ++j << ", "<< lastCity << endl;

	//cout << map.dfs() << endl;
	//cout << mapById.dfs() << endl;
}

bool findItem(int left, int right, int year, int month, int date, int &index, SeqList<AirQuality> *list) {
	if (!list) list = &qualities;
	int l = left, r = right + 1;
	//cout << year << ", " << month << ", " << date <<  endl;
	while (l < r) {
		int mid = (l + r) >> 1;
		AirQuality q = (*list)[mid];
		//cout << mid << " "<< q << endl;
		if (q.year < year 
				|| (q.year == year && (q.month < month 
						|| (q.month == month && q.date < date)))) {
			r = mid;
		} else if (q.year > year 
				|| (q.year == year && (q.month > month 
						|| (q.month == month && q.date > date)))) {
			l = mid + 1;
		} else {
			index = mid;
			return true;
		}
	}
	index = l;
	return false;
}

RecordPointer findItemsByDate(int left, int right, int year, int month = 0, int date = 0, SeqList<AirQuality> *list = NULL) {
	int s, t;
	if (month && date) {
		if (findItem(left, right, year, month, date, s, list)) {
			t = s;
		} else {
			s = 0; t = -1;
			cout << "未检索到此天记录！" << endl;
		}
	} else if (month && !date) {
		findItem(left, right, year, month, 1, t, list);
		findItem(left, right, year, month, 31, s, list);
	} else {
		findItem(left, right, year, 1, 1, t, list);
		findItem(left, right, year, 12, 31, s, list);
	}
	return RecordPointer(s, t);
}

RecordPointer findItemsBySeason(int left, int right, int year, int season, SeqList<AirQuality> *list = NULL) {
	// season 1: 1 - 3; season 2: 4 - 6; season 3: 7 - 9; season 4: 10 - 12
	int s, t;
	int monthStart = season * 3 - 2;
	int monthEnd = season * 3;
	findItem(left, right, year, monthStart, 1, t, list);
	findItem(left, right, year, monthEnd, 31, s, list);
	return RecordPointer(s, t);
}

bool isLeap(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int date2month(int &date, int year = 1) {
	for (int i = 0; i < 12; ++i) {
		if (i == 1 && isLeap(year)) date--;
		date -= MONTH[i];
		if (date < 0) {
			date += MONTH[i];
			return i + 1;
		}
	}
	date += MONTH[11];
	return 12;
}

RecordPointer findItemsByWeek(int left, int right, int year, int week, int month = 0, SeqList<AirQuality> *list = NULL) {
	int s, t;
	if (month) {
		findItem(left, right, year, month, week * 7 - 6, t, list);
		findItem(left, right, year, month, week * 7, s, list);
	} else {
		int dateStart = week * 7 - 6;
		int monthStart = date2month(dateStart);
		int dateEnd = week * 7;
		int monthEnd = date2month(dateEnd);
		findItem(left, right, year, monthStart, dateStart, t, list);
		findItem(left, right, year, monthEnd, dateEnd, s, list);
	}
	return RecordPointer(s, t);
}

RecordPointer getCity() {
	char city[30];
	cout << "请输入城市名称：" << endl;
	cin >> city;
	RecordPointer *rp = NULL;
	if (city[0] >= '0' && city[0] <= '9') {
		rp = mapById.find(city);
	} else {
		rp = map.find(city);
	}
	if (!rp) {
		cout << "未检索到城市！" << endl;
		return RecordPointer(0, -1);
	}
	return *rp;
}

RecordPointer getRange(RecordPointer rp, SeqList<AirQuality> *list = NULL) {
	int method;
	cout << "请选择检索方式：\n\t1) 日期\n\t2) 季度\n\t3) 周数" << endl;
	cin >> method;

	RecordPointer range;
	switch (method) {
	case 1:
		{
			int y, m = 0, d = 0;
			cout << "请输入年份：" << endl;
			cin >> y;
			cout << "请输入月份（全部则填0）：" << endl;
			cin >> m;
			if (m) {
				cout << "请输入日期（全部则填0）：" << endl;
				cin >> d;
			}
			range = findItemsByDate(rp.start, rp.end, y, m, d, list);
		}
		break;
	case 2:
		{
			int y, s;
			cout << "请输入年份：" << endl;
			cin >> y;
			cout << "请输入季度：" << endl;
			cin >> s;
			range = findItemsBySeason(rp.start, rp.end, y, s, list);
		}
		break;
	case 3:
			int y, m, w;
			cout << "请输入年份：" << endl;
			cin >> y;
			cout << "请输入月份（填0则按年算）：" << endl;
			cin >> m;
			cout << "请输入周数：" << endl;
			cin >> w;
			range = findItemsByWeek(rp.start, rp.end, y, w, m, list);
		break;
	}
	return range;
}

void searchFunc() {
	RecordPointer rp = getCity();
	cout << getRange(rp);
}

bool cmpByDate(const AirQuality &a, const AirQuality &b) {
	if (a.year > b.year) return true;
	if (a.year < b.year) return false;
	if (a.month > b.month) return true;
	if (a.month < b.month) return false;
	if (a.date > b.date) return true;
	return false;
}
bool cmpByAqi(const AirQuality &a, const AirQuality &b) {
	return a.aqi < b.aqi;
}

void sortFunc() {
	SeqList<AirQuality> qualities_bk(qualities);
	qualities_bk.sort(cmpByDate);
	RecordPointer rp = getRange(RecordPointer(0, N - 1), &qualities_bk);
	//cout << rp.start << " " << rp.end << endl;
	qualities_bk.sort(cmpByAqi, rp.start, rp.end + 1);

	cout << "榜单显示数量（输入0默认为20）：" << endl;
	int ct;
	cin >> ct;
	if (ct == 0) ct = 20;
	for (int i = rp.start; i <= min(rp.end, rp.start + ct - 1); ++i)
		cout << qualities_bk[i];
}

void statFunc() {
	RecordPointer rp = getCity();
	RecordPointer range = getRange(rp);
	int ct[6];
	memset(ct, 0, sizeof(ct));
	for (int i = range.start; i <= range.end; ++i) {
		//cout << qualities[i].state;
		if (strcmp(qualities[i].state, "优") == 0) {
			++ct[0];
		} else if (strcmp(qualities[i].state, "良") == 0) {
			++ct[1];
		} else if (strcmp(qualities[i].state, "轻微污染") == 0) {
			++ct[2];
		} else if (strcmp(qualities[i].state, "轻度污染") == 0) {
			++ct[3];
		} else if (strcmp(qualities[i].state, "重污染") == 0) {
			++ct[4];
		} else if (strcmp(qualities[i].state, "中度重污染") == 0) {
			++ct[5];
		} 
	}
	cout << "优：" << ct[0] << "天" << endl;
	cout << "良：" << ct[1] << "天" << endl;
	cout << "轻微污染：" << ct[2] << "天" << endl;
	cout << "轻度污染：" << ct[3] << "天" << endl;
	cout << "重污染：" << ct[4] << "天" << endl;
	cout << "中度重污染：" << ct[5] << "天" << endl;
}

int main() {

	inputData();
	mapCities();

	while (1) {
		int method;
		cout << "请选择功能：\n\t1) 检索\n\t2) 统计\n\t3) 排序\n\t4) 退出" << endl;
		cin >> method;
		switch (method) {
		case 1:
			searchFunc();
			break;
		case 2:
			statFunc();
			break;
		case 3:
			sortFunc();
			break;
		case 4:
			return 0;
		}
	}
	return 0;

}
