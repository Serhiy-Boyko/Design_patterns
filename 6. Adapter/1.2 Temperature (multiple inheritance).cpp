#include <iostream>
#include <time.h>

// multiple inheritance

class FahrenheitSensor {
public:
	virtual ~FahrenheitSensor() {}
	float getFahrenheitTemp() {
		return 32 + rand() % 80 + 0.01*(rand() % 100); // 0 .. 4~
	}
};

class CelsiusSensor {
public:
	float getCelsiusTemp() {
		return rand() % 40 + 0.01*(rand() % 100);
	}
};

class Sensor {
public:
	virtual ~Sensor() {}
	virtual float getTemperature() = 0;
};

class AdapterFahrenheitToCelsius : public Sensor, private FahrenheitSensor
{
public:
	virtual ~AdapterFahrenheitToCelsius() {}
	virtual float getTemperature() {
		return (getFahrenheitTemp() - 32.0)*5.0 / 9.0;
	}
};

class AdapterCelsiusToFahrenheit : public Sensor, private CelsiusSensor
{
public:
	virtual ~AdapterCelsiusToFahrenheit() {}
	virtual float getTemperature() {
		return getCelsiusTemp()*9.0 / 5.0 + 32;
	}
};


int main()
{
	srand(time(0));
	Sensor *p = new AdapterFahrenheitToCelsius;
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	std::cout << "Celsius temperature: " << p->getTemperature() << std::endl;
	delete p;

	Sensor *u = new AdapterCelsiusToFahrenheit;
	std::cout << "Fahrenheit temperature: " << u->getTemperature() << std::endl;
	std::cout << "Fahrenheit temperature: " << u->getTemperature() << std::endl;
	delete u;

	system("Pause");
	return 0;
}
