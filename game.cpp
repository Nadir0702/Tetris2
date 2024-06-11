#include "game.h"


void Game::run() const
{
	Menu menu;
	Player* player1 = nullptr;
	Player* player2 = nullptr;

	menu.printLogo();
	menu.chooseOption(player1, player2, *this);
}


void Game::playGame(Player& player1, Player& player2, bool& isGameOn,bool& isInColor) const
{
	player1.drawBoard();
	player2.drawBoard();
	player1.getMoveByLevel();
	player2.getMoveByLevel();

	while (!gameOver(player1, player2))
	{
		char input = GameConfig::NO_ACTION;
		if (_kbhit())
		{
			input = _getch();
			if (input == GameConfig::ESC)
				return;	
		}

		player1.nextMove(input, isInColor);
		player2.nextMove(input, isInColor);

		Sleep(500);
	}

	handleWinner(player1, player2, isGameOn, isInColor); 
}


void Game::handleWinner(const Player& player1, const Player& player2, bool& isGameOn, bool& isInColor) const
{
	int winner = 3;

	if (player1.getDidLoose())
		winner -= 1;
	if (player2.getDidLoose())
		winner -= 2;

	if (!winner)
	{
		if (player1.getScore() < player2.getScore())
			winner = 2;
		else if (player1.getScore() > player2.getScore())
			winner = 1;
	}

	printGameOver(winner);

	isGameOn = false;
	isInColor = false;
}


void Game::printGameOver(const int& winnerNumber) const
{
	int printY = GameConfig::MIN_Y + GameConfig::GAME_HEIGHT / 2 - 5;
	int printX = GameConfig::MIN_X + GameConfig::BOARD_DIFF / 2;

	gotoxy(printX, printY);
	std::cout << "\033[1;31mGAME OVER!\033[0m";
	printY += 2;

	if (winnerNumber)
	{
		gotoxy(printX - 2, printY);
		std::cout << "\033[1;32mPLAYER " << winnerNumber << " WIN!!!\033[0m";
	}
	else
	{
		gotoxy(printX - 2, printY);
		std::cout << "\033[1;34mIT'S A DRAW....\033[0m";
	}
	
	gotoxy(printX - 8, GameConfig::MIN_Y + GameConfig::GAME_HEIGHT - 5);
	std::cout << "Press any key to continue...";
	_getch();
}


bool Game::gameOver(Player& player1, Player& player2) const
{
	bool player1Lost, player2Lost;

	player1Lost = player1.isEmptyLine();
	player2Lost = player2.isEmptyLine();

	return player1Lost || player2Lost;
}
