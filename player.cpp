#include "player.h"

extern HANDLE hStdOut;


Player::Player(int _drawOffset, bool& isInColor) : currBlock(isInColor)
{
	didLoose = false;
	shouldLock = false;
	drawOffset = _drawOffset * GameConfig::BOARD_DIFF;
	score = 0;

	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
		for (size_t j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			grid[i][j].ch = ' ';
			grid[i][j].color = GameConfig::BLACK;
		}

}


void Player::nextMove(const char& input, bool& isInColor)
{
	char charToDraw = ' ';
	GameConfig::eCommands direction = getDirection(input);

	currBlock.draw(charToDraw, drawOffset);

	currBlock.move(direction);
	if (!isValidMove(currBlock, direction))
	{
		currBlock.unMove(direction);
		if (direction != GameConfig::eCommands::DOWN && direction != GameConfig::eCommands::DROP)
		{
			currBlock.move(GameConfig::eCommands::DOWN);
			if (!isValidMove(currBlock, GameConfig::eCommands::DOWN))
				currBlock.unMove(GameConfig::eCommands::DOWN);
		}

		resetStep(direction);
	}

	if (currBlock.getShape() == GameConfig::eShapes::BOMB)
		charToDraw = '@';
	else
		charToDraw = '#';

	currBlock.draw(charToDraw, drawOffset);

	if (shouldLock)
	{
		if (currBlock.getShape() == GameConfig::eShapes::BOMB)
			explodeBomb();

		else
			lockBlock();
		shouldLock = false;
		handleFullLine();
		drawBoard();
		currBlock.reset(isInColor);
		getMoveByLevel();
	}
	else if (isDrop(input))
	{
		Sleep(10);
		nextMove(useDrop(), isInColor);
	}
}


void Player::explodeBomb()
{
	Point points[GameConfig::BLOCK_SIZE];
	currBlock.getPoints(points);
	int col, row, left, right, top, buttom;

	left = getLeftExplosionBound(points[0]);
	right = getRightExplosionBound(points[0]);
	top = getTopExplosionBound(points[0]);
	buttom = getButtomExplosionBound(points[0]);

	for (col = left; col <= right; col++)
	{
		for (row = top; row <= buttom; row++)
		{
			grid[col - 1][row - 1].ch = ' ';
			grid[col - 1][row - 1].color = GameConfig::BLACK;
		}
	}

	if (top != GameConfig::DEFAULT_Y + 1)
		handleBombAftermath(left, right, top);
}


void Player::handleBombAftermath(const int& left, const int& right, const int& top)
{
	
	for (size_t col = left; col < right; col++)
	{
		int row = top - 1;
		while (row > GameConfig::DEFAULT_Y)
		{
			if (grid[col - 1][row - 1].ch != ' ')
			{
				dropPoint(col, row, grid[col - 1][row - 1].ch, grid[col - 1][row - 1].color);
				grid[col - 1][row - 1].ch = ' ';
				grid[col - 1][row - 1].color = GameConfig::BLACK;
			}
			row--;
		}
	}
}


void Player::dropPoint(int x, int y, char ch, int color)
{
	while (y + 1 <= GameConfig::GAME_HEIGHT && grid[x - 1][y].ch == ' ')
		y++;

	grid[x - 1][y - 1].ch = ch;
	grid[x - 1][y - 1].color = color;
}


int Player::getLeftExplosionBound(const Point& bomb) const
{
	int leftBound = bomb.getX() - GameConfig::BOMB_RADIUS;

	if (leftBound > GameConfig::DEFAULT_Y)
		return leftBound;
	else
		return 1;
}


int Player::getRightExplosionBound(const Point& bomb) const
{
	int rightBound = bomb.getX() + GameConfig::BOMB_RADIUS;

	if (rightBound <= GameConfig::GAME_WIDTH)
		return rightBound;
	else
		return GameConfig::GAME_WIDTH;
}


int Player::getTopExplosionBound(const Point& bomb) const
{
	int topBound = bomb.getY() - GameConfig::BOMB_RADIUS;

	if (topBound > GameConfig::DEFAULT_Y)
		return topBound;
	else
		return 1;
}


int Player::getButtomExplosionBound(const Point& bomb) const
{
	int buttomBound = bomb.getY() + GameConfig::BOMB_RADIUS;

	if (buttomBound <= GameConfig::GAME_HEIGHT)
		return buttomBound;
	else
		return GameConfig::GAME_HEIGHT;
}


bool Player::isValidMove(const Block& block, const GameConfig::eCommands& direction)
{
	Point points[GameConfig::BLOCK_SIZE];
	block.getPoints(points);
	return isPosValid(points, direction);
}


bool Player::isPosValid(const Point* ptArr, const GameConfig::eCommands& direction)
{
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		if (ptArr[i].getY() <= GameConfig::DEFAULT_Y)
			return false;

		if (ptArr[i].getX() == 0 || ptArr[i].getX() == GameConfig::GAME_WIDTH + 1)
			return false;

		if (grid[ptArr[i].getX() - 1][ptArr[i].getY() - 1].ch != ' ')
		{
			if (direction == GameConfig::eCommands::DOWN || direction == GameConfig::eCommands::DROP)
			{
				shouldLock = true;
			}
			return false;
		}

		if ((ptArr[i].getY() == GameConfig::GAME_HEIGHT + 1))
		{
			shouldLock = true;
			return false;
		}
	}

	return true;
}


void Player::lockBlock()
{
	Point points[GameConfig::BLOCK_SIZE];
	currBlock.getPoints(points);
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		grid[points[i].getX() - 1][points[i].getY() - 1].ch = '#';
		grid[points[i].getX() - 1][points[i].getY() - 1].color = currBlock.getColor();
	}
}


void Player::handleFullLine()
{
	int read, write;
	read = write = GameConfig::GAME_HEIGHT;
	while (read >= 0)
	{
		if (!isFullLine(read))
		{
			copyLine(read, write);
			write--;
		}
		read--;
	}

	score += ((write + 1) * (write + 1)) * GameConfig::POINTS_PER_LINE;

	while (write >= 0)
	{
		resetLine(write);
		write--;
	}
}


void Player::resetLine(const int row)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		grid[i][row].ch = ' ';
	}
}


void Player::copyLine(const int read, const int write)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		grid[i][write] = grid[i][read];
	}
}


bool Player::isFullLine(const int row) const
{
	for (size_t col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		if (grid[col][row].ch == ' ')
			return false;
	}
	return true;
}


bool Player::isEmptyLine(const int row)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
		if (grid[i][row].ch != ' ')
			didLoose = true;

	return didLoose;
}


void Player::drawBoard() const
{

	gotoxy(GameConfig::MIN_X + drawOffset, GameConfig::MIN_Y - 3);
	std::cout << "SCORE: " << score;

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::MIN_X - 1 + drawOffset, row);
		std::cout << '|';
		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X + drawOffset, row);
		std::cout << '|';
	}

	for (int col = GameConfig::MIN_X - 1 + drawOffset;
		col <= GameConfig::GAME_WIDTH + GameConfig::MIN_X + drawOffset; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		std::cout << '-';
		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		std::cout << '-';
	}


	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (size_t j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			gotoxy(i + GameConfig::MIN_X + drawOffset, j + GameConfig::MIN_Y);
			SetConsoleTextAttribute(hStdOut, grid[i][j].color);
			std::cout << this->grid[i][j].ch;
		}
	}

	SetConsoleTextAttribute(hStdOut, GameConfig::WHITE);
}
