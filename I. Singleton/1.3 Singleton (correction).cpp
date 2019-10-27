#include <iostream>

class Singleton {
	// звичайне поле
	int *field;

	// статичний вказівник на екземпляр класу 
	static Singleton *p_instance;

	// закриті конструктори і перегрузка присвоєння
	Singleton() : field() {}
	explicit Singleton(int afield) : field(new int(afield)) {}
	Singleton(const Singleton&);
	Singleton &operator=(Singleton&);
public:
	void Set(int afield) { *field = afield; }
	void Print() { std::cout << "*field: " << *field << std::endl; }

	~Singleton() {
		delete field;
		p_instance = nullptr;
		std::cout << " ~Singleton()" << std::endl;
	}

	/* статичний метод, який повертає вказівник на
	єдиний екземпляр класу, якщо вказівник був порожній,
	утворюється об'єкт */
	static Singleton *getReference() {
		if (!p_instance) {
			p_instance = new Singleton(12);
			std::cout << " create Singleton " << std::endl;
		}
		return p_instance;
	}
};

Singleton *Singleton::p_instance = nullptr;

void Method() {
	// створюється об'єкт і повертається вказівник на нього
	Singleton *p = Singleton::getReference();
	// робота з об'єктом  
	p->Print();
	p->Set(26);
	p->Print();
	// ручний виклик деструктора
	p->~Singleton();
}

void Other_Method() {
	// створюється інший об'єкт і повертається вказівник на нього
	Singleton *p = Singleton::getReference();
	p->Print();
	p->Set(38);
	p->Print();
	// тепер програма не падає
	p->~Singleton();
	// але все одно можуть бути проблеми, якщо невчасно викликати деструктор
	//p->Print(); 
	//p->Set(43);
	//p->Print();
}

void main()
{
	/* Ручний виклик деструктора може викликати цілий ряд помилок
	в різних частинах програми, які звертаються до Сінгетона */
	Method();
	Other_Method();
	system("pause");
}