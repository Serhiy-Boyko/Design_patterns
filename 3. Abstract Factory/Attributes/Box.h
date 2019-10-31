#pragma once
#include <string>
#include "Factories.h"

/* Клас-коробка, що містить повний комплект атрибутів
наповнення коробки залежить від фабрики,
яка викликається у конструкторі - це зручно */
class Box {
	Anthen *a;
	Flag *f;
	Blazon *b;
	std::string name; // підпис на коробці - назва країни
	friend class BoxFactory;
public:
	void Info() { std::cout << name; f->Info(); b->Info(); a->Info(); }
	~Box() { delete a; delete f; delete b; }
};

// Окремий клас-фабрика створення коробок
class BoxFactory {
public:
	Box *createBox(Factory &fact) {
		Box *p = new Box;
		p->name = fact.getName();
		p->a = fact.createAnthen();
		p->f = fact.createFlag();
		p->b = fact.createBlazon();
		return p;
	}
};