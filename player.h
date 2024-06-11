#ifndef PLAYER_H
#define PLAYER_H
#include "block.h"
#include"menu.h"


class Player
{
    
    bool didLoose; // Flag indicating whether the player has lost
    bool shouldLock; // Flag indicating whether the block should be locked in place
    int drawOffset; // Offset used for drawing on the screen
    int score; // Player's score
    struct PIXEL // Struct holding a char and a color
    {
        char ch;
        int color;
    };

    virtual GameConfig::eCommands getDirection(const char& input) = 0; // Get the player's input direction
    virtual void resetStep(const GameConfig::eCommands& direction) { }; // Reset a step that was undone
    bool isValidMove(const Block& block, const GameConfig::eCommands& direction); // Check if a move is valid for the current block
    void lockBlock(); // Lock the current block in place 
    void handleFullLine(); // Handle the removal of full lines and update the score 
    void resetLine(const int row); // Reset a line by clearing it
    void copyLine(const int read, const int write); // Copy a line from one row to another
    virtual bool isDrop(const char& input) const = 0; // Checks if the block is ready to be dropped
    virtual const char useDrop() = 0; // Make the Player use drop
    void explodeBomb(); // Explodes the bomb block 
    void handleBombAftermath(const int& left, const int& right, const int& top); // Handles the bombs explosion aftermath
    void dropPoint(int x, int y, char ch, int color); // Moves a point down antil it reaches another point or the board floor


protected:

    Block currBlock; // Current block in play
    PIXEL grid[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT]; // Game grid representing the play area

    // Constructor: Initializes the Player with player input keys and draw offset
    Player(int _drawOffset, bool& isInColor);

    bool isPosValid(const Point* ptArr, const GameConfig::eCommands& direction); // Check if the position is valid for the block
    bool isFullLine(const int row) const; // Check if a line is full

    // Get the bombs explosions dimentions 
    int getLeftExplosionBound(const Point& bomb) const;
    int getRightExplosionBound(const Point& bomb) const;
    int getTopExplosionBound(const Point& bomb) const;
    int getButtomExplosionBound(const Point& bomb) const;

    // Setter for shouldLock flag
    void setShouldLock(bool shouldLock) { this->shouldLock = shouldLock; }

public:

    // Virtual destructor of Player
    virtual ~Player() {};

    // Getter for didLoose flag
    bool getDidLoose() const { return didLoose; }

    // Getter for the player's score
    int getScore() const { return score; }

    // Getter for the player's offSet
    int getPlayerNumber() const { return (drawOffset / GameConfig::BOARD_DIFF) + 1; }

    // Getter for shouldLock flag
    bool getShouldLock() const { return shouldLock; }   

    // Process the player's input and update the game state
    void nextMove(const char& input, bool& isInColor);

    // Check if a line is empty
    bool isEmptyLine(const int row = 0);

    // Makes the player calculate his move depending on his level
    virtual void getMoveByLevel() { };

    // Setter for the level data member
    virtual void setLevel(const GameConfig::eLevel _level) { };

    // Draw the game board on the screen
    void drawBoard() const;

};

#endif // !PLAYER_H

