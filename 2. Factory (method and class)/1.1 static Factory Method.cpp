#include <iostream>
#include <vector>
#include <cassert>
#include <time.h>

class Warrior {
protected:
	int hp;
public:
	Warrior() : hp(0) {}
	virtual void Info() = 0;

	static Warrior *CreateWarrior(int num);
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

Warrior *Warrior::CreateWarrior(int num) {
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
	srand(time(0));
	std::vector<Warrior*> Army;

	int cnt = 8;
	for (int i = 0; i < cnt; i++)
		Army.push_back(Warrior::CreateWarrior(rand() % 3));

	for (int i = 0; i < cnt; i++)
		Army[i]->Info();

	system("Pause");
	return 0;
}