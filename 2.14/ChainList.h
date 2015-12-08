/*
 *
 * ChainNode
 *
 */
template <class T>
struct ChainNode {
	// value
	T val;
	// pointer to next element
	ChainNode *next;
	// constructor for no value;
	ChainNode(ChainNode *n = NULL) {
		next = n;
	}
	// constructor
	ChainNode(T v, ChainNode *n = NULL) {
		val = v;
		next = n;
	}
};

/*
 *
 * ChainList
 *
 */
template <class T>
class ChainList {
public:

	/*
	 * constructor
	 */
	ChainList() {
		head = new ChainNode<T>;
		tail = head;
		length = 0;
	}

	/*
	 * insert to the tail
	 */
	void insert(T v) {
		insert(length, v);
	}

	/*
	 * insert to the specific position
	 */
	void insert(int i, T v) {
		if (i == length) {
			tail->next = new ChainNode<T>(v);
			tail = tail->next;
		} else {
			ChainNode<T> *p = head;
			while (i--) {
				if (p == tail) {
					throw "out of bound";
				}
				p = p->next;
			}
			p->next = new ChainNode<T>(v, p->next);
		}
		++length;
	}

	/*
	 * output the elements
	 */
	void output() {
		for (ChainNode<T> *p = head->next; p != NULL; p = p->next) {
			std::cout << p->val << " ";
		}
	}

	/*
	 * empty the list
	 */
	void empty() {
		ChainNode<T> *p = head->next;
		while (p != NULL) {
			ChainNode<T> *q = p;
			p = p->next;
			delete q;
		}
		head->next = NULL;
	}

	/*
	 * locate the element
	 */
	ChainNode<T> *locate(int index) {
		if (index < 0) return NULL;
		ChainNode<T> *p = head->next;
		while (p != NULL && index--) {
			p = p->next;
		}
		if (index != -1) return NULL;
		return p;
	}

	/*
	 * find the max element
	 */
	T max() {
		ChainNode<T> *p = head->next;
		if (p == NULL) throw "no element";
		T m = p->val;
		p = p->next;
		while (p != NULL) {
			if (p->val > m) m = p->val;
			p = p->next;
		}
		return m;
	}

	/*
	 * count the element
	 */
	int number(T x) {
		ChainNode<T> *p = head->next;
		int res = 0;
		while (p != NULL) {
			if (p->val == x) ++res;
			p = p->next;
		}
		return res;
	}

	/* 
	 * create chainlist from a array
	 */
	void create(T *arr, int n) {
		for (int i = 0; i < n; ++i) {
			insert(arr[i]);
		}
	}

	/*
	 * make every element unique (increasing list)
	 */
	void tidyup() {
		ChainNode<T> *last = head;
		ChainNode<T> *p = head->next;
		while (p != NULL) {
			if (last != head && last->val == p->val) {
				last->next = p->next;
				--length;
				delete p;
				p = last->next;
			} else {
				last = p;
				p = p->next;
			}
		}
		tail = last;
	}

	/*
	 * free the memory
	 */
	~ChainList() {
		ChainNode<T> *p = head;
		while (p != NULL) {
			ChainNode<T> *q = p;
			p = p->next;
			delete q;
		}
	}
private:
	ChainNode<T> *head;
	ChainNode<T> *tail;
	int length;
};
