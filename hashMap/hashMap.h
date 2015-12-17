#pragma once
#include <iostream>

using namespace std;
#define DEFAULT_SIZE 20

/*
 *
 * 本宝宝 的『散列表的散列表』
 * 结合 开散列方法 和 双散列法
 * 不断跳、跳、跳！
 *
 * By: xuhongxu.cn
 * 2015.12.17
 *
 */


template <class E, class K>
class HashMap {
public:
	typedef int (*Hash)(const E &k, int d);
	typedef bool (*Equal)(const E &k, const E &k2);
	HashMap(Hash hashFunc, Equal equalFunc, int d = 13, int sz = DEFAULT_SIZE) 
		: divitor(d), size(sz), length(0),
		  table(NULL), value(NULL), isValue(false),
		  key(NULL), hashf(hashFunc), equalf(equalFunc) {
			  table = new HashMap<E, K>*[sz];
			  memset(table, 0, sz * sizeof(HashMap<E, K> *));
		  }
	~HashMap() {
		if (!table) delete [] table;
	}
	K *find(const E &k) {
		int i = hashf(k, divitor);
		if (i >= size) return NULL;
		if (isValue && equalf(*key, k)) {
			return value;
		}
		if (table[i])
			return table[i]->find(k);
		return NULL;
	}
	bool insert(const E &k, const K &v) {
		int i = hashf(k, divitor);
		if (find(k)) return false;
		if (i >= size) return false;
		if (table[i]) {
			if (table[i]->isValue) {
				// Value
				table[i]->isValue = false;
				bool ret = table[i]->insert(*(table[i]->key), *(table[i]->value));
				table[i]->key = NULL;
				table[i]->value = NULL;
				return ret;
			} else {
				// HashMap
				return table[i]->insert(k, v);
			}
		} else {
			// NULL
			table[i] = new HashMap<E, K>(hashf, equalf, divitor - 1, size);
			table[i]->isValue = true;
			table[i]->key = const_cast<E*>(&k);
			table[i]->value = const_cast<K*>(&v);
		}
		return true;
	}
protected:
	int divitor;
	int size;
	int length;
	Hash hashf;
	Equal equalf;
	HashMap<E, K> **table;
	bool isValue;
	E *key;
	K *value;
};
