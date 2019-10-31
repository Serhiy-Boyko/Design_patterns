#pragma once
#include <iostream>

/* Абстрактні базові класи атрибутів,
які складатимуть єдиний комплект -
класи пов'язані, хоч і не взаємодіють безпосередньо */
class Anthen { // гімн
public:
	virtual void Info() = 0;
};

class Flag { // прапор
public:
	virtual void Info() = 0;
};

class Blazon { // герб
public:
	virtual void Info() = 0;
};

/* Три класи атрибутів України, які складатимуть єдиний комплект -
класи пов'язані, хоч і не взаємодіють безпосередньо */
class UkrAnthen : public Anthen {
public:
	virtual void Info() { std::cout << " Ще не вмерла України " << std::endl; }
};

class UkrFlag : public Flag {
public:
	virtual void Info() { std::cout << " Блакитно-жовтий "; }
};

class UkrBlazon : public Blazon {
public:
	virtual void Info() { std::cout << " Тризуб "; }
};

/* Три класи атрибутів Польщі, які складатимуть єдиний комплект -
класи пов'язані, хоч і не взаємодіють безпосередньо */
class PolAnthen : public Anthen {
public:
	virtual void Info() {std::cout << " Єщо Польша не сгiнелла " << std::endl;}
};

class PolFlag : public Flag {
public:
	virtual void Info() { std::cout << " Бiло-червоний "; }
};

class PolBlazon : public Blazon {
public:
	virtual void Info() { std::cout << " Бiлий орел "; }
};

/* Три класи атрибутів Болгарії, які складатимуть єдиний комплект -
класи пов'язані, хоч і не взаємодіють безпосередньо */
class BolAnthen : public Anthen {
public:
	virtual void Info() { std::cout << " Мила Родино " << std::endl; }
};

class BolFlag : public Flag {
public:
	virtual void Info() { std::cout << " Бiло-зелено-червоний "; }
};

class BolBlazon : public Blazon {
public:
	virtual void Info() { std::cout << " Золотий лев "; }
};