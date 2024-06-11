#ifndef COMPUTER_H
#define COMPUTER_H
#include "block.h"
#include"menu.h"
#include "player.h"

class Computer : public Player
{
    int rotateNum; // Number of rotate moves the computer needs to do
    int numOfStepsLeft; // Number of steps left(positive)/right(negative) the computer needs to make
    GameConfig::eLevel level; // Difficulty level of the computer

    virtual GameConfig::eCommands getDirection(const char& input) override; // Get the computer direction
    virtual void resetStep(const GameConfig::eCommands& direction) override; // Reset a step that was undone
    virtual bool isDrop(const char& input) const override; // Checks if the block is ready to be dropped
    virtual const char useDrop() override { return GameConfig::NO_ACTION; }; // Make the computer use drop
    void drawPossibleLocation(const Block& tempBlock, const char ch); // Draws a possible block location given a possible move
    void calcNumOfDroppedLines(const Block& tempBlock, int& fullLinesCounter) const; // Calculates the number of dropped lines of a possible move
    bool isMoveBetter(const Block& tempBlock, int& maxFullLines, int& minHeight, int& minEmptyPoints) const; // Checks if the current move is better than the one previously saved
    bool isMoveBetter(const Block& tempBlock, int& explodedCounter) const;// Checks if the current move is better than the one previously saved for bombs
    void calcHighestPoint(const Block& tempBlock, int& currMinHeight) const; // calculates the highest point of the block in a possible move
    void calcNumOfEmptyPoints(const Block& tempBlock, int& emptyPointsCounter) const; // Calculates the number of emty points below the block in a possible move
    bool isPointsInBoard(Block& tempBlock); // Checks if all the points of the block are inside the game board
    void MakeBadMove(); // Make the computer do a random move
    void findBestMove(); // Calculates the the best possible move to do
    


public:

    // Constructor: Initializes the Computer Player with player input keys and draw offset
    Computer(int _drawOffset, bool& isInColor);

    // Makes the computer calculate his move depending on his level 
    virtual void getMoveByLevel() override;

    // Setter for the level data member
    virtual void setLevel(const GameConfig::eLevel _level) override { level = _level; }

};

#endif // !COMPUTER_H
