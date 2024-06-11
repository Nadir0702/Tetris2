#ifndef POINT_H
#define POINT_H

#include "gameConfig.h"

class Human; // Forward declaration

class Point
{
    mutable int x;
    int y;
    int diff_x;
    int diff_y;

public:

    // Constructor with default values
    Point(int _x = GameConfig::DEFAULT_X, int _y = GameConfig::DEFAULT_Y);

    // Draw the point on the screen
    void draw(const char& ch, const int& drawOffset, const int color) const;

    // Move the point based on the specified direction
    void move(const GameConfig::eCommands direction);

    // Setter for X coordinate
    void setX(const int x) { this->x = x; }

    // Setter for Y coordinate
    void setY(const int y) { this->y = y; }

    // Getter for X coordinate
    int getX() const { return x; } 

    // Getter for Y coordinate
    int getY() const { return y; }
};

#endif // !POINT_H