#pragma once
#include "Attributes.h"

// Абстрактна фабрика для виробництва атрибутів
class Factory {
protected:
	std::string name; // назва країни
public:
	Factory(std::string n) : name(n) {}
	std::string getName() { return name; }
	virtual Anthen *createAnthen() = 0;
	virtual  Flag  *createFlag() = 0;
	virtual Blazon *createBlazon() = 0;
	virtual ~Factory() {}
};

/* Фабрика для створення атрибутів України -
її завдання забезпечити можливість створення
кожного з трьох атрибутів */
class UkrFactory : public Factory {
public:
	UkrFactory() : Factory("Ukraine") {}
	virtual Anthen *createAnthen() { return new UkrAnthen; }
	virtual  Flag  *createFlag() { return new UkrFlag; }
	virtual Blazon *createBlazon() { return new UkrBlazon; }
};

/* Фабрика для створення атрибутів Польщі -
її завдання забезпечити можливість створення
кожного з трьох атрибутів */
class PolFactory : public Factory {
public:
	PolFactory() : Factory("Poland") {}
	virtual Anthen *createAnthen() { return new PolAnthen; }
	virtual  Flag  *createFlag() { return new PolFlag; }
	virtual Blazon *createBlazon() { return new PolBlazon; }
};

/* Фабрика для створення атрибутів Болгарії -
її завдання забезпечити можливість створення
кожного з трьох атрибутів */
class BolFactory : public Factory {
public:
	BolFactory() : Factory("Bulgaria") {}
	virtual Anthen *createAnthen() { return new BolAnthen; }
	virtual  Flag  *createFlag() { return new BolFlag; }
	virtual Blazon *createBlazon() { return new BolBlazon; }
};