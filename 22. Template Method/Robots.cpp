#include <iostream>
#include <vector>
#include <string>
#include <time.h>

class IRobot {
protected:
	int x;
	int y;
public:
	IRobot(int sx, int sy) : x(sx), y(sy) {}
	virtual void LessX() = 0;
	virtual void MoreY() = 0;
	virtual void MoreX() = 0;
	virtual void LessY() = 0;
	void Info() { std::cout << " R(" << x << "," << y << ") "; }
};

class Robot : public IRobot {
public:
	Robot(int sx, int sy) : IRobot(sx, sy) {}
	virtual void LessX() { x--; }
	virtual void MoreY() { y++; }
	virtual void MoreX() { x++; }
	virtual void LessY() { y--; }
};

class Turbo_Robot : public IRobot {
public:
	Turbo_Robot(int sx, int sy) : IRobot(sx, sy) {}
	virtual void LessX() { x-=5; }
	virtual void MoreY() { y+=5; }
	virtual void MoreX() { x+=5; }
	virtual void LessY() { y-=5; }
};

class Management {
	std::vector<IRobot*> unit;
public:
	void AddRobot(IRobot *r) { unit.push_back(r); }
	virtual size_t Count() { return unit.size(); }

	virtual void MoveUnits() {
		std::cout << " Management: ";
		for (auto &i : unit)
			switch (rand() % 4)
			{
			case 0: i->LessX(); i->Info(); break;
			case 1: i->MoreY(); i->Info(); break;
			case 2: i->MoreX(); i->Info(); break;
			case 3: i->LessY(); i->Info(); break;
			}
		std::cout << std::endl;
	}

	virtual void Info() {
		std::cout << " Management: ";
		for (auto i : unit)
			i->Info();
		std::cout << std::endl;
	}
};

int main()
{
	srand(time(0));
	Management sys;
	sys.AddRobot(new Robot(2, 2));
	sys.AddRobot(new Robot(3, 3));
	sys.AddRobot(new Turbo_Robot(11, 11));
	sys.AddRobot(new Turbo_Robot(15, 15));
	sys.Info();
	for (int i = 0; i < 5; i++)
		sys.MoveUnits();

	system("Pause");
	return 0;
}