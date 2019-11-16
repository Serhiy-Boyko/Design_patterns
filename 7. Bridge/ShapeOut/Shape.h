#pragma once
#include "Header.h"

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

	std::string getname() { return name; }
	std::string getKoords() { return LeftUp.str() + "\n" + RightDown.str(); }
};

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