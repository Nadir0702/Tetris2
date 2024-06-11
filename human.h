#ifndef HUMAN_H
#define HUMAN_H
#include "block.h"
#include"menu.h"
#include "player.h"

class Human : public Player
{
    const char* keys; // Array of keys for player input

    virtual GameConfig::eCommands getDirection(const char& input); // Get the player's input direction
    virtual bool isDrop(const char& input) const override; // Checks if the block is ready to be dropped
    virtual const char useDrop() override { return keys[(int)GameConfig::eCommands::DROP]; }; // Make the Player use drop

public:

    // Constructor: Initializes the Human game with player input keys and draw offset
    Human(int _drawOffset, bool& isInColor, const char* _keys) : Player(_drawOffset, isInColor) { keys = _keys; };

    // Gets the key in the given index of the human keys array
    char getKey(const int index) const { return keys[index]; } ;

};

#endif // !HUMAN_H