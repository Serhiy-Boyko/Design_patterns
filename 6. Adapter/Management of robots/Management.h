#pragma once
#include "Robots.h"

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

	virtual void MoveUnits();
	virtual void Info();
};

class Management2 : public IManagement {
	std::vector<IRobot2*> unit;
public:
	void AddRobot(IRobot2 *r) { unit.push_back(r); }
	virtual size_t Count() { return unit.size(); }

	virtual void MoveUnits();
	virtual void Info();
};
