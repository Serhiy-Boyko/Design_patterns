#include <iostream>
#include <cassert>
#include <vector>

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

enum Warrior_ID { Infantryman_ID = 0, Archer_ID, Horseman_ID };

Warrior *FactoryMethod(Warrior_ID num) {
	switch (num)
	{
	case 0: return new Infantryman; break;
	case 1: return new Archer; break;
	case 2: return new Horseman; break;
	default: assert(false);
	}
}

int main()
{
	std::vector<Warrior*> Army;
	Army.push_back(FactoryMethod(Infantryman_ID));
	Army.push_back(FactoryMethod(Infantryman_ID));
	Army.push_back(FactoryMethod(Archer_ID));
	Army.push_back(FactoryMethod(Archer_ID));
	Army.push_back(FactoryMethod(Archer_ID));
	Army.push_back(FactoryMethod(Horseman_ID));
	std::cout << std::endl;

	for (int i = 0; i < Army.size(); i++)
		Army[i]->Info();
	system("pause");
	return 0;
}