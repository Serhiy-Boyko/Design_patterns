#include <iostream>
#include <vector>
#include <time.h>

class IRobot2;

class IRobot1 {
public:
	virtual void LessX() = 0;
	virtual void MoreY() = 0;
	virtual void MoreX() = 0;
	virtual void LessY() = 0;
	virtual void  Info() = 0;
	static IRobot1 *CreateRobot(int sx, int sy);
	static IRobot1 *CreateAdapter(IRobot2 *r);
};

class Robot1 : public IRobot1 {
	int x;
	int y;
public:
	Robot1(int sx, int sy) : x(sx), y(sy) {}
	virtual void LessX() { x--; }
	virtual void MoreY() { y++; }
	virtual void MoreX() { x++; }
	virtual void LessY() { y--; }
	virtual void Info() { std::cout << " R1(" << x << "," << y << ") "; }
};

IRobot1 *IRobot1::CreateRobot(int sx, int sy) {
	return new Robot1(sx, sy);
}

class IRobot2 {
public:
	virtual void  Left(int d) = 0;
	virtual void    Up(int d) = 0;
	virtual void Right(int d) = 0;
	virtual void  Down(int d) = 0;
	virtual void Info() = 0;
	static IRobot2 *CreateRobot(int sx, int sy);
	static IRobot2 *CreateAdapter(IRobot1 *r);
};

class Robot2 : public IRobot2 {
	int x;
	int y;
public:
	Robot2(int sx, int sy) : x(sx), y(sy) {}
	virtual void  Left(int d) { x -= d; }
	virtual void    Up(int d) { y += d; }
	virtual void Right(int d) { x += d; }
	virtual void  Down(int d) { y -= d; }
	virtual void Info() { std::cout << " R2(" << x << "," << y << ") "; }
};

IRobot2 *IRobot2::CreateRobot(int sx, int sy) {
	return new Robot2(sx, sy);
}

class Adapter1 : public IRobot1 {
	IRobot2 *robot;
public:
	Adapter1(IRobot2 *r) : robot(r) {}
	virtual void LessX() { robot->Left(1); }
	virtual void MoreY() { robot->Up(1); }
	virtual void MoreX() { robot->Right(1); }
	virtual void LessY() { robot->Down(1); }
	virtual void Info() { robot->Info(); }
	virtual ~Adapter1() { delete robot; }
};

IRobot1 *IRobot1::CreateAdapter(IRobot2 *r) {
	return new Adapter1(r);
}

class  Adapter2 : public IRobot2 {
	IRobot1 *robot;
public:
	Adapter2(IRobot1 *r) : robot(r) {}
	virtual void Left(int d) {
		for (int i = 0; i < d; i++)
			robot->LessX();
	}
	virtual void Up(int d) {
		for (int i = 0; i < d; i++)
			robot->MoreY();
	}
	virtual void Right(int d) {
		for (int i = 0; i < d; i++)
			robot->MoreX();
	}
	virtual void Down(int d) {
		for (int i = 0; i < d; i++)
			robot->LessY();
	}
	virtual void Info() { robot->Info(); }
	virtual ~Adapter2() { delete robot; }
};

IRobot2 *IRobot2::CreateAdapter(IRobot1 *r) {
	return new Adapter2(r);
}

class IManagement {
public:
	virtual size_t Count() = 0;
	virtual void MoveUnits() = 0;
	virtual void Info() = 0;
};

class Management1 : public IManagement {
	std::vector<IRobot1*> unit;
public:
	void AddRobot(IRobot1 *r) { unit.push_back(r); }
	virtual size_t Count() { return unit.size(); }

	virtual void MoveUnits() {
		for (auto &i : unit)
			switch (rand() % 4)
			{
			case 0: i->LessX(); break;
			case 1: i->MoreY(); break;
			case 2: i->MoreX(); break;
			case 3: i->LessY(); break;
			}
	}

	virtual void Info() {
		std::cout << " Management1: ";
		for (auto i : unit)
			i->Info();
		std::cout << std::endl;
	}
};

class Management2 : public IManagement {
	std::vector<IRobot2*> unit;
public:
	void AddRobot(IRobot2 *r) { unit.push_back(r); }
	virtual size_t Count() { return unit.size(); }

	virtual void MoveUnits() {
		for (auto &i : unit)
			switch (rand() % 4)
			{
			case 0: i->Left(1 + rand() % 4); break;
			case 1: i->Up(1 + rand() % 4); break;
			case 2: i->Right(1 + rand() % 4); break;
			case 3: i->Down(1 + rand() % 4); break;
			}
	}

	virtual void Info() {
		std::cout << " Management2: ";
		for (auto i : unit)
			i->Info();
		std::cout << std::endl;
	}
};

int main()
{
	srand(time(0));
	Management1 sys1;
	sys1.AddRobot(IRobot1::CreateRobot(2, 2));
	sys1.AddRobot(IRobot1::CreateRobot(3, 3));
	sys1.AddRobot(IRobot1::CreateRobot(4, 4));
	sys1.AddRobot(IRobot1::CreateAdapter(IRobot2::CreateRobot(5, 5)));
	sys1.Info();
	sys1.MoveUnits();
	sys1.Info();

	Management2 sys2;
	sys2.AddRobot(IRobot2::CreateRobot(1, 5));
	sys2.AddRobot(IRobot2::CreateAdapter(IRobot1::CreateRobot(1, 5)));
	sys2.Info();
	sys2.MoveUnits();
	sys2.Info();

	system("Pause");
	return 0;
}
