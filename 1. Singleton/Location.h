#pragma once
#include "Personage.h"
#include <list>

/* Кожна локація - сінглетон.
Реалізація у всіх локацій однакова, але,
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

	void Accept_visitors() { inside = std::move(approach); }

	virtual const std::string &getname() const = 0;
	virtual void Print_approach() const = 0;
	virtual void Print_inside() const = 0;

	friend std::ofstream &operator << (std::ofstream &f, const Location *A){
		f << A->getname() << " inside:" << std::endl;
		for (auto &it : A->inside)
			f << it;
		f << std::endl;
		return f;
	}
};

class Castle : public Location {
	std::string name;
	static Castle *p_instance;
	Castle() : name("Castle") {}
	Castle(const Castle&) = delete;
	Castle &operator=(Castle&) = delete;
public:
	static Castle *getInstance() { return p_instance; }

	virtual const std::string &getname() const override { return name; };

	virtual void Print_approach() const {
		std::cout << name << " approach:" << std::endl;
		for (auto &it : approach)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Print_inside() const {
		std::cout << name << " inside:" << std::endl;
		for (auto &it : inside)
			it->Print();
		std::cout << std::endl;
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

	virtual const std::string &getname() const override { return name; };

	virtual void Print_approach() const {
		std::cout << name << " approach:" << std::endl;
		for (auto &it : approach)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Print_inside() const {
		std::cout << name << " inside:" << std::endl;
		for (auto &it : inside)
			it->Print();
		std::cout << std::endl;
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

	virtual const std::string &getname() const override { return name; };

	virtual void Print_approach() const {
		std::cout << name << " approach:" << std::endl;
		for (auto &it : approach)
			it->Print();
		std::cout << std::endl;
	}
	virtual void Print_inside() const {
		std::cout << name << " inside:" << std::endl;
		for (auto &it : inside)
			it->Print();
		std::cout << std::endl;
	}
};
Field *Field::p_instance = new Field;

