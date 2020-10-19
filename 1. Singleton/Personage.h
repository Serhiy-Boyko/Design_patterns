#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>

/* Реалізація у всіх персонажів однакова, але, 
якщо "гру" потрібно буде розширяти, 
то при такому стартовому коді це буде зручно */

class Personage {
protected:
	std::string name;
public:
	virtual const std::string &getrace() const = 0;
	Personage(const std::string &n) : name(n) {}
	virtual void Print() const { std::cout << name << std::endl; };
	friend std::ofstream &operator << (std::ofstream &f, const Personage *A) {
		f << A->name << "\t: " << A->getrace() << std::endl;
		return f;
	}
};

class Magic : public Personage {
	std::string race;
public:
	virtual const std::string &getrace() const { return race; }
	Magic(const std::string &n) : Personage(n), race("Magic") {}
	
	virtual void Print()const override 
	{ std::cout << name << "\t: " << race << std::endl;}
};

class Warrior : public Personage {
	std::string race;
public:
	virtual const std::string &getrace() const { return race; }
	Warrior(const std::string &n) : Personage(n), race("Warrior") {}
	
	virtual void Print()const override 
	{ std::cout << name << "\t: " << race << std::endl;}
};

class Gnom : public Personage {
	std::string race;
public:
	virtual const std::string &getrace() const { return race; }
	Gnom(const std::string &n) : Personage(n), race("Gnom") {}
	
	virtual void Print()const override 
	{ std::cout << name << "\t: " << race << std::endl;}
};

enum person { magic = 1, warrior, gnom };

Personage *Factory(person num, const std::string &name) {
	switch (num)
	{
	case magic: return new Magic(name); break;
	case warrior: return new Warrior(name); break;
	case gnom: return new Gnom(name); break;
	default: assert(false);
	}
}