#include <iostream>
#include <time.h>
using namespace std;

template <class T>
class Vector {
	size_t count;
	size_t reserved_count;
	T *mas;

	void copy(int num = 0) {
		capacity += 10;
		T *arr = new T[capacity];
		for (int i = 0; i < size; i++)
			arr[i + num] = mas[i];
		delete[]mas;
		mas = arr;
	}
public:
	Vector() : count(0), reserved_count(0), mas(nullptr) {}
	~Vector() { delete[]mas; }

	void clear() { 
		delete[]mas; 
		mas = nullptr;
		count = 0; 
		reserved_count = 0;
	}

	void reserve(size_t cnt) { 
		delete[]mas;
		count = 0;
		reserved_count = cnt;
		mas = new T[reserved_count];		
	}
	
	void resize(size_t cnt) {
		size_t min = cnt > reserved_count ? reserved_count : cnt;
		reserved_count = cnt;
		T *arr = new T[reserved_count];
		for (int i = 0; i < min; i++)
			arr[i] = mas[i];
		delete[]mas;
		mas = arr;
	}

	size_t size() { return count; }
	size_t capacity() { return reserved_count; }

	void print() {
		if (!count)
			cout << " Vector is empty! ";
		else
			for (int i = 0; i < count; i++)
				cout << " " << mas[i];
		cout << endl;
	}

	void push_back(T elem) {
		if (count == reserved_count)
			resize(reserved_count + 10);
		mas[count++] = elem;
	}

	void pop_back() { count--; }

	class iterator {
		T *pos;
	public:
		iterator(T *p = nullptr) : pos(p) {}

		T &operator*() { return *pos; }

		iterator &operator++() {
			pos++;
			return *this;
		}

		iterator &operator++(int) {
			iterator tmp = *this;
			pos++;
			return tmp;
		}

		iterator &operator=(const iterator &A) {
			pos = A.pos;
			return *this;
		}

		friend bool operator!=(const iterator &A, const iterator &B) {
			return A.pos != B.pos;
		}
	};

	iterator begin() { return &mas[0]; }
	iterator end() { return &mas[count]; }
};

void main()
{
	srand(time(0));
	Vector<int> A;
	Vector<int>::iterator it;
	for (int i = 0; i < 10; i++)
		A.push_back(rand() % 10);
	cout << "     A.size: " << A.size() << endl;
	cout << " A.capacity: " << A.capacity() << endl;
	A.print();
	A.push_back(10);
	A.print();
	A.push_back(11);

	for (auto it : A)
		cout << " " << it;
	cout << endl;
	cout << "     A.size: " << A.size() << endl;
	cout << " A.capacity: " << A.capacity() << endl;

	system("pause");
}