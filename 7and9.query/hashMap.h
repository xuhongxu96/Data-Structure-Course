#pragma once
#include <iostream>

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE  20
#endif

/*
 *
 * updated:
 * dfs returns Count of Elemetns.
 *
 * 本宝宝 的『散列表的散列表』
 * 结合 开散列方法 和 双散列法
 * 不断跳、跳、跳！
 *
 * By: xuhongxu.cn
 * 2015.12.17
 *
 */

int val(const int *p) {
	if (p) return *p;
	return -1;
}

int hashf(const char *const &k, int d) {
	int ret = 0;
	for (int i = 0; k[i]; ++i) {
		if (k[i] < 0) ret += -k[i] % d;
		else ret += k[i] % d;
		ret <<= d;
	}
	if (ret < 0) ret = -ret;
	return ret % d;
}

bool equalf(const char *const &k, const char *const &k2) {
	return strcmp(k, k2) == 0;
}


template <class E, class K>
class HashMap {
public:
	typedef int (*Hash)(const E &k, int d);
	typedef bool (*Equal)(const E &k, const E &k2);
	HashMap(Hash hashFunc, Equal equalFunc, int d = 19, int sz = DEFAULT_SIZE) 
		: divitor(d), size(sz), length(0),
		  table(NULL), isValue(false),
		  hashf(hashFunc), equalf(equalFunc) {
			  table = new HashMap<E, K>*[sz];
			  memset(table, 0, sz * sizeof(HashMap<E, K> *));
		  }
	~HashMap() {
		if (!table) delete [] table;
	}
	K *find(const E &k) {
		if (isValue && equalf(key, k)) {
			return &value;
		}
		int i = hashf(k, divitor);
		if (i >= size) return NULL;
		if (table[i])
			return table[i]->find(k);
		return NULL;
	}
	bool insert(const E &k, const K &v) {
		int i = hashf(k, divitor);
		if (find(k)) return false;
		if (i >= size) return false;
		//std::cout << i << std::endl;
		if (table[i]) {
			if (table[i]->isValue) {
				// Value
				table[i]->isValue = false;
				bool ret = table[i]->insert(table[i]->key, table[i]->value);
				ret &= table[i]->insert(k, v);
				return ret;
			} else {
				// HashMap
				return table[i]->insert(k, v);
			}
		} else {
			// NULL
			table[i] = new HashMap<E, K>(hashf, equalf, divitor - 1, size);
			table[i]->isValue = true;
			table[i]->key = k;
			table[i]->value = v;
		}
		return true;
	}
	int dfs(int level = 0) {
		if (isValue) {
			std::cout << "level: " << level << " -- "<< key << ": " << value << std::endl;
			return 1;
		}
		int t = 0;
		for (int i = 0; i < size; ++i) {
			if (table[i]) {
				std::cout << "level " <<level<< ", enter "<< i << std::endl;
				t += table[i]->dfs(level + 1);
			}
		}
		return t;
	}
protected:
	int divitor;
	int size;
	int length;
	Hash hashf;
	Equal equalf;
	HashMap<E, K> **table;
	bool isValue;
	E key;
	K value;
};
