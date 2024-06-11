#ifndef BLOCK_H
#define BLOCK_H
#include "point.h"

class Human; // Forward declaration
class Computer; // Forward declaration

class Block
{
    // Array representing possible block orientations
    static constexpr int ORIENTATIONS[GameConfig::NUM_OF_ORIENTATIONS] = { 0, 1, 2, 3 };

    // Current block orientation
    int orientation;

    // Type of tetris shape
    GameConfig::eShapes shape;

    // Array of points representing the block
    Point points[GameConfig::BLOCK_SIZE];

    // Color of the block
    int color;

    // Private helper function to rotate the block
    void rotate(GameConfig::eCommands direction);

    // Private helper functions for specific shape rotations
    void rotateI();
    void rotateL();
    void rotateS();
    void rotateZ();
    void rotatePlus();
    void rotateReverseL();

    // Private helper functions for handling square and bomb "rotations"
    void updatePointsToCenterSquare();
    void updatePointsToCenterBomb();

    // Reset the block's properties
    void resetPoints();

    // Draw a random possible shape
    void drawRandomShape();

public:

    // Constructor: Initializes the block with default properties
    Block(bool& isInColor) : points() { reset(isInColor); }

    // Getter for block color
    int getColor() const { return color; }

    // Getter for block shape
    GameConfig::eShapes getShape() const { return shape; }

    // Setter for Orientation data member
    void setOrientation(const int newOrientation) { this->orientation = newOrientation; };

    // Reset the block to its default state
    void reset(bool& isInColor);

    // Draw the block on the screen
    void draw(const char& ch, const int& drawOffset) const;

    // Move the block based on the specified direction
    void move(GameConfig::eCommands direction);

    // Reverse a previous move based on the specified direction
    void unMove(GameConfig::eCommands direction);

    // Get an array of points representing the block
    void getPoints(Point* pointsArr) const;

    // Sets the points of a shape relativly to a given center coordinates
    void setPoints(const int x, const int y);
};

#endif // !BLOCK_H