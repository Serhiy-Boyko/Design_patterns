﻿#include <iostream>

/* Singleton вирішує дві задачі:
   1. Гарантує наявність єдиного екземпляра класу
   2. Надає глобальну точку доступу. 
*/
class Singleton {
	// статичний вказівник на екземпляр класу 
	static Singleton *p_instance;

	// закриті конструктори і перегрузка присвоєння
	Singleton() {}
	Singleton(const Singleton&);
	Singleton &operator=(Singleton&);
public:
	/* статичний метод, який повертає вказівник на
	єдиний екземпляр класу */
	static Singleton *getReference() { return p_instance; }
};

/* Ініціалізація статичного вказівника класу:
при запуску програми конструктором створюється об'єкт,
на який вказує статичний вказівник */
Singleton *Singleton::p_instance = new Singleton;

int main()
{
	// отримуємо вказівник на єдиний екземпляр класу
	Singleton *p = Singleton::getReference();

	// створити екземпляр класу неможливо, бо конструктори закриті
	// Singleton A; 
	// Singleton B = *p;
	system("pause");
	return 0;
}