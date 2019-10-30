#include <iostream>
#include <vector>
#include <time.h>

class Warrior {
protected:
	int hp; // hitpoints
public:
	Warrior() : hp(10) {}
	virtual void Info() = 0;
};

class Infantryman : public Warrior {
public:
	Infantryman() {
		hp = 15;
		std::cout << " create Infantryman " << std::endl;
	}
	virtual void Info() {
		std::cout << " Infantryman hitpoints:\t" << hp << std::endl;
	}
};

class Archer : public Warrior {
public:
	Archer() {
		hp = 12;
		std::cout << " create Archer " << std::endl;
	}
	virtual void Info() {
		std::cout << " Archer hitpoints:\t" << hp << std::endl;
	}
};

class Horseman : public Warrior {
public:
	Horseman() {
		hp = 25;
		std::cout << " create Horseman " << std::endl;
	}
	virtual void Info() {
		std::cout << " Horseman hitpoints:\t" << hp << std::endl;
	}
};

class Factory {
public:
	virtual Warrior* createWarrior() = 0;
	virtual ~Factory() {}
};

class InfantryFactory : public Factory {
public:
	Warrior* createWarrior() { return new Infantryman; }
};

class ArchersFactory : public Factory {
public:
	Warrior* createWarrior() { return new Archer; }
};

class CavalryFactory : public Factory {
public:
	Warrior* createWarrior() { return new Horseman; }
};

int main()
{
	srand(time(0));
	InfantryFactory *iFactory = new InfantryFactory;
	ArchersFactory  *aFactory = new ArchersFactory;
	CavalryFactory  *cFactory = new CavalryFactory;

	std::vector<Warrior*> Army;

	int cnt = 8;
	for (int i = 0; i < cnt; i++)
		switch (rand() % 3)
		{
		case 0: Army.push_back(iFactory->createWarrior()); break;
		case 1: Army.push_back(aFactory->createWarrior());  break;
		case 2: Army.push_back(cFactory->createWarrior());  break;
		}

	for (int i = 0; i < cnt; i++)
		Army[i]->Info();
	system("pause");
	return 0;
}