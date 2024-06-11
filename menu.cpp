#include "menu.h"
#include "human.h"
#include "game.h"
#include "computer.h"
#include "player.h"


void Menu::chooseOption(Player* player1, Player* player2,const Game& game)
{

	while (!isExit)
	{
		printMenu();
		input = _getch();

		switch ((Menu::eOptions)input)
		{
		case Menu::eOptions::HUMAN_VS_HUMAN:
			resetGame(player1, player2);
			player1 = new Human(0, isInColor, GameConfig::keysP1);
			player2 = new Human(1, isInColor, GameConfig::keysP2);
			loadGame(player1, player2, game);
			break;
		case Menu::eOptions::HUMAN_VS_COMPUTER:
			resetGame(player1, player2);
			player1 = new Human(0, isInColor, GameConfig::keysP1);
			player2 = new Computer(1, isInColor);
			chooseLevel(player2);
			loadGame(player1, player2, game);
			break;
		case Menu::eOptions::COMPUTER_VS_COMPUTER:
			resetGame(player1, player2);
			player1 = new Computer(0, isInColor);
			player2 = new Computer(1, isInColor);
			chooseLevel(player1);
			chooseLevel(player2);
			loadGame(player1, player2, game);
			break;
		case Menu::eOptions::CONTINUE:
			if (isGameOn)
				loadGame(player1, player2, game);
			break;
		case Menu::eOptions::INSTRUCTION:
			clear_screen();
			printInstructions();
			break;
		case Menu::eOptions::EXIT:
			clear_screen();
			printExit();
			isExit = true;
			delete player1;
			delete player2;
			return;
			break;
		default:
			break;
		}

		clear_screen();
	}
}


void Menu::chooseLevel(Player* player)
{
	bool isValidInput = false;
	printLevels(player->getPlayerNumber());

	input = _getch();
	while (!isValidInput)
	{
		input = input - '0' - 1;
		if (input == (char)GameConfig::eLevel::NOVICE)
		{
			player->setLevel(GameConfig::eLevel::NOVICE);
			isValidInput = true;
		}
		else if (input == (char)GameConfig::eLevel::GOOD)
		{
			player->setLevel(GameConfig::eLevel::GOOD);
			isValidInput = true;
		}
		else if (input == (char)GameConfig::eLevel::BEST)
		{
			player->setLevel(GameConfig::eLevel::BEST);
			isValidInput = true;
		}
		else
			input = _getch();
	}

	clear_screen();
}


void Menu::printLevels(int playerNum) const
{
	int nemu_y = MENU_Y;

	gotoxy(MENU_X, nemu_y);
	std::cout << "Choose Level For Player #" << playerNum << ":" << std::endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (int)GameConfig::eLevel::NOVICE + 1 << ") NOVICE" << std::endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (int)GameConfig::eLevel::GOOD + 1 << ") GOOD" << std::endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (int)GameConfig::eLevel::BEST + 1 << ") BEST" << std::endl;
	nemu_y++;
}


void Menu::resetGame(const Player* player1, const Player* player2)
{
	chooseColors();
	isGameOn = true;
	delete player1;
	delete player2;
}


void Menu::chooseColors()
{
	int nemu_y = MENU_Y;
	char answer = 0;
	bool isValidInput = false;

	while (!isValidInput)
	{
		clear_screen();
		gotoxy(MENU_X, nemu_y);
		std::cout << "Would you like to play with Colors?";
		nemu_y += 2;

		gotoxy(MENU_X, nemu_y);
		std::cout << "	Y	/	N";
		
		answer = _getch();

		if (answer == 'y' || answer == 'Y') 
		{
			isInColor = true;
			isValidInput = true;
		}
			
		if (answer == 'n' || answer == 'N')
		{
			isInColor = false;
			isValidInput = true;
		}

		nemu_y = MENU_Y;
	}
	
	answer = 0;

	clear_screen();
}


void Menu::loadGame(Player* player1, Player* player2,const Game& game)
{
	clear_screen();
	game.playGame(*player1, *player2, isGameOn, isInColor);
}


void Menu::printExit() const
{
	gotoxy(MENU_X, MENU_Y);
	std::cout << "  *********************************" << std::endl;
	gotoxy(MENU_X, MENU_Y + 1);
	std::cout << "  * \033[1;31mTHANK\033[0m \033[1;32mYOU\033[0m \033[1;33mFOR\033[0m \033[1;34mPLAYING\033[0m \033[1;35mTETRIS!\033[0m *" << std::endl;
	gotoxy(MENU_X, MENU_Y + 2);
	std::cout << "  *********************************" << std::endl;
}


void Menu::printMenu() const
{
	int nemu_y = MENU_Y;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (char)Menu::eOptions::HUMAN_VS_HUMAN << ") Start a new game - Human vs Human" << std::endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (char)Menu::eOptions::HUMAN_VS_COMPUTER << ") Start a new game - Human vs Computer" << std::endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (char)Menu::eOptions::COMPUTER_VS_COMPUTER << ") Start a new game - Computer vs Computer" << std::endl;
	nemu_y++;

	if (isGameOn)
	{
		gotoxy(MENU_X, nemu_y);
		std::cout << "(" << (char)Menu::eOptions::CONTINUE << ") Continue a paused game" << std::endl;
		nemu_y++;
	}

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (char)Menu::eOptions::INSTRUCTION << ") Present instructions and keys" << std::endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	std::cout << "(" << (char)Menu::eOptions::EXIT << ") EXIT" << std::endl;
}


void Menu::printInstructions() const
{
	char keyPressed = 0;
	int instructions_y = INSTRUCTIONS_Y;

	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "In Tetris, your objective is to manipulate falling tetrominoes " << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "composed of four blocks each, to create solid horizontal lines " << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "at the bottom of the playing field." << std::endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "COMMAND\\KEY			PLYAER 1		PLAYER 2" << std::endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "LEFT				a / A			j / J" << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "RIGHT				d / D			l / L" << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "ROTATE clockwise		s / S			k / K" << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "ROTATE counterclockwise	w / W			i / I" << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "DROP				x / X			m / M" << std::endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "Clearing lines earns  points. Plan your moves strategically to avoid creating " << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "gaps in the stack, and aim for Tetrises(clearing four lines at once) " << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "The game ends if the stack reaches the top of the screen " << std::endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "Enjoy the timeless puzzle - solving challenge of Tetris!" << std::endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	std::cout << "Press ESC to go back to the Menu" << std::endl;


	while(keyPressed != GameConfig::ESC)
		if(_kbhit())
			keyPressed = _getch();

}


void Menu::printLogo() const
{
	char keyPressed = 0;

	std::cout << R"(

 /$$      /$$           /$$                                                     /$$              
| $$  /$ | $$          | $$                                                    | $$              
| $$ /$$$| $$  /$$$$$$ | $$  /$$$$$$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$        /$$$$$$    /$$$$$$ 
| $$/$$ $$ $$ /$$__  $$| $$ /$$_____/ /$$__  $$| $$_  $$_  $$ /$$__  $$      |_  $$_/   /$$__  $$
| $$$$_  $$$$| $$$$$$$$| $$| $$      | $$  \ $$| $$ \ $$ \ $$| $$$$$$$$        | $$    | $$  \ $$
| $$$/ \  $$$| $$_____/| $$| $$      | $$  | $$| $$ | $$ | $$| $$_____/        | $$ /$$| $$  | $$
| $$/   \  $$|  $$$$$$$| $$|  $$$$$$$|  $$$$$$/| $$ | $$ | $$|  $$$$$$$        |  $$$$/|  $$$$$$/
|__/     \__/ \_______/|__/ \_______/ \______/ |__/ |__/ |__/ \_______/         \___/   \______/ 
                                                                                                 
                                                                                                 
                                                                                                 
                   /$$$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$$  /$$$$$$  /$$$$$$                      
                  |__  $$__/| $$_____/|__  $$__/| $$__  $$|_  $$_/ /$$__  $$                     
                     | $$   | $$         | $$   | $$  \ $$  | $$  | $$  \__/                     
                     | $$   | $$$$$      | $$   | $$$$$$$/  | $$  |  $$$$$$                      
                     | $$   | $$__/      | $$   | $$__  $$  | $$   \____  $$                     
                     | $$   | $$         | $$   | $$  \ $$  | $$   /$$  \ $$                     
                     | $$   | $$$$$$$$   | $$   | $$  | $$ /$$$$$$|  $$$$$$/                     
                     |__/   |________/   |__/   |__/  |__/|______/ \______/                      
                                                                                                 
                                                                                                 
                                                                                                 
)";
	std::cout << "					Press any key to Start";
	_getch();
	clear_screen();
}
