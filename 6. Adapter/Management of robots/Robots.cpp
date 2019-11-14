#pragma once
#include "Robots.h"

IRobot1 *IRobot1::CreateRobot(int sx, int sy) {
	return new Robot1(sx, sy);
}

IRobot2 *IRobot2::CreateRobot(int sx, int sy) {
	return new Robot2(sx, sy);
}

IRobot1 *IRobot1::CreateAdapter(IRobot2 *r) {
	return new Adapter1(r);
}

void Adapter2::Left(int d) {
	for (int i = 0; i < d; i++)
		robot->LessX();
}
void Adapter2::Up(int d) {
	for (int i = 0; i < d; i++)
		robot->MoreY();
}
void Adapter2::Right(int d) {
	for (int i = 0; i < d; i++)
		robot->MoreX();
}
void Adapter2::Down(int d) {
	for (int i = 0; i < d; i++)
		robot->LessY();
}

IRobot2 *IRobot2::CreateAdapter(IRobot1 *r) {
	return new Adapter2(r);
}