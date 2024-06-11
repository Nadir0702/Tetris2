#include "game.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void main()
{	
	srand(time(NULL));
	Game().run();

	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
}
