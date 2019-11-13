#include <iostream>
#include <time.h>

// Клас, який потрібно адаптувати - 
// міряє температуру у градусах Фаренгейта
class FahrenheitSensor {
public:
	// метод повертає температуру в градусах Фаренгейта
	float getFahrenheitTemp() {
		return 32 + rand() % 80 + 0.01*(rand() % 100); // 0 .. 4~
	}
};

class Sensor {
public:
	virtual ~Sensor() {}
	virtual float getTemperature() = 0;
};

class Adapter : public Sensor {
	FahrenheitSensor* p_fsensor;
public:
	Adapter(FahrenheitSensor* p) : p_fsensor(p) { }

	~Adapter() { delete p_fsensor; }

	// перетворює температуру з градусів Фаренгейта у градуси Цельсія
	float getTemperature() {
		return (p_fsensor->getFahrenheitTemp() - 32.0) / 1.8;
	}
};

int main()
{
	srand(time(0));
	FahrenheitSensor *fs = new FahrenheitSensor;
	Sensor* p = new Adapter(fs);
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	delete p;

	system("Pause");
	return 0;
}
