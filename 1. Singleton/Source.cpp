﻿#include <time.h>
#include "Game.h"

int main()
{
	srand(time(0));
	// ініціалізуємо тут, інакше дестроєр не спрацює
	Game *mygame = &Game::getInstance();
	mygame->Init(); // активізуємо 6 гравців (по 2 на локацію)
	mygame->Accept_all_visitors();
	mygame->PrintAll();
	mygame->SaveAll();
	mygame->Moving();
	mygame->Accept_all_visitors();
	mygame->PrintAll();
	mygame->SaveAll();
	//mygame->Moving();
	//mygame->Accept_all_visitors();
	//mygame->PrintAll();
	//mygame->SaveAll();

	system("pause");
	return 0;
}