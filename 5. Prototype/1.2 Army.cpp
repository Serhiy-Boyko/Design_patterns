#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cassert>

enum Warrior_ID { Infantryman_ID, Archer_ID, Horseman_ID };

class Warrior {
protected:
	int hitpoints;
	int strength;
	std::string grade = "Recruit";
public:
	Warrior(int h, int s) : hitpoints(h), strength(s) {}
	// virtual Warrior* clone() = 0;
	virtual void Info() = 0;
	virtual ~Warrior() {}

	static Warrior *CreateWarrior(int num);
};

class Infantryman : public Warrior {
	Infantryman(int h, int s) : Warrior(h, s) {};
	Infantryman operator=(const Infantryman &) = delete;
	// Infantryman(const Infantryman &);
	static Infantryman *prototype;
public: 
	static Warrior* clone() { return new Infantryman(*prototype); }
	virtual void Info() {
		std::cout << std::setw(11) << grade;
		std::cout << std::setw(14) << " infantryman: ";
		std::cout << hitpoints << " " << strength << std::endl;
	};
	static void Upgrade() {
		prototype->hitpoints++;
		prototype->strength++;
		if (prototype->hitpoints < 18) prototype->grade = "Recruit";
		else if (prototype->hitpoints < 21) prototype->grade = "Experienced";
		else prototype->grade = "Veteran";
	}
};
Infantryman *Infantryman::prototype = new Infantryman(15, 5);

class Archer : public Warrior {
	Archer(int h, int s) : Warrior(h, s) {};
	Archer operator=(const Archer &) = delete;
	//Archer(const Archer &);
	static Archer *prototype;
public: 
	static Warrior* clone() { return new Archer(*prototype); }
	virtual void Info() {
		std::cout << std::setw(11) << grade;
		std::cout << std::setw(14) << " archer: ";
		std::cout << hitpoints << " " << strength << std::endl;
	};
	static void Upgrade() {
		prototype->hitpoints++;
		prototype->strength++;
		if (prototype->hitpoints < 15) prototype->grade = "Recruit";
		else if (prototype->hitpoints < 18) prototype->grade = "Experienced";
		else prototype->grade = "Veteran";
	}
};
Archer *Archer::prototype = new Archer(12, 4);

class Horseman : public Warrior {
	Horseman(int h, int s) : Warrior(h, s) {};
	Horseman operator=(const Horseman &) = delete;
	//Horseman(const Horseman &);
	static Horseman *prototype;
public:
	static Warrior* clone() { return new Horseman(*prototype); }
	virtual void Info() {
		std::cout << std::setw(11) << grade;
		std::cout << std::setw(14) << " horseman: ";
		std::cout << hitpoints << " " << strength << std::endl;
	};
	static void Upgrade() {
		prototype->hitpoints++;
		prototype->strength++;
		if (prototype->hitpoints < 30) prototype->grade = "Recruit";
		else if (prototype->hitpoints < 35) prototype->grade = "Experienced";
		else prototype->grade = "Veteran";
	}
};
Horseman *Horseman::prototype = new Horseman(25, 7);

Warrior *Warrior::CreateWarrior(int num) {
	switch (num)
	{
	case 0: return Infantryman::clone(); break;
	case 1: return Archer::clone(); break;
	case 2: return Horseman::clone(); break;
	default: assert(false);
	}
}

int main()
{
	std::vector<Warrior*> v;
	v.push_back(Warrior::CreateWarrior(Infantryman_ID));
	v.push_back(Warrior::CreateWarrior(Archer_ID));
	v.push_back(Warrior::CreateWarrior(Horseman_ID));

	Infantryman::Upgrade();
	Infantryman::Upgrade();
	v.push_back(Warrior::CreateWarrior(Infantryman_ID));
	Infantryman::Upgrade();
	v.push_back(Warrior::CreateWarrior(Infantryman_ID));
	v.push_back(Warrior::CreateWarrior(Infantryman_ID));

	for (int i = 0; i < v.size(); i++)
		v[i]->Info();

	system("Pause");
	return 0;
}
