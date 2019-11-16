#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

class Point {
	double x, y;
public:
	Point(double ax, double ay) : x(ax), y(ay) {}
	double getx() { return x; }
	double gety() { return y; }
	std::string str() {
		char s[50];
		sprintf(s, "   x: %0.2f  y: %0.2f ", x, y);
		return s;
	}
};

// ---------------------------------------------------------------------

class Shape;

class Output {
protected:
	Shape *p;
public:
	Output(Shape *A) : p(A) {}
	virtual void outputInfo() = 0;
};

class console : public Output {
public:
	console(Shape *A) : Output(A) {}
	virtual void outputInfo();
};

class message : public Output {
public:
	message(Shape *A) : Output(A) {}
	virtual void outputInfo();
};

class logfile : public Output {
public:
	logfile(Shape *A) : Output(A) {}
	virtual void outputInfo();
};

// ---------------------------------------------------------------------
// базовий клас для фігур
class Shape {
protected:
	std::string name;
	Point LeftUp;
	Point RightDown;
public:
	Shape(Point LU, Point RD) : LeftUp(LU), RightDown(RD), name("Shape") {}

	void consoleOut();
	void messageOut();
	void logfileOut();

	//void Output() {
	//	cout << " Shape: " << name << endl;
	//	cout << LeftUp.str() << endl;
	//	cout << RightDown.str() << endl;
	//}

	std::string getname() { return name; }
	std::string getKoords() { return LeftUp.str() + "\n" + RightDown.str(); }
};

// у класів Oval та Rectangle інтерфейс спільний, а реалізація різна
class Oval : public Shape {
public:
	Oval(Point LU, Point RD) : Shape(LU, RD) {
		name = "Oval";
	}
};

class Rectangle : public Shape {
public:
	Rectangle(Point LU, Point RD) : Shape(LU, RD) {
		name = "Rectangle";
	}
};

// ---------------------------------------------------------------------
void console::outputInfo() {
	std::cout << p->getname() << " : " << std::endl;
	std::cout << p->getKoords() << std::endl;
}

void message::outputInfo() {
	std::string s = p->getname();
	std::string info = p->getKoords();
	// конвертируем ANSI-строки в Unicode-строки
	wchar_t *ptr = new wchar_t[s.length() + 1];
	mbstowcs(ptr, s.c_str(), s.length());
	ptr[s.length()] = '\0';
	wchar_t *p = new wchar_t[info.length() + 1];
	mbstowcs(p, info.c_str(), info.length());
	p[info.length()] = '\0';

	MessageBox(0, p, ptr, MB_OK | MB_ICONINFORMATION);
}

void logfile::outputInfo() {
	std::ofstream f("log.txt", std::ios::app);
	f << p->getname() << " : " << std::endl;
	f << p->getKoords() << std::endl;
	f.close();
}

// ---------------------------------------------------------------------
void Shape::consoleOut() {
	console out(this);
	out.outputInfo();
}
void Shape::messageOut() {
	message out(this);
	out.outputInfo();
}
void Shape::logfileOut() {
	logfile out(this);
	out.outputInfo();
}

void main()
{
	//Point X(2, 5);
	//cout << " Point: " << X.str() << endl;
	Oval A({ 1, 6 }, { 6, 1 });
	A.consoleOut();
	A.logfileOut();
	A.messageOut();
	system("Pause");
}