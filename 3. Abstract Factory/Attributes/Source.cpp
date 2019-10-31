#include <vector>
#include <time.h>
#include <windows.h>
#include "Box.h"

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	UkrFactory ukrfactory;
	PolFactory polfactory;
	BolFactory bolfactory;
	BoxFactory boxfact;

	std::vector<Box*> boxes; // вектор коробок з атрибутами

	const int cnt = 5;
	for (int i = 0; i < cnt; i++)
		switch (rand() % 3)
		{
		case 0: boxes.push_back(boxfact.createBox(ukrfactory)); break;
		case 1: boxes.push_back(boxfact.createBox(polfactory)); break;
		case 2: boxes.push_back(boxfact.createBox(bolfactory)); break;
		}

	for (int i = 0; i < boxes.size(); i++)
		boxes[i]->Info();

	system("Pause");
	return 0;
}