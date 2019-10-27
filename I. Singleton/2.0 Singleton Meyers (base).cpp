#include <iostream>

// Сінглетон Майєрса не передбачає деструктора
class Singleton {
	// закритий конструктор
	Singleton() {}
public:
	// видалення конструктора і перегрузки присвоєння
	Singleton(const Singleton&) = delete;
	Singleton &operator=(Singleton&) = delete;

	/* при першому виклику буде створено об'єкт,
	який є статичним у ф-ї,
	всі інші виклики просто повертається
	вже створений єдиний екземпляр класу */
	static Singleton &getInstance() {
		static Singleton instance;
		return instance;
	}
};

void main() {
	Singleton *p = &Singleton::getInstance();
	/* створити екземпляр класу неможливо,
	бо конструктори закриті або видалені */
	// Singleton A; 
	// Singleton B = *p;
	system("Pause");
}