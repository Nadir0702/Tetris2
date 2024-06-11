#include "block.h"
#include "human.h"
#include "computer.h"


void Block::resetPoints()
{
	Point originPoint;
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
		points[i] = originPoint;
}


void Block::drawRandomShape()
{
	int randNum = rand();
	if (randNum % 20 == 0)
		shape = GameConfig::eShapes::BOMB;
	else
		shape = (GameConfig::eShapes)(randNum % (GameConfig::numOfShapes - 1));
}


void Block::reset(bool& isInColor) 
{
	drawRandomShape();
	orientation = 0;

	resetPoints(); 
	switch (shape)
	{
	case GameConfig::eShapes::I:
		points[0].move(GameConfig::eCommands::DOWN);
		points[2] = points[0];
		points[2].move(GameConfig::eCommands::DOWN);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::DOWN);
		color = GameConfig::CYAN;
		break;
	case GameConfig::eShapes::L:
		points[0].move(GameConfig::eCommands::DOWN);
		points[2] = points[0];
		points[2].move(GameConfig::eCommands::DOWN);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::RIGHT);
		color = GameConfig::ORANGE;
		break;
	case GameConfig::eShapes::Z:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::LEFT);
		points[3] = points[1];
		points[3].move(GameConfig::eCommands::RIGHT);
		color = GameConfig::RED;
		break;
	case GameConfig::eShapes::S:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::RIGHT);
		points[3] = points[1];
		points[3].move(GameConfig::eCommands::LEFT);
		color = GameConfig::GREEN;
		break;
	case GameConfig::eShapes::PLUS:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::LEFT);
		points[3].move(GameConfig::eCommands::RIGHT);
		color = GameConfig::MAGENTA;
		break;
	case GameConfig::eShapes::SQUARE:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::RIGHT);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::DOWN);
		color = GameConfig::YELLOW;
		break;
	case GameConfig::eShapes::REVERSEL:
		points[0].move(GameConfig::eCommands::DOWN);
		points[2] = points[0];
		points[2].move(GameConfig::eCommands::DOWN);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::LEFT);
		color = GameConfig::BLUE;
		break;
	case GameConfig::eShapes::BOMB:
		color = GameConfig::GREY;
	default:
		break;
	}
	
	if (!isInColor)
		color = GameConfig::WHITE;
}


void Block::unMove(GameConfig::eCommands direction)
{
	switch (direction)
	{
	case GameConfig::eCommands::DROP:
		move(GameConfig::eCommands::UP);
		break;
	case GameConfig::eCommands::DOWN:
		move(GameConfig::eCommands::UP);
		break;
	case GameConfig::eCommands::UP:
		move(GameConfig::eCommands::DOWN);
		break;
	case GameConfig::eCommands::LEFT:
		move(GameConfig::eCommands::RIGHT);
		break;
	case GameConfig::eCommands::RIGHT:
		move(GameConfig::eCommands::LEFT);
		break;
	case GameConfig::eCommands::ROTATE_CLOCKWISE:
		move(GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE);
		break;
	case GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE:
		move(GameConfig::eCommands::ROTATE_CLOCKWISE);
		break;
	default:
		break;
	}
}


void Block::getPoints(Point* pointsArr) const
{
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		pointsArr[i].setX(points[i].getX());
		pointsArr[i].setY(points[i].getY());
	}
}


void Block::draw(const char& ch, const int& drawOffset) const
{
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
		points[i].draw(ch, drawOffset, color);
}


void Block::move(GameConfig::eCommands direction)
{
	if (direction == GameConfig::eCommands::ROTATE_CLOCKWISE || direction == GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE)
		rotate(direction);
	else
		for (int i = 0; i < GameConfig::BLOCK_SIZE; i++)
			points[i].move(direction);
}


void Block::setPoints(const int x, const int y)
{
	this->points[0].setX(x);
	this->points[0].setY(y);
	rotate(GameConfig::eCommands::STAY);
}


void Block::rotate(GameConfig::eCommands direction)
{
	if (direction == GameConfig::eCommands::ROTATE_CLOCKWISE)
		orientation = (orientation + 1) % 4;
	if (direction == GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE)
		orientation = (orientation + 3) % 4;

	switch (shape)
	{
	case GameConfig::eShapes::I:
		rotateI();
		break;
	case GameConfig::eShapes::L:
		rotateL();
		break;
	case GameConfig::eShapes::Z:
		rotateZ();
		break;
	case GameConfig::eShapes::S:
		rotateS();
		break;
	case GameConfig::eShapes::PLUS:
		rotatePlus();
		break;
	case GameConfig::eShapes::REVERSEL:
		rotateReverseL();
		break;
	case GameConfig::eShapes::SQUARE:
		updatePointsToCenterSquare();
		break;
	case GameConfig::eShapes::BOMB:
		updatePointsToCenterBomb();
		break;
	default:
		break;
	}
}


void Block::updatePointsToCenterBomb()
{
	for (size_t i = 1; i < GameConfig::BLOCK_SIZE; i++)
		points[i] = points[0];
}


void Block::updatePointsToCenterSquare()
{
	points[1].setX(points[0].getX());
	points[1].setY(points[0].getY() + 1);
	points[2].setX(points[0].getX() + 1);
	points[2].setY(points[0].getY());
	points[3].setX(points[0].getX() + 1);
	points[3].setY(points[0].getY() + 1);
}


void Block::rotatePlus()
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY());
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY());
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() - 1);
		break;
	default:
		break;
	}
}


void Block::rotateI()
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() + 2);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 2);
		points[3].setY(points[0].getY());
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() - 2);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 2);
		points[3].setY(points[0].getY());
		break;
	default:
		break;
	}
}


void Block::rotateL()
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	default:
		break;
	}
}


void Block::rotateS()
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	default:
		break;
	}
}


void Block::rotateZ()
{
		switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	default:
		break;
	}
}


void Block::rotateReverseL()
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	default:
		break;
	}
}
