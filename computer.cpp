#include "computer.h"

extern HANDLE hStdOut;


Computer::Computer(int _drawOffset, bool& isInColor): Player(_drawOffset, isInColor)
{
	rotateNum = 0;
	numOfStepsLeft = 0;
	level = GameConfig::eLevel::BEST;
}


void Computer::resetStep(const GameConfig::eCommands& direction)
{
	if (GameConfig::eCommands::ROTATE_CLOCKWISE == direction)
		rotateNum++;
	else if (GameConfig::eCommands::LEFT == direction)
		numOfStepsLeft++;
	else if (GameConfig::eCommands::RIGHT == direction)
		numOfStepsLeft--;
}


bool Computer::isDrop(const char& input) const
{
	return (rotateNum == 0 && numOfStepsLeft == 0);
}


void Computer::getMoveByLevel()
{
	int randMove = -1;

	switch (level)
	{
	case GameConfig::eLevel::NOVICE:
		randMove = rand() % GameConfig::NOVICE_MISTAKE_CHANCE;
		break;
	case GameConfig::eLevel::GOOD:
		randMove = rand() % GameConfig::GOOD_MISTAKE_CHANCE;
		break;
	default:
		break;
	}

	if (randMove == GameConfig::BAD_MOVE)
		MakeBadMove();
	else
		findBestMove();

}


void Computer::MakeBadMove()
{
	rotateNum = rand() % GameConfig::NUM_OF_ORIENTATIONS;
	numOfStepsLeft = (rand() % GameConfig::GAME_WIDTH) + 1 - GameConfig::DEFAULT_X;
}


GameConfig::eCommands Computer::getDirection(const char& input)
{
	GameConfig::eCommands direction; 
	if (rotateNum > 0)
	{
		direction = GameConfig::eCommands::ROTATE_CLOCKWISE;
		rotateNum--;
	}
	else if (numOfStepsLeft > 0)
	{
		direction = GameConfig::eCommands::LEFT;
		numOfStepsLeft--;
	}
	else if (numOfStepsLeft < 0)
	{
		direction = GameConfig::eCommands::RIGHT;
		numOfStepsLeft++;
	}
	else
		direction = GameConfig::eCommands::DROP;

	return direction;
}


void Computer::findBestMove()
{
	Block tempBlock = currBlock;
	int maxExploded = -1;
	int maxFullLines = -1;
	int minHeight = GameConfig::GAME_HEIGHT;
	int minEmptyPoints = GameConfig::GAME_HEIGHT * GameConfig::GAME_WIDTH;

	for (size_t currOrientation = 0; currOrientation < GameConfig::NUM_OF_ORIENTATIONS; currOrientation++)
	{
		tempBlock.setOrientation(currOrientation);
		for (size_t col = 1; col <= GameConfig::GAME_WIDTH; col++)
		{
			tempBlock.setPoints(col, 1);
			if (isPointsInBoard(tempBlock))
			{
				drawPossibleLocation(tempBlock, '$');

				if (tempBlock.getShape() == GameConfig::eShapes::BOMB)
				{
					if (isMoveBetter(tempBlock, maxExploded))
						numOfStepsLeft = GameConfig::DEFAULT_X - col;
				}
				else if(isMoveBetter(tempBlock, maxFullLines, minHeight, minEmptyPoints))
				{
					rotateNum = currOrientation;
					numOfStepsLeft = GameConfig::DEFAULT_X - col;
				}

				drawPossibleLocation(tempBlock, ' ');
			}
		}
	}
}


bool Computer::isPointsInBoard(Block& tempBlock)
{
	Point points[GameConfig::BLOCK_SIZE];
	tempBlock.getPoints(points);

	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		if (points[i].getY() <= GameConfig::DEFAULT_Y)
		{
			tempBlock.move(GameConfig::eCommands::DOWN);
			tempBlock.getPoints(points);
			i = 0;
		}
	}

	while (isPosValid(points, GameConfig::eCommands::DOWN))
		for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
			points[i].setY(points[i].getY() + 1);
		
	if (!getShouldLock())
		return false;

	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		points[i].setY(points[i].getY() - 1);
		if (points[i].getY() <= GameConfig::DEFAULT_Y)
			return false;
	}
		
	tempBlock.setPoints(points[0].getX(), points[0].getY());
	
	setShouldLock(false);
	return true;
}


bool Computer::isMoveBetter(const Block& tempBlock, int& maxExploded) const
{
	Point points[GameConfig::BLOCK_SIZE];
	tempBlock.getPoints(points);
	bool betterMove = false;
	int col, row, left, right, top, buttom, explodedCounter = 0;

	left = getLeftExplosionBound(points[0]);
	right = getRightExplosionBound(points[0]);
	top = getTopExplosionBound(points[0]);
	buttom = getButtomExplosionBound(points[0]);

	for (col = left; col <= right; col++)
	{
		for (row = top; row <= buttom; row++)
		{
			if (grid[col - 1][row - 1].ch != ' ')
				explodedCounter++;
		}
	}

	if (maxExploded < explodedCounter)
	{
		maxExploded = explodedCounter;
		return true;
	}
	else
		return false;
}


bool Computer::isMoveBetter(const Block& tempBlock, int& maxFullLines, int& minHeight, int& minEmptyPoints) const
{
	int fullLinesCounter = 0;
	int currMinHeight;
	int emptyPointsCounter = 0;
	bool betterMove = false;

	calcNumOfDroppedLines(tempBlock, fullLinesCounter);
	calcHighestPoint(tempBlock, currMinHeight);
	calcNumOfEmptyPoints(tempBlock, emptyPointsCounter);

	if (maxFullLines > fullLinesCounter)
		betterMove = false;
	else if (maxFullLines < fullLinesCounter)
	{
		maxFullLines = fullLinesCounter;
		minHeight = currMinHeight;
		minEmptyPoints = emptyPointsCounter;
		betterMove = true;
	}
	else
	{
		if (minHeight > currMinHeight)
			betterMove = false;
		else if (minHeight < currMinHeight)
		{
			maxFullLines = fullLinesCounter;
			minHeight = currMinHeight;
			minEmptyPoints = emptyPointsCounter;
			betterMove = true;
		}
		else
		{
			if (minEmptyPoints > emptyPointsCounter)
			{
				maxFullLines = fullLinesCounter;
				minHeight = currMinHeight;
				minEmptyPoints = emptyPointsCounter;
				betterMove = true;
			}
			else
				betterMove = false;
		}
	}
	return betterMove;
}


void Computer::calcNumOfEmptyPoints(const Block& tempBlock,int& emptyPointsCounter) const
{
	Point points[GameConfig::BLOCK_SIZE];
	tempBlock.getPoints(points);
	int row;
	bool wasColChecked = false;

	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (points[j].getX() == points[i].getX())
			{
				wasColChecked = true;
				break;
			}
		}
		row = points[i].getY();
		while (row < GameConfig::GAME_HEIGHT && !wasColChecked)
		{
			if (grid[points[i].getX() - 1][row].ch == ' ')
				emptyPointsCounter++;
			else
				wasColChecked = true;

			row++;
		}
		wasColChecked = false;
	}
}


void Computer::calcHighestPoint(const Block& tempBlock, int& currMinHeight) const
{
	Point points[GameConfig::BLOCK_SIZE];
	tempBlock.getPoints(points);

	currMinHeight = points[0].getY();
	for (size_t i = 1; i < GameConfig::BLOCK_SIZE; i++)
		if (currMinHeight > points[i].getY())
			currMinHeight = points[i].getY();
}


void Computer::calcNumOfDroppedLines(const Block& tempBlock, int& fullLinesCounter) const
{
	Point points[GameConfig::BLOCK_SIZE];
	tempBlock.getPoints(points);

	for (size_t i = points[0].getY() - 2; i <= points[0].getY() + 2; i++)
	{
		if (i == GameConfig::GAME_HEIGHT + 1)
			return;

		if (isFullLine(i - 1))
			fullLinesCounter++;
	}
}


void Computer::drawPossibleLocation(const Block& tempBlock, const char ch)
{
	Point points[GameConfig::BLOCK_SIZE];
	tempBlock.getPoints(points);

	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		grid[points[i].getX() - 1][points[i].getY() - 1].ch = ch;
		if (ch == ' ')
			grid[points[i].getX() - 1][points[i].getY() - 1].color = GameConfig::BLACK;
		else
			grid[points[i].getX() - 1][points[i].getY() - 1].color = tempBlock.getColor();
	}
}
