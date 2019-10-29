#include <iostream>
#include <fstream>

class Singleton;

class SingletonDestroyer {
	Singleton *p_instance;
public:
	void initialize(Singleton* p) { p_instance = p; }
	~SingletonDestroyer();
};

class Singleton {
	static Singleton *p_instance;
	static SingletonDestroyer destroyer;
	static std::ofstream Logfile;
protected:
	Singleton() {
		Logfile << "create Singleton " << std::endl;
	}
	Singleton(const Singleton&) = delete;
	Singleton &operator=(Singleton&) = delete;
	~Singleton() {
		Logfile << "delete Singleton " << std::endl;
		Logfile << "==================" << std::endl;
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

	void working() { Logfile << " working... " << std::endl; }

	friend class SingletonDestroyer;
};

std::ofstream Singleton::Logfile("Logfile.txt", std::ios::app);
Singleton *Singleton::p_instance = nullptr;
SingletonDestroyer Singleton::destroyer;

SingletonDestroyer::~SingletonDestroyer() {
	delete p_instance;
}

int main() {
	Singleton *p = &Singleton::getInstance();
	p->working();
	p->working();
	system("pause");
	return 0;
}