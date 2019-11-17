#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

// Component 
class Unit {
protected:
	std::string name;
	Unit(std::string n) : name(n) {}
public:
	virtual void Info() = 0;
	virtual int getCount() = 0;
	virtual void PutInside(Unit* p) {
		std::cout << " ви не можете сюди щось покласти " << std::endl;
	};
	virtual ~Unit() {}
};

// -----------------------------------------------------
/* Primitives - класи простих речей
   кількість 1 для кожного предмету */

class Pen : public Unit {
public:
	Pen() : Unit("pen") {}
	virtual void Info() { std::cout << "  " << name << std::endl; }
	virtual int getCount() { return 1; };
	virtual ~Pen() {}
};

class Pencil : public Unit {
public:
	Pencil() : Unit("pencil") {}
	virtual void Info() { std::cout << "  " << name << std::endl; }
	virtual int getCount() { return 1; };
	virtual ~Pencil() {}
};

class Needle : public Unit { // Голка
public:
	Needle() : Unit("needle") {}
	virtual void Info() { std::cout << "  " << name << std::endl; }
	virtual int getCount() { return 1; };
	virtual ~Needle() {}
};

// -----------------------------------------------------
// Composite - класи коробок - кількість 1 + речі в коробці

class smallBox : public Unit {
	std::vector<Unit*> inside;
public:
	smallBox() : Unit("smallBox") {}

	virtual void Info() {
		std::cout << "-----------------------" << std::endl;
		std::cout << " " << name << ": " << std::endl;
		for (auto i:inside)
			i->Info();
	}

	virtual int getCount() { // кількість речей в коробці
		int res = 0;
		for (auto i : inside)
			res += i->getCount();
		return res + 1;
	};

	virtual void PutInside(Unit* p) { inside.push_back(p); }

	virtual ~smallBox() { 
		for (auto i : inside)
			i->~Unit();
	}
};

class bigBox : public Unit {
	std::vector<Unit*> inside;
public:
	bigBox() : Unit("bigBox") {}
	virtual void Info() {
		std::cout << "==============================" << std::endl;
		std::cout << " " << name << ": " << std::endl;
		for (auto i : inside)
			i->Info();
	}

	virtual int getCount() { // кількість речей в коробці
		int res = 0;
		for (auto i : inside)
			res += i->getCount();
		return res + 1;
	};

	virtual void PutInside(Unit* p) { inside.push_back(p); }

	virtual ~bigBox() {
		for (auto i : inside)
			i->~Unit();
	}
};

int main()
{
	// створюємо малу коробку
	Unit *sbox = new smallBox();

	// створюємо речі і кладемо в малу коробку
	for (int i = 0; i < 3; i++)
		sbox->PutInside(new Pen());

	sbox->PutInside(new Needle());

	// перелік речей в малій коробці
	sbox->Info();

	// к-ть речей в малій коробці
	std::cout << " count in smallBox: " << sbox->getCount() << std::endl;

	// створюємо велику коробку
	Unit *bbox = new bigBox();

	// створюємо речі і кладемо у велику коробку
	bbox->PutInside(new Pencil());
	bbox->PutInside(new Pencil());
	// кладемо малу коробку у велику коробку
	bbox->PutInside(sbox);

	// перелік речей у великій коробці
	bbox->Info();

	// к-ть речей у великій коробці
	std::cout << " count in Bigbox: " << bbox->getCount() << std::endl;
	
	delete bbox;
	system("Pause");
	return 0;
}
