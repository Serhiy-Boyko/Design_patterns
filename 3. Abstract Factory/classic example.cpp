#include <iostream>
#include <cassert>
#include <vector>

// Абстрактные базовые классы всех возможных видов воинов
class Infantryman {
public:
	virtual void info() = 0;
};

class Archer {
public:
	virtual void info() = 0;
};

class Horseman {
public:
	virtual void info() = 0;
};


// Классы всех видов воинов Римской армии
class RomanInfantryman : public Infantryman {
public:
	void info() { std::cout << "Roman Infantryman" << std::endl; }
};

class RomanArcher : public Archer {
public:
	void info() { std::cout << "Roman Archer" << std::endl; }
};

class RomanHorseman : public Horseman {
public:
	void info() { std::cout << "Roman Horseman" << std::endl; }
};


// Классы всех видов воинов армии Карфагена
class CarthaginianInfantryman : public Infantryman {
public:
	void info() { std::cout << "Carthaginian Infantryman" << std::endl; }
};

class CarthaginianArcher : public Archer {
public:
	void info() { std::cout << "Carthaginian Archer" << std::endl; }
};

class CarthaginianHorseman : public Horseman {
public:
	void info() { std::cout << "Carthaginian Horseman" << std::endl; }
};


// Абстрактная фабрика для производства воинов
class ArmyFactory {
public:
	virtual Infantryman* createInfantryman() = 0;
	virtual Archer* createArcher() = 0;
	virtual Horseman* createHorseman() = 0;
	virtual ~ArmyFactory() {}
};


// Фабрика для создания воинов Римской армии
class RomanArmyFactory : public ArmyFactory
{
public:
	Infantryman* createInfantryman() {
		return new RomanInfantryman;
	}
	Archer* createArcher() {
		return new RomanArcher;
	}
	Horseman* createHorseman() {
		return new RomanHorseman;
	}
};

// Фабрика для создания воинов армии Карфагена
class CarthaginianArmyFactory : public ArmyFactory
{
public:
	Infantryman* createInfantryman() {
		return new CarthaginianInfantryman;
	}
	Archer* createArcher() {
		return new CarthaginianArcher;
	}
	Horseman* createHorseman() {
		return new CarthaginianHorseman;
	}
};

// Класс, содержащий всех воинов той или иной армии
class Army
{
	std::vector<Infantryman*> vi;
	std::vector<Archer*> va;
	std::vector<Horseman*> vh;
public:
	void info() {
		for (auto i : vi)  i->info();
		for (auto i : va)  i->info();
		for (auto i : vh)  i->info();
	}
	~Army() {
		for (int i = 0; i < vi.size(); i++)  delete vi[i];
		for (int i = 0; i < va.size(); i++)  delete va[i];
		for (int i = 0; i < vh.size(); i++)  delete vh[i];
	}

	friend class Game;
};

// Здесь создается армия той или иной стороны
class Game {
public:
	Army* createArmy(ArmyFactory& factory) {
		Army* p = new Army;
		p->vi.push_back(factory.createInfantryman());
		p->va.push_back(factory.createArcher());
		p->vh.push_back(factory.createHorseman());
		return p;
	}
};


int main()
{
	Game game;
	RomanArmyFactory ra_factory;
	CarthaginianArmyFactory ca_factory;

	Army *ra = game.createArmy(ra_factory);
	Army *ca = game.createArmy(ca_factory);
	std::cout << " Roman army:" << std::endl;
	ra->info();
	std::cout << std::endl << " Carthaginian army:" << std::endl;
	ca->info();
	system("Pause");
	return 0;
}