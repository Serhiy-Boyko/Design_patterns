#include <time.h>
#include "GameProcess.h"

int main()
{
	srand(time(0));
	// ініціалізуємо тут, інакше дестроєр не спрацює
	LogSingleton *p = &LogSingleton::getInstance();
	GameProcess game;
	game.Init();
	game.Accept_all_visitors();
	game.PrintAll();
	game.SaveAll();
	game.Moving();
	game.Accept_all_visitors();
	game.PrintAll();
	game.SaveAll();
	//game.Moving();
	//game.Accept_all_visitors();
	//game.PrintAll();
	//game.SaveAll();

	system("pause");
	return 0;
}