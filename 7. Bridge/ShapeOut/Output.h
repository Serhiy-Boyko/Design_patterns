#pragma once
#include "Shape.h"

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