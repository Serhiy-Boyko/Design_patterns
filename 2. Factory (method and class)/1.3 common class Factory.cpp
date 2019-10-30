#include <iostream>
#include <vector>
#include <cassert>
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
	int i, a, h;
public:
	Factory() : i(0), a(0), h(0) {}

	void Print() {
		std::cout << "       Total: " << i + a + h << std::endl;
		std::cout << " Infantryman: " << i << std::endl;
		std::cout << "      Archer: " << a << std::endl;
		std::cout << "    Horseman: " << h << std::endl;
	}

	Warrior *CreateWarrior(int num) {
		switch (num)
		{
		case 0: i++; return new Infantryman; break;
		case 1: a++; return new Archer;  break;
		case 2: h++; return new Horseman;  break;
		default: assert(false);
		}
	}
};

int main()
{
	srand(time(0));
	Factory ArmyFactory;
	std::vector<Warrior*> Army;

	int cnt = 8;
	for (int i = 0; i < cnt; i++)
		Army.push_back(ArmyFactory.CreateWarrior(rand() % 3));

	for (int i = 0; i < cnt; i++)
		Army[i]->Info();

	ArmyFactory.Print();
	system("Pause");
	return 0;
}