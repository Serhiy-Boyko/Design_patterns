#include "Management.h"

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
