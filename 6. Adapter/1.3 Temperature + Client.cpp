#include <iostream>
#include <vector>
#include <time.h>

class Sensor {
public:
	virtual float getTemperature() = 0;
};

class FahrenheitSensor : public Sensor {
public:
	float getTemperature() {
		return 32 + rand() % 80 + 0.01*(rand() % 100);
	}
};

class CelsiusSensor : public Sensor {
public:
	virtual float getTemperature() {
		return rand() % 40 + 0.01*(rand() % 100);
	}
};

class Adapter : public Sensor {
	FahrenheitSensor *f;
public:
	Adapter(FahrenheitSensor* ff) : f(ff) { }

	float getTemperature() {
		return (f->getTemperature() - 32.0) / 1.8;
	}

	~Adapter() { delete f; }
};

// це наш клієнт
class Device {
	Sensor *sensor;
	std::vector <float> Celsius;
public:
	Device(Sensor *s) :sensor(s) {}
	void Assign(Sensor *s) { sensor = s; }
	void Metering() { Celsius.push_back(sensor->getTemperature()); }

	void Print() {
		for (auto i : Celsius)
			std::cout << " " << i;
		std::cout << std::endl;
	}

	float Mean() {
		float suma = 0;
		for (auto i : Celsius)
			suma += i;
		return suma / Celsius.size();
	}
};

int main()
{
	srand(time(0));
	// міряємо температуру термометром Цельсія
	Sensor *c = new CelsiusSensor;
	Device X(c);
	X.Metering();
	X.Metering();
	X.Metering();
	X.Print();
	std::cout << " Mean: " << X.Mean() << std::endl;

	// міряємо температуру термометром Фаренгейта
	FahrenheitSensor *f = new FahrenheitSensor;
	Sensor *a = new Adapter(f);
	X.Assign(a);
	X.Metering();
	X.Metering();
	X.Metering();
	// клас Device не знає, що термометр давно змінили
	X.Print();
	std::cout << " Mean: " << X.Mean() << std::endl;

	system("Pause");
	return 0;
}