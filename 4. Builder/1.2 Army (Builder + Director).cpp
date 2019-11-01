#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <Windows.h>

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
	std::string getNation() { return nation; }
	virtual void Info() = 0;

	friend class RomanBuilder;
	friend class CarthaginianBuilder;
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

/* class Builder (pattern Builder) - окремий клас
для створення деякого об'єкта покроково */

class Builder {
protected:
	Army *p;
public:
	Builder() : p(nullptr) {}
	virtual Army *createArmy() = 0;
	virtual void createInfantry() {}
	virtual void createVelites() {}
	virtual void createArchers() {}
	virtual void createCavalry() {}
	~Builder() { delete p; }
};

class RomanBuilder : public Builder {
public:
	virtual Army *createArmy() {
		p = new RomanArmy("Roman");
		return p;
	}
	virtual void createInfantry() {
		Sleep(400);
		std::cout << " Creating of Infantry" << std::endl;
		for (int i = 1; i <= 300; i++)
			p->gi.push_back(Infantryman());
	}
	virtual void createVelites() {
		Sleep(400);
		std::cout << " Creating of Velites" << std::endl;
		for (int i = 1; i <= 150; i++)
			p->gv.push_back(Veles());
	}
	virtual void createCavalry() {
		Sleep(400);
		std::cout << " Creating of Cavalry" << std::endl;
		for (int i = 1; i <= 30; i++)
			p->gh.push_back(Horseman());
	}
};

class CarthaginianBuilder : public Builder {
public:
	virtual Army *createArmy() {
		p = new CarthaginianArmy("Carthaginian");
		return p;
	}
	virtual void createInfantry() {
		Sleep(400);
		std::cout << " Creating of Infantry" << std::endl;
		for (int i = 1; i <= 320; i++)
			p->gi.push_back(Infantryman());
	}
	virtual void createArchers() {
		Sleep(400);
		std::cout << " Creating of Archers" << std::endl;
		for (int i = 1; i <= 120; i++)
			p->ga.push_back(Archer());
	}
	virtual void createCavalry() {
		Sleep(400);
		std::cout << " Creating of Cavalry" << std::endl;
		for (int i = 1; i <= 40; i++)
			p->gh.push_back(Horseman());
	}
};

/* class Director - окремий клас
для покрокової постановки задач будівельинкам */
class Director {
public:
	virtual Army *createArmy(Builder &fact) {
		Army *p = fact.createArmy();
		std::cout << " Creating of " << p->getNation();
		std::cout << " army " << std::endl;
		fact.createInfantry();		
		fact.createVelites();		
		fact.createArchers();		
		fact.createCavalry();
		Sleep(400);
		std::cout << std::endl;
		return p;
	}
};

int main()
{
	srand(time(0));
	// створення будівельників для кожної з армій
	RomanBuilder rBuilder;
	CarthaginianBuilder cBuilder;
	Director dir;

	// створення армій
	Army *RA = dir.createArmy(rBuilder);
	Army *CA = dir.createArmy(cBuilder);

	// робота з об'єктами
	RA->Info();
	CA->Info();

	system("Pause");
	return 0;
}