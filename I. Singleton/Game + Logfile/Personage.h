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
	virtual std::string getrace() const = 0;// const { return name; }
	Personage(std::string n) : name(n) {}
	virtual void Print() { std::cout << name << std::endl; };
	virtual void Save(std::ofstream &f) = 0;
};

class Magic : public Personage {
	std::string race;
public:
	virtual std::string getrace() const { return race; }
	Magic(std::string n) : Personage(n), race("Magic") {}
	virtual void Print() { std::cout << name << "\t: " << race << std::endl; }
	virtual void Save(std::ofstream &f) {
		f << name << "\t: " << race << std::endl;
	}
};

class Warrior : public Personage {
	std::string race;
public:
	virtual std::string getrace() const { return race; }
	Warrior(std::string n) : Personage(n), race("Warrior") {}
	virtual void Print() { std::cout << name << "\t: " << race << std::endl; }
	virtual void Save(std::ofstream &f) {
		f << name << "\t: " << race << std::endl;
	}
};

class Gnom : public Personage {
	std::string race;
public:
	virtual std::string getrace() const { return race; }
	Gnom(std::string n) : Personage(n), race("Gnom") {}
	virtual void Print() { std::cout << name << "\t: " << race << std::endl; }
	virtual void Save(std::ofstream &f) {
		f << name << "\t: " << race << std::endl;
	}
};

enum person { magic = 1, warrior, gnom };

Personage *Factory(person num, std::string name) {
	switch (num)
	{
	case magic: return new Magic(name); break;
	case warrior: return new Warrior(name); break;
	case gnom: return new Gnom(name); break;
	default: assert(false);
	}
}