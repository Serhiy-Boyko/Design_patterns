#pragma once
#include <string>
#include "Factories.h"

/* ����-�������, �� ������ ������ �������� ��������
���������� ������� �������� �� �������,
��� ����������� � ����������� - �� ������ */
class Box {
	Anthen *a;
	Flag *f;
	Blazon *b;
	std::string name; // ����� �� ������� - ����� �����
	friend class BoxFactory;
public:
	void Info() { std::cout << name; f->Info(); b->Info(); a->Info(); }
	~Box() { delete a; delete f; delete b; }
};

// ������� ����-������� ��������� �������
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