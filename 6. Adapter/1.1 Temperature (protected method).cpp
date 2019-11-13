#include <iostream>
#include <time.h>

// Клас, який потрібно адаптувати - 
// міряє температуру у градусах Фаренгейта
class FahrenheitSensor {
protected:
	int d = 80; // dispersion
	void adjust(int disp) { d = disp; }// Настройка датчика (защищенный метод)
public:
	float getFahrenheitTemp() {
		return 32 + rand() % d + 0.01*(rand() % 100); // 0 .. 4~
	}
};

class Sensor {
public:
	virtual ~Sensor() {}
	virtual float getTemperature() = 0;
	virtual void adjust(int disp) = 0;
};

class Adapter : public Sensor, private FahrenheitSensor
{
public:
	Adapter() { }
	float getTemperature() {
		return (getFahrenheitTemp() - 32.0)*5.0 / 9.0;
	}

	void adjust(int disp) {
		FahrenheitSensor::adjust(disp);
	}
};


int main()
{
	srand(time(0));
	FahrenheitSensor *fs = new FahrenheitSensor;
	Sensor *p = new Adapter();
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	p->adjust(40);
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	delete p;

	system("Pause");
	return 0;
}
