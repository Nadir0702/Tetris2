#ifndef GAME_H
#define GAME_H

#include "human.h"
#include "Player.h"
#include "menu.h"

 /**
  * @class Game
  * @brief Manages the flow and rules of the Tetris game.
  */
class Game
{
private:
    /**
     * @brief Checks if the game is over.
     * @param player1 The Player instance for player 1.
     * @param player2 The Player instance for player 2.
     * @return True if the game is over, false otherwise.
     */
    bool gameOver(Player& player1, Player& player2) const;

    /**
     * @brief Handles the winner and game over conditions.
     * @param player1 The Player instance for player 1.
     * @param player2 The Player instance for player 2.
     * @param isGameOn Reference to a boolean indicating whether the game is still on.
     * @param isInColor Reference to a boolean indicating whether the game is in color mode.
     */
    void handleWinner(const Player& player1, const Player& player2, bool& isGameOn, bool& isInColor) const;

    /**
     * @brief Prints the game over message with the winner's number.
     * @param winnerNumber The number of the winning player.
     */
    void printGameOver(const int& winnerNumber) const;

public:
    /**
     * @brief Runs the Tetris game.
     */
    void run() const;

    /**
     * @brief Plays a single game round between two players.
     * @param player1 The Player instance for player 1.
     * @param player2 The Player instance for player 2.
     * @param isGameOn Reference to a boolean indicating whether the game is still on.
     * @param isInColor Reference to a boolean indicating whether the game is in color mode.
     */
    void playGame(Player& player1, Player& player2, bool& isGameOn, bool& isInColor) const;
};

#endif // GAME_H