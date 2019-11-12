#include <iostream>
#include <vector>

// Поліморфний базовий клас
class Warrior {
public:
	Warrior() {}
	virtual Warrior* clone() = 0;
	virtual void info() = 0;	
};

class Infantryman : public Warrior {
private:
	Infantryman() {}	
public:
	Warrior* clone() { return new Infantryman(*this); }
	void info() { std::cout << "Infantryman" << std::endl; }

	friend class PrototypeFactory;
};

class Archer : public Warrior {
private:
	Archer() {}
public:
	Warrior* clone() { return new Archer(*this); }
	void info() { std::cout << "Archer" << std::endl; }

	friend class PrototypeFactory;
};

class Horseman : public Warrior {
private:
	Horseman() {}	
public:
	Warrior* clone() { return new Horseman(*this); }
	void info() { std::cout << "Horseman" << std::endl; }

	friend class PrototypeFactory;
};

// Фабрика, яка використовує прототипи 
class PrototypeFactory {
public:
	Warrior* createInfantrman() {
		static Infantryman prototype;
		return prototype.clone();
	}
	Warrior* createArcher() {
		static Archer prototype;
		return prototype.clone();
	}
	Warrior* createHorseman() {
		static Horseman prototype;
		return prototype.clone();
	}
};

int main() {
	PrototypeFactory factory;
	std::vector<Warrior*> v;
	v.push_back(factory.createInfantrman());
	v.push_back(factory.createArcher());
	v.push_back(factory.createHorseman());

	for (int i = 0; i < v.size(); i++)
		v[i]->info();

	system("pause");
	return 0;
}