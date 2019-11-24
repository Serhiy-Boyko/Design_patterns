#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

class Base {
	Base *next; // 1. Вказівник "next" у базовому класі
public:
	Base() : next(nullptr) {}

	// приєднуємо наступну обробку тут або передаємо далі
	void setNext(Base *n) { next ? next->setNext(n) : next = n; }

	// 2. Метод базового класа, що делегує запит next-об'єкту
	virtual void handle(int c) { next->handle(c); }
	// c - рівень складності проблеми
};

class Operator : public Base {
	string name;
public:
	Operator(string n) : name(n) {}

	/*virtual*/ void handle(int c) {
		cout << " Operator " << name << ": Can I help You ? " << endl;
		if (c < 8) // якщо проблема проста, вирішуємо тут
			cout << " Operator " << name << ": Problem " << c << " is solved ! " << endl;
		else {// якщо надто складно, передаємо виклик спеціалісту
			cout << " Operator " << name << ": Please, wait connection with specialist" << endl;
			Base::handle(c); // 3. делегуємо виклик базовому класу
		}
	}
};

class Specialist : public Base {
public:
	/*virtual*/ void handle(int c) {
		cout << " Specialist: Can I help You ? " << endl;
		cout << " Specialist: Problem " << c << " is solved ! " << endl;
	}
};

class Commutator : public Base {
	vector <Operator*> Operators;
public:
	void add(Operator *o) { Operators.push_back(o); }

	void setNext(Base *n) { for (auto it : Operators) it->setNext(n); }

	/*virtual*/ void handle(int c) {
		cout << " Commutator: please, wait connection with operator" << endl;
		int cnt = Operators.size(); // к-ть операторів
		switch (cnt) {
		case 0: cout << " Commutator: sorry, no one of free operator" << endl; break;
		case 1:	cout << " Your call will be save " << endl;
			Operators[0]->handle(c);//3. делегуємо виклик базовому класу
			break;
		default:
			cout << " Your call will be save " << endl;
			Operators[rand() % cnt]->handle(c);//3. делегуємо виклик базовому класу
		}
	}
};

void main()
{
	srand(time(0));
	Commutator c;
	c.add(new Operator("Oleg"));
	c.add(new Operator("Ira"));
	c.add(new Operator("Misha"));
	c.setNext(new Specialist);
	for (int i = 1; i < 10; i++) {
		c.handle(rand() % 10);
		cout << endl;
	}
}