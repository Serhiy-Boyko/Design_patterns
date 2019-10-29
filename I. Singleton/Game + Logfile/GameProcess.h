#pragma once
#include "Location.h"
#include "LogFile.h"

class GameProcess {
	Location *place[3] = { Castle::getInstance(), Forest::getInstance(),
		Field::getInstance() };
public:
	void Init();
	void Accept_all_visitors();
	void PrintAll();
	void SaveAll();
	void Moving();
};

/* Error LNK2005 "public: __thiscall LogDestroyer::~LogDestroyer(void)"
(??1LogDestroyer@@QAE@XZ) already defined in GameProcess.obj  */

void GameProcess::Init() {
	place[0]->Add_visitor(Factory(magic, "Alex"));
	place[0]->Add_visitor(Factory(magic, "Borys"));
	place[1]->Add_visitor(Factory(warrior, "Casima"));
	place[1]->Add_visitor(Factory(warrior, "Dana"));
	place[2]->Add_visitor(Factory(gnom, "Egor"));
	place[2]->Add_visitor(Factory(gnom, "Fedir"));
}

void GameProcess::Accept_all_visitors() {
	for (auto it : place)
		it->Accept_visitors();
}

void GameProcess::PrintAll() {
	for (auto it : place)
		it->Print_inside();
	std::cout << "--------------------------" << std::endl;
}

void GameProcess::SaveAll() {
	for (auto it : place)
		it->Save_inside(LogSingleton::Logfile);
	LogSingleton::Logfile << "--------------------------" << std::endl;
}

void GameProcess::Moving() {
	Personage *p;
	int num;
	int ind = 0;
	do {
		p = place[ind]->Pop_visitor();
		if (p) { // в локації ще хтось є
			num = rand() % std::size(place);
			place[num]->Add_visitor(p);
		}
		else
			ind++;
	} while (ind < std::size(place));
}