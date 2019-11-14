#pragma once
#include "Header.h"

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

class Adapter2 : public IRobot2 {
	IRobot1 *robot;
public:
	Adapter2(IRobot1 *r) : robot(r) {}
	virtual void  Left(int d);
	virtual void    Up(int d);
	virtual void Right(int d);
	virtual void  Down(int d);
	virtual void Info() { robot->Info(); }
	virtual ~Adapter2() { delete robot; }
};
