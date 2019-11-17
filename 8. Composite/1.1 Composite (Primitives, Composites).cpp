﻿#include <iostream>
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
	virtual bool PutInside(Unit* p) = 0;
	virtual bool checkComposite() = 0;
	virtual ~Unit() {}
};

// -----------------------------------------------------
/* Primitives - класи простих речей
   кількість 1 для кожного предмету */

class Primitive : public Unit {
public:
	Primitive(std::string n) : Unit(n) {}
	virtual void Info() final{ std::cout << "  " << name << std::endl;}
	virtual int getCount() final { return 1; };
	virtual bool PutInside(Unit* p) { return false; }
	virtual bool checkComposite() final { return false; }
	virtual ~Primitive() {}
};

class Pen : public Primitive {
public:
	Pen() : Primitive("pen") {}
	virtual ~Pen() {}
};

class Pencil : public Primitive {
public:
	Pencil() : Primitive("pencil") {}
	virtual ~Pencil() {}
};

class Needle : public Primitive { // Голка
public:
	Needle() : Primitive("needle") {}
	virtual ~Needle() {}
};

// -----------------------------------------------------
/* Composite - класи складних речей (класи коробок)
   кількість 1 + речі в коробці */

class Composite : public Unit {
protected:
	std::vector<Unit*> inside;
public:
	Composite(std::string n) : Unit(n) {}
	// virtual void Info() = 0;
	virtual bool checkComposite() final { return true; }

	virtual int getCount() final { // кількість речей в коробці
		int res = 0;
		for (auto i : inside)
			res += i->getCount();
		return res + 1;
	};

	virtual bool PutInside(Unit* p) final { 
		inside.push_back(p); 
		return true;
	}

	virtual ~Composite() {
		for (auto i : inside)
			i->~Unit();
	}
};

class smallBox : public Composite {
public:
	smallBox() : Composite("smallBox") {}

	virtual void Info() override {
		std::cout << "-----------------------" << std::endl;
		std::cout << " " << name << ": " << std::endl;
		for (auto i:inside)
			i->Info();
	}

	virtual ~smallBox() {}
};

class bigBox : public Composite {
public:
	bigBox() : Composite("bigBox") {}

	virtual void Info() override {
		std::cout << "==============================" << std::endl;
		std::cout << " " << name << ": " << std::endl;
		for (auto i : inside)
			i->Info();
	}

	virtual ~bigBox() {}
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
