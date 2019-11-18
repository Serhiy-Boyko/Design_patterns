#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <fstream>

class Output {
public:
	Output() {}
	virtual void getInfo(std::string name, std::string Koords) = 0;
};

class console : public Output {
	Output *p; // клас може мати додаткову функціональність
public:
	console() : p(nullptr) {}
	console(Output *pa) : p(pa) {}

	virtual void getInfo(std::string name, std::string Koords) {
		std::cout << name << " " << Koords << std::endl;
		if (p) // перевірка додаткової функціональністі
			p->getInfo(name, Koords);
	}
};

class message : public Output {
	Output *p;
public:
	message() : p(nullptr) {}
	message(Output *pa) : p(pa) {}

	virtual void getInfo(std::string name, std::string Koords) {
		std::string s = name;
		std::string info = Koords;
		// конвертируем ANSI-строки в Unicode-строки
		wchar_t *ptr = new wchar_t[s.length() + 1];
		mbstowcs(ptr, s.c_str(), s.length());
		ptr[s.length()] = '\0';
		wchar_t *str = new wchar_t[info.length() + 1];
		mbstowcs(str, info.c_str(), info.length());
		str[info.length()] = '\0';

		MessageBox(0, str, ptr, MB_OK | MB_ICONINFORMATION);

		if (p)
			p->getInfo(name, Koords);
	}
};

class logfile : public Output {
	Output *p;
public:
	logfile() : p(nullptr) {}
	logfile(Output *pa) : p(pa) {}

	virtual void getInfo(std::string name, std::string Koords) {
		std::ofstream f("log.txt", std::ios::app);
		f << name << " " << Koords << std::endl;
		f.close();
		if (p)
			p->getInfo(name, Koords);
	}
};

// ---------------------------------------------------------------------
class Point {
	std::string name;
	double x, y;
	Output *p;
public:
	Point(Output *ap) : p(ap) {
		x = -10 + rand() % 21;
		y = -10 + rand() % 21;
		name = "Point";
	}

	void getInfo() { p->getInfo(name, str()); }

	double getx() { return x; }
	double gety() { return y; }

	std::string str() {
		char s[50];
		sprintf(s, " x: %0.2f  y: %0.2f ", x, y);
		return s;
	}
};

int main()
{
	srand(time(0));

	//Point X(new console);
	//X.getInfo();

	//Point Y(new message);
	//Y.getInfo();

	//Point Z(new logfile);
	//Z.getInfo();

	// конфигурація функціональності визначається клієнтом
	Point U(new console(new logfile(new message)));
	U.getInfo();
	system("Pause");
	return 0;
}