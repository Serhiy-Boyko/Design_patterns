#include <iostream>

/* дана конструкція гарантує, що перед створенням
Singleton2 буде створено Singleton1 */
class Singleton1 {
	Singleton1() { }
	Singleton1(const Singleton1&);
	Singleton1& operator=(Singleton1&);
public:
	static Singleton1& getInstance() {
		static Singleton1 instance;
		std::cout << " create Singleton 1 " << std::endl;
		return instance;
	}
};

class Singleton2 {
	Singleton2(Singleton1& instance) : s1(instance) { }
	Singleton2(const Singleton2&);
	Singleton2& operator=(Singleton2&);
	Singleton1& s1;
public:
	static Singleton2& getInstance() {
		static Singleton2 instance(Singleton1::getInstance());
		std::cout << " create Singleton 2 " << std::endl;
		return instance;
	}
};

int main() {
	Singleton2 &s = Singleton2::getInstance();
	system("pause");
	return 0;
}