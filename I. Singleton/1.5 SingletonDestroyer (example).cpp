#include <iostream>
#include <fstream>
using namespace std;

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
	Singleton() {
		ofstream Logfile("Logfile.txt", ios::app);
		Logfile << endl << "create Singleton " << endl;
		Logfile.close();
	}
	Singleton(const Singleton&);
	Singleton &operator=(Singleton&);
	~Singleton() {
		ofstream Logfile("Logfile.txt", ios::app);
		Logfile << "delete Singleton " << endl;
		Logfile.close();
	}
public:
	static Singleton &getInstance() {
		if (!p_instance) {
			p_instance = new Singleton();
			destroyer.initialize(p_instance);
		}
		return *p_instance;
	}

	void working() {
		ofstream Logfile("Logfile.txt", ios::app);
		Logfile << " working... " << endl;
		Logfile.close();
	}

	friend class SingletonDestroyer;
};

Singleton *Singleton::p_instance = 0;
SingletonDestroyer Singleton::destroyer;

// якщо не винести вниз, то не спрацює
SingletonDestroyer::~SingletonDestroyer() {
	delete p_instance;
}
/* при завершенні програми автоматично буде викликаний
деструктор ~SingletonDestroyer(), який знищить Singleton */

void main() {
	Singleton *p = &Singleton::getInstance();
	p->working();
	p->working();
	system("pause");
}