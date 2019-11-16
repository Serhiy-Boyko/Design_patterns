#include "Shape.h"
#include "Output.h"

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