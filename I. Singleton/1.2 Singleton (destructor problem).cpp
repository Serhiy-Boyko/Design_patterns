#include <iostream>

class Singleton {
	// звичайне поле
	int *field;

	// статичний вказівник на екземпляр класу 
	static Singleton *p_instance;

	// закриті конструктори і перегрузка присвоєння
	Singleton() {}
	explicit Singleton(int afield) : field(new int(afield)) {}
	Singleton(const Singleton&);
	Singleton &operator=(Singleton&);
public:
	void Set(int afield) { *field = afield; }
	void Print() { std::cout << "*field: " << *field << std::endl; }

	~Singleton() {
		delete field;
		std::cout << " ~Singleton()" << std::endl;
	}

	/* статичний метод, який повертає вказівник на
	єдиний екземпляр класу */
	static Singleton *getReference() { return p_instance; }
};

/* Ініціалізація статичного вказівника класу:
при запуску програми конструктором створюється об'єкт,
на який вказує статичний вказівник */
Singleton *Singleton::p_instance = new Singleton(14);

void Method() {
	// отримуємо вказівник на єдиний екземпляр класу
	Singleton *p = Singleton::getReference();
	// робота з об'єктом  
	p->Print();
	p->Set(26);
	p->Print();
	// ручний виклик деструктора
	p->~Singleton();
}

void Other_Method() {
	Singleton *p = Singleton::getReference();
	p->Print(); // програма видає сміття
	p->Set(38);
	p->Print();
	p->~Singleton(); // програма падає
}

void main()
{
	/* Ручний виклик деструктора може викликати цілий ряд помилок
	в різних частинах програми, які звертаються до Сінгетона */
	Method();
	Other_Method();
	system("pause");
}