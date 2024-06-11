#ifndef MENU_H
#define MENU_H

#include "io_utils.h"

 // Forward declarations
class Player;
class Human;
class Computer;
class Game;

/**
 * @class Menu
 * @brief Manages the game menu and user choices.
 */
class Menu
{
private:
    // Enumeration for menu options
    enum class eOptions { HUMAN_VS_HUMAN = '1', HUMAN_VS_COMPUTER = '2', COMPUTER_VS_COMPUTER = '3', CONTINUE = '4', INSTRUCTION = '8', EXIT = '9' };

    // Constants for menu and instructions positions
    static constexpr int MENU_X = 35;
    static constexpr int MENU_Y = 8;
    static constexpr int INSTRUCTIONS_X = 25;
    static constexpr int INSTRUCTIONS_Y = 6;

    bool isGameOn;     ///< Flag indicating whether the game is ongoing.
    bool isExit;       ///< Flag indicating whether the user chose to exit.
    bool isInColor;    ///< Flag indicating whether the game is in color mode.

    char input;  ///< User input for menu choices.

    /**
     * @brief Prints the main menu options.
     */
    void printMenu() const;

    /**
     * @brief Prints game instructions.
     */
    void printInstructions() const;

    /**
     * @brief Loads the game with player instances and starts the game loop.
     * @param player1 The Player instance for player 1.
     * @param player2 The Player instance for player 2.
     * @param game The Game instance for managing the game flow.
     */
    void loadGame(Player* player1, Player* player2,const Game& game);

    /**
     * @brief Prints the exit message.
     */
    void printExit() const;


    /**
     * @brief Prompts the user to choose color mode for the game.
     */
    void chooseColors();

    /**
     * @brief resets the game before starting a new game.
     */
    void resetGame(const Player* player1, const Player* player2);

    /**
     * @brief Prompts the user to choose the level of the computer player
     */
    void chooseLevel(Player* player);

    /**
     * @brief Prints the levels options
     */
    void printLevels(int playerNum) const;

public:
    /**
     * @brief Constructor for the Menu class.
     * Initializes flags and menu input.
     */
    Menu() : isExit(false), isGameOn(false), input(0), isInColor(false) {}


    /**
     * @brief Handles user's menu choice and initiates corresponding actions.
     * @param player1 The Player instance for player 1.
     * @param player2 The Player instance for player 2.
     * @param game The Game instance for managing the game flow.
     */
    void chooseOption(Player* player1, Player* player2, const Game& game) ;

    /**
     * @brief Prints the game logo.
     */
    void printLogo() const;
};

#endif // !MENU_H