#include <iostream>
#include <vector>
#include <string>
#include <time.h>

class Warrior {
protected:
	int hp;
public:
	Warrior() : hp(0) {}
	virtual void Info() = 0;
};

class Infantryman : public Warrior {
public:
	Infantryman() { hp = 15; }
	virtual void Info() { 
		std::cout << " Infantryman hitpoints:\t" << hp << std::endl;
	}
};

class Archer : public Warrior {
public:
	Archer() { hp = 12; }
	virtual void Info() { 
		std::cout << " Archer hitpoints:\t" << hp << std::endl; 
	}
};

class Veles : public Warrior {
public:
	Veles() { hp = 13; }
	virtual void Info() { 
		std::cout << " Veles hitpoints:\t" << hp << std::endl; 
	}
};

class Horseman : public Warrior {
public:
	Horseman() { hp = 25; }
	virtual void Info() { 
		std::cout << " Horseman hitpoints:\t" << hp << std::endl; 
	}
};

// Абстрактний клас "Армія", що складається з усіх типів вояків
class Army {
protected:
	std::vector<Infantryman> gi; // Group of Infantrymans
	std::vector<Archer> ga;
	std::vector<Veles> gv;
	std::vector<Horseman> gh;
	std::string nation;
public:
	Army(std::string n) : nation(n) {}
	virtual void Info() = 0;

	friend class RomanFactory;
	friend class CarthaginianFactory;
};

/* Клас "Римська армія", що містить лише вояків-римлян.
Наповнення армії залежить від фабрики,
яка викликається у конструкторі - це зручно */
class RomanArmy : public Army {
public:
	RomanArmy(std::string n) : Army(n) {}
	virtual void Info() {
		std::cout << nation << " Army " << std::endl;
		std::cout << " Infantry: " << gi.size() << std::endl;
		std::cout << "  Velites: " << gv.size() << std::endl;
		std::cout << "  Cavalry: " << gh.size() << std::endl;
	}
};

class CarthaginianArmy : public Army {
public:
	CarthaginianArmy(std::string n) : Army(n) {}
	virtual void Info() {
		std::cout << nation << " Army " << std::endl;
		std::cout << " Infantry: " << gi.size() << std::endl;
		std::cout << "  Archers: " << ga.size() << std::endl;
		std::cout << "  Cavalry: " << gh.size() << std::endl;
	}
};

/* class Factory (pattern Factory)- окремий клас
для створення об'єктів дочірніх класів від деякого базового */

class Factory {
protected:
	Army *p;
public:
	Factory() : p(nullptr) {}
	virtual Army *createArmy() = 0;
	~Factory() { delete p; }
};

class RomanFactory : public Factory {
public:
	virtual Army *createArmy() {
		p = new RomanArmy("Roman");
		for (int i = 1; i <= 300; i++)
			p->gi.push_back(Infantryman());
		for (int i = 1; i <= 150; i++)
			p->gv.push_back(Veles());
		for (int i = 1; i <= 30; i++)
			p->gh.push_back(Horseman());
		return p;
	}
};

class CarthaginianFactory : public Factory {
public:
	virtual Army *createArmy() {
		p = new CarthaginianArmy("Carthaginian");
		for (int i = 1; i <= 320; i++)
			p->gi.push_back(Infantryman());
		for (int i = 1; i <= 120; i++)
			p->ga.push_back(Archer());
		for (int i = 1; i <= 40; i++)
			p->gh.push_back(Horseman());
		return p;
	}
};

int main()
{
	srand(time(0));
	// створення фабрик для кожної з армій
	RomanFactory rFactory;
	CarthaginianFactory cFactory;

	// створення армій
	Army *RA = rFactory.createArmy();
	Army *CA = cFactory.createArmy();

	// робота з об'єктами
	RA->Info();
	CA->Info();

	system("Pause");
	return 0;
}