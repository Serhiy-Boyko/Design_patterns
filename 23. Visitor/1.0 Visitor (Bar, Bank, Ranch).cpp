#include <iostream>
#include <string>

class Bar;
class Bank;
class Ranch;

// Абстракція відвідувача
class Visitor {
public:
	virtual void visit(Bar &ref) = 0;
	virtual void visit(Bank &ref) = 0;
	virtual void visit(Ranch &ref) = 0;
};

// Елементи
class Location {
public:
	virtual void accept(Visitor &v) = 0;
};

// Конкретні елементи
class Bar : public Location {
public:
	void accept(Visitor &v) { 
		std::cout << "   Bar: ";
		v.visit(*this); 
	}
};

class Bank : public Location {
public:
	void accept(Visitor &v) { 
		std::cout << "  Bank: ";
		v.visit(*this); 
	}
};

class Ranch : public Location {
public:
	void accept(Visitor &v) { 
		std::cout << " Ranch: ";
		v.visit(*this); 
	}
};

// Конкретний відвідувач
class Cowboy : public Visitor {
public:
	void visit(Bar &ref) {
		std::cout << "Всiм привiт. Офiцiант, вiскi!" << std::endl;
	}
	void visit(Bank &ref) {
		std::cout << "Доброго дня. Я хочу покласти грошi на депозит.\n";
	}
	void visit(Ranch &ref) {
		std::cout << "Привiт, мiй дiм." << std::endl;
	}
};

class Robber : public Visitor {
public:
	void visit(Bar &ref) {
		std::cout << "Офiцiант, пива!" << std::endl;
	}
	void visit(Bank &ref) {
		std::cout << "Це пограбування! Грошi на стiл!" << std::endl;
	}
	void visit(Ranch &ref) {
		std::cout << "Де господар? Я хочу купити коня!" << std::endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	Bar bar;
	Bank bank;
	Ranch ranch;
	Location *location[] = { &bar, &bank, &ranch };
	Cowboy cowboy;
	std::cout << " Ковбой " << std::endl;
	for (auto elem : location)
		elem->accept(cowboy);
	std::cout << "----------------------------------" << std::endl;
	Robber robber;
	std::cout << " Грабiжник " << std::endl;
	for (auto elem : location)
		elem->accept(robber);

	system("Pause");
	return 0;
}