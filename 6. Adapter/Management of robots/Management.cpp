#pragma once
#include "Management.h"

void Management1::MoveUnits() {
	for (auto &i : unit)
		switch (rand() % 4)
		{
		case 0: i->LessX(); break;
		case 1: i->MoreY(); break;
		case 2: i->MoreX(); break;
		case 3: i->LessY(); break;
		}
}

void Management1::Info() {
	std::cout << " Management1: ";
	for (auto i : unit)
		i->Info();
	std::cout << std::endl;
}


void Management2::MoveUnits() {
	for (auto &i : unit)
		switch (rand() % 4)
		{
		case 0: i->Left(1 + rand() % 4); break;
		case 1: i->Up(1 + rand() % 4); break;
		case 2: i->Right(1 + rand() % 4); break;
		case 3: i->Down(1 + rand() % 4); break;
		}
}

void Management2::Info() {
	std::cout << " Management2: ";
	for (auto i : unit)
		i->Info();
	std::cout << std::endl;
}

