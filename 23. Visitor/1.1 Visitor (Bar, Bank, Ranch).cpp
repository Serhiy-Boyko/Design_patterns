#include <iostream>
#include <string>

class Bar;
class Bank;
class Ranch;

// Абстракція відвідувача
class Visitor {
protected:
	int money;
public:
	virtual int visit(Bar &ref) = 0;
	virtual int visit(Bank &ref) = 0;
	virtual int visit(Ranch &ref) = 0;
};

// Елементи
class Location {
protected:
	int money;
public:
	Location(int m) : money(m) {}
	virtual void accept(Visitor &v) = 0;
	virtual void PrintMoney() = 0;
};

// Конкретні елементи
class Bar : public Location {
public:
	Bar(int m) : Location(m) {}

	void accept(Visitor &v) { 
		std::cout << "   Bar: ";
		money += v.visit(*this);
	}
	void PrintMoney() { std::cout << "  Bar money: " << money << std::endl; }
};

class Bank : public Location {
public:
	Bank(int m) : Location(m) {}

	void accept(Visitor &v) { 
		std::cout << "  Bank: ";
		money += v.visit(*this);
	}
	// Пограбування
	int Rob() {
		int m = money;
		money = 0;
		return m;
	}

	void PrintMoney() { std::cout << " Bank money: " << money << std::endl; }
};

class Ranch : public Location {
public:
	Ranch(int m) : Location(m) {}

	void accept(Visitor &v) { 
		std::cout << " Ranch: ";
		money += v.visit(*this);
	}

	void PrintMoney() { std::cout << "Ranch money: " << money << std::endl; }
};

// Конкретний відвідувач
class Cowboy : public Visitor {
public:
	int visit(Bar &ref) {
		std::cout << "Всiм привiт. Офiцiант, вiскi!" << std::endl;
		money -= 2;
		return 2;
	}
	int visit(Bank &ref) {
		std::cout << "Доброго дня. Я хочу покласти грошi на депозит.\n";
		money /= 2;
		return money;
	}
	int visit(Ranch &ref) {
		std::cout << "Привiт, мiй дiм." << std::endl;
		return 0;
	}
};

class Robber : public Visitor {
public:
	int visit(Bar &ref) {
		std::cout << "Офiцiант, пива!" << std::endl;
		money -= 1;
		return 1;
	}
	int visit(Bank &ref) {
		std::cout << "Це пограбування! Грошi на стiл!" << std::endl;
		money += ref.Rob();
		return 0;
	}
	int visit(Ranch &ref) {
		std::cout << "Де господар? Я хочу купити коня!" << std::endl;
		money -= 50;
		return 50;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	Bar bar(300);
	Bank bank(3400);
	Ranch ranch(210);
	Location *location[] = { &bar, &bank, &ranch };	
	for (auto elem : location)
		elem->PrintMoney();

	Cowboy cowboy;
	std::cout << "----------------------------------" << std::endl;
	std::cout << " Ковбой " << std::endl;
	for (auto elem : location)
		elem->accept(cowboy);
	std::cout << "----------------------------------" << std::endl;
	Robber robber;
	std::cout << " Грабiжник " << std::endl;
	for (auto elem : location)
		elem->accept(robber);
	std::cout << "----------------------------------" << std::endl;
	for (auto elem : location)
		elem->PrintMoney();
	system("Pause");
	return 0;
}