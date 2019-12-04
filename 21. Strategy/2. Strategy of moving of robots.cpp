/* Завдання:
1.	Реалізувати клас «Робот», який буде рухатися по координатній площині 
вздовж осей. Поля – поточні координати. 
Методи (lessX(), moreY(), moreX(), lessY()) – кожен пересуває робота 
у заданому напрямку на одну одиницю. Метод, що повідомляє 
поточні координати робота.

2.	Реалізувати клас «Управління», який керуватиме цілим рядом Роботів. 
Методи: конструктор, який приймає стратегію руху, «Додати робота», 
«Рухати роботів»(згідно стратегії), «Інформація»(кожен робот 
повідомляє свої координати), «Кількість» (повертає кількість роботів 
під управлінням).

3.	Стратегій має бути дві: випадкове пересування робота і така, 
що реалізує просування робота у точку початку координат.
*/
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

class Robot {
	int x;
	int y;
public:
	Robot(int sx, int sy) : x(sx), y(sy) {}
	void LessX() { x--; }
	void MoreY() { y++; }
	void MoreX() { x++; }
	void LessY() { y--; }
	void Info() { std::cout << " R1(" << x << "," << y << ") "; }
	int getx() { return x; }
	int gety() { return y; }
	static Robot *CreateRobot(int sx, int sy);
};

Robot *Robot::CreateRobot(int sx, int sy) {
	return new Robot(sx, sy);
}

class Strategy {
public:
	virtual void move(Robot *r) = 0;
};

// тут стратегії ще можна було б зробити однинаками
class Random : public Strategy {
public:
	virtual void move(Robot *r) {
		switch (rand() % 4)
		{
		case 0: r->LessX(); break;
		case 1: r->MoreY(); break;
		case 2: r->MoreX(); break;
		case 3: r->LessY(); break;
		}
	}
};

// в початок координат
class ToOrigin : public Strategy {
public:
	virtual void move(Robot *r) {
		if (r->getx() > 0)
			r->LessX();
		else
			if (r->getx() < 0)
				r->MoreX();
			else
				if (r->gety() > 0)
					r->LessY();
				else
					if (r->gety() < 0)
						r->MoreY();
	}
};

class Management {
	std::vector<Robot*> unit;
	Strategy *strategy;
public:
	Management(Strategy *s) : strategy(s) {}
	void ChangeStrategy(Strategy* s) { strategy = s; }

	void AddRobot(Robot *r) { unit.push_back(r); }
	size_t Count() { return unit.size(); }

	void MoveUnits() {
		for (auto &i : unit)
			strategy->move(i);
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
	std::cout << " Random strategy" << std::endl;
	Random random;
	Management sys1(&random);
	sys1.AddRobot(Robot::CreateRobot(2, 2));
	sys1.AddRobot(Robot::CreateRobot(3, 3));
	sys1.AddRobot(Robot::CreateRobot(4, 4));
	sys1.AddRobot(Robot::CreateRobot(5, 5));
	sys1.Info();
	sys1.MoveUnits();
	sys1.Info();

	std::cout << std::endl;
	std::cout << " ToOrigin strategy" << std::endl;
	ToOrigin toOridgin;
	Management sys2(&toOridgin);
	sys2.AddRobot(Robot::CreateRobot(1, 5));
	sys2.AddRobot(Robot::CreateRobot(2, 5));
	sys2.Info();
	sys2.MoveUnits();
	sys2.Info();
	sys2.MoveUnits();
	sys2.MoveUnits();
	sys2.MoveUnits();
	sys2.Info();

	system("Pause");
	return 0;
}