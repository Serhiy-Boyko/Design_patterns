#include <iostream>

class Singleton;  // опережающее объявление (декларація класу)

class SingletonDestroyer {
	Singleton *p_instance;
public:
	void initialize(Singleton* p) { p_instance = p; }
	~SingletonDestroyer();
};

class Singleton {
	static Singleton *p_instance;
	static SingletonDestroyer destroyer;
protected:
	Singleton() {}
	Singleton(const Singleton&);
	Singleton &operator=(Singleton&);
	~Singleton() {}
public:
	static Singleton &getInstance() {
		if (!p_instance) {
			p_instance = new Singleton();
			destroyer.initialize(p_instance);
		}
		return *p_instance;
	}

	friend class SingletonDestroyer;
};

Singleton *Singleton::p_instance = nullptr;
SingletonDestroyer Singleton::destroyer;

// якщо не винести вниз, то не спрацює
SingletonDestroyer::~SingletonDestroyer() {
	delete p_instance; // delete Singleton
}
/* при завершенні програми автоматично буде викликаний
деструктор ~SingletonDestroyer(), який знищить Singleton */

void main() {
	Singleton *p = &Singleton::getInstance();
	system("pause");
}