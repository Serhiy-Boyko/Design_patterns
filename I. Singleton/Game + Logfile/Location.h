#pragma once
#include "Personage.h"
#include <list>

/* Реалізація у всіх локацій однакова, але,
якщо "гру" потрібно буде розширяти,
то при такому стартовому коді це буде зручно */

class Location {
protected:
	std::list<Personage*> inside;
	std::list<Personage*> approach;
public:
	Personage *Pop_visitor() {
		if (inside.begin() == inside.end())
			return nullptr;
		Personage *p = *inside.begin();
		inside.pop_front();
		return p;
	}
	void Add_visitor(Personage *A) { approach.push_back(A); }
	void Accept_visitors() {
		inside = approach;
		approach.clear();
	}
	virtual void Print_approach() = 0;
	virtual void Print_inside() = 0;
	virtual void Save_inside(std::ofstream &f) = 0;
};

class Castle : public Location {
	std::string name;
	static Castle *p_instance;
	Castle() : name("Castle") {}
	Castle(const Castle&) = delete;
	Castle &operator=(Castle&) = delete;
public:
	static Castle *getInstance() { return p_instance; }

	virtual void Print_approach() {
		std::cout << name << " approach:" << std::endl;
		for (auto it : approach)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Print_inside() {
		std::cout << name << " inside:" << std::endl;
		for (auto it : inside)
			it->Print();
		std::cout << std::endl;
	}

	virtual void Save_inside(std::ofstream &f) {
		f << name << " inside:" << std::endl;
		for (auto it : inside)
			it->Save(f);
		f << std::endl;
	}
};
Castle *Castle::p_instance = new Castle;

class Forest : public Location {
	std::string name;
	static Forest *p_instance;
	Forest() : name("Forest") {}
	Forest(const Forest&) = delete;
	Forest &operator=(Forest&) = delete;
public:
	static Forest *getInstance() { return p_instance; }

	virtual void Print_approach() {
		std::cout << name << " approach:" << std::endl;
		for (auto it : approach)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Print_inside() {
		std::cout << name << " inside:" << std::endl;
		for (auto it : inside)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Save_inside(std::ofstream &f) {
		f << name << " inside:" << std::endl;
		for (auto it : inside)
			it->Save(f);
		f << std::endl;
	}
};
Forest *Forest::p_instance = new Forest;

class Field : public Location {
	std::string name;
	static Field *p_instance;
	Field() : name("Field") {}
	Field(const Field&) = delete;
	Field &operator=(Field&) = delete;
public:
	static Field *getInstance() { return p_instance; }

	virtual void Print_approach() {
		std::cout << name << " approach:" << std::endl;
		for (auto it : approach)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Print_inside() {
		std::cout << name << " inside:" << std::endl;
		for (auto it : inside)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Save_inside(std::ofstream &f) {
		f << name << " inside:" << std::endl;
		for (auto it : inside)
			it->Save(f);
		f << std::endl;
	}
};
Field *Field::p_instance = new Field;

