#include "Output.h"

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