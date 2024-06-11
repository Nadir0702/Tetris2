#include "point.h"
#include "human.h"
#include "computer.h"

extern HANDLE hStdOut;

Point::Point(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
	diff_x = 0;
	diff_y = 1;
}


void Point::draw(const char& ch, const int& drawOffset, const int color) const
{
	
	if (this->y != 0)
	{
		SetConsoleTextAttribute(hStdOut, color);
		if(ch == ' ')
			SetConsoleTextAttribute(hStdOut, GameConfig::BLACK);
		gotoxy(this->x + (GameConfig::MIN_X - 1) + drawOffset, this->y + GameConfig::MIN_Y - 1);
		std::cout << ch;
		SetConsoleTextAttribute(hStdOut, GameConfig::WHITE);
	}
}


void Point::move(const GameConfig::eCommands direction)
{
	switch (direction)
	{
	case GameConfig::eCommands::LEFT:
		diff_x = -1;
		diff_y = 0;	
		break;
	case GameConfig::eCommands::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case GameConfig::eCommands::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case GameConfig::eCommands::UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case GameConfig::eCommands::DROP:
		diff_x = 0;
		diff_y = 1;
		break;
	default:
		diff_y = 0;
		diff_x = 0;
		break;
	}

	x += diff_x;
	y += diff_y;
}
