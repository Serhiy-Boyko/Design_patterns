#include <iostream>
#include <vector>
#include <ctime>
#include <string>

class Base {
	Base *next; // 1. Вказівник "next" у базовому класі
public:
	Base() : next(nullptr) {}

	// приєднуємо наступну обробку тут або передаємо далі
	void setNext(Base *n) { 
		if (next)
			next->setNext(n);
		else
			next = n; 
	}

	// 2. Метод базового класа, що делегує запит next-об'єкту
	// c - рівень складності проблеми
	virtual void handle(int c) { next->handle(c); }	
};

class Employee : public Base {
protected:
	std::string name;
public:
	Employee(std::string n) : name(n) {}
	virtual void handle(int c) = 0;
};

class Operator : public Employee {
public:
	Operator(std::string n) : Employee(n) {}

	virtual void handle(int c) {
		std::cout << " Operator " << name << ": Can I help You ? " << std::endl;
		std::cout << " Client: My problem is " << c << "." << std::endl;
		if (c < 8) // якщо проблема проста, вирішуємо тут
			std::cout << " Operator " << name << ": Problem " << c << " is solved! \n";
		else {// якщо надто складно, передаємо виклик спеціалісту
			std::cout << " Operator " << name;
			std::cout << ": Please, wait connection with specialist" << std::endl;
			Base::handle(c); // 3. делегуємо виклик базовому класу
		}
	}
};

class Specialist : public Employee {
public:
	Specialist(std::string n) : Employee(n) {}

	virtual void handle(int c) {
		std::cout << " Specialist " << name << ": Can I help You ? " << std::endl;
		std::cout << " Client: My problem is " << c << "." << std::endl;
		std::cout << " Specialist " << name << ": Problem " << c << " is solved! \n";
	}
};

class Commutator : public Base {
	std::string employee;
	std::vector <Employee*> Employees;
public:
	Commutator(std::string emp) : employee(emp) {}
	void add(Employee *emp) { Employees.push_back(emp); }

	void setNext(Base *n) { for (auto it : Employees) it->setNext(n); }

	virtual void handle(int c) {
		std::cout << " Commutator: Please, wait connection with ";
		std::cout << employee << std::endl;
		int cnt = Employees.size(); // к-ть операторів
		switch (cnt) {
		case 0: std::cout << " Commutator: Sorry, no one of free " << employee << '\n';
			break;
		case 1:	std::cout << " Your call will be save " << std::endl;
			Employees[0]->handle(c);//3. делегуємо виклик базовому класу
			break;
		default:
			std::cout << " Your call will be save " << std::endl;
			Employees[rand() % cnt]->handle(c);//3. делегуємо виклик базовому класу
		}
	}
};

int main()
{
	srand(time(0));
	Commutator comOperators("operator");
	comOperators.add(new Operator("Oleg"));
	comOperators.add(new Operator("Ira"));
	comOperators.add(new Operator("Misha"));
	Commutator *comSpecialists = new Commutator("specialist");
	comSpecialists->add(new Specialist("Alex"));
	comSpecialists->add(new Specialist("Ruslan"));
	comOperators.setNext(comSpecialists);
	for (int i = 1; i < 10; i++) {
		comOperators.handle(rand() % 10);
		std::cout << std::endl;
	}
	system("Pause");
	return 0;
}