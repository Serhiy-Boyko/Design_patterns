#pragma once
#include "Location.h"

class Game;

class GameDestroyer {
	Game *p_instance;
public:
	void initialize(Game* p) { p_instance = p; }
	~GameDestroyer();
};

class Game {
	static Game *p_instance;
	static GameDestroyer destroyer;

	Location *place[3] = { Castle::getInstance(), Forest::getInstance(),
		Field::getInstance() };
protected:
	static std::ofstream Logfile;

	Game() { Logfile << "Start of new game: " << std::endl; }

	Game(const Game&) = delete;
	Game &operator=(Game&) = delete;

	~Game() {
		Logfile << "End of game " << std::endl;
		Logfile << "==========================" << std::endl;
		Logfile.close();
	}
public:
	void Init();
	void Accept_all_visitors();
	void PrintAll();
	void SaveAll();
	void Moving();

	static Game &getInstance() {
		if (!p_instance) {
			p_instance = new Game();
			destroyer.initialize(p_instance);
		}
		return *p_instance;
	}

	friend class GameDestroyer;
};

std::ofstream Game::Logfile("Logfile.txt", std::ios::app);
Game *Game::p_instance = nullptr;
GameDestroyer Game::destroyer;

GameDestroyer::~GameDestroyer() {
	delete p_instance;
}

void Game::Init() {
	place[0]->Add_visitor(Factory(magic, "Alex"));
	place[0]->Add_visitor(Factory(magic, "Borys"));
	place[1]->Add_visitor(Factory(warrior, "Casima"));
	place[1]->Add_visitor(Factory(warrior, "Dana"));
	place[2]->Add_visitor(Factory(gnom, "Egor"));
	place[2]->Add_visitor(Factory(gnom, "Fedir"));
}

void Game::Accept_all_visitors() {
	for (auto it : place)
		it->Accept_visitors();
}

void Game::PrintAll() {
	for (auto it : place)
		it->Print_inside();
	std::cout << "--------------------------" << std::endl;
}

void Game::SaveAll() {
	for (auto it : place)
		Game::Logfile << it;
	Game::Logfile << "--------------------------" << std::endl;
}

void Game::Moving() {
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