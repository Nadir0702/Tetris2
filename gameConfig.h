#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include "io_utils.h"


class GameConfig
{
public:

    // Number of keys for each player
    static constexpr char NUM_OF_KEYS = 5;

    // Enum representing the difficulty levels of the computer player
    enum class eLevel { NOVICE, GOOD, BEST };

    // Enum representing different player commands
    enum class eCommands { LEFT, RIGHT, ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE, DROP, DOWN, UP, STAY };

    // Enum representing different tetris shapes
    enum class eShapes { I, L, Z, S, PLUS, SQUARE, REVERSEL, BOMB };

    // Keys for player 1 and player 2
    static constexpr char keysP1[NUM_OF_KEYS] = { 'a', 'd', 's', 'w', 'x' };
    static constexpr char keysP2[NUM_OF_KEYS] = { 'j', 'l', 'k', 'i', 'm' };

    // Special keys
    static constexpr char ESC = 27;
    static constexpr char NO_ACTION = -1;

    // Number of different tetris shapes
    static constexpr int numOfShapes = 8;

    // The bomb radius
    static constexpr char BOMB_RADIUS = 4;

    // Game board dimensions
    static constexpr int GAME_WIDTH = 12;
    static constexpr int GAME_HEIGHT = 18;

    // Minimum coordinates for the game board
    static constexpr int MIN_X = 10;
    static constexpr int MIN_Y = 5;

    // Board difference for rendering
    static constexpr int BOARD_DIFF = 50;

    // Size of each tetris block
    static constexpr int BLOCK_SIZE = 4;
    static constexpr int NUM_OF_ORIENTATIONS = 4;

    // Default coordinates for center points of new blocks
    static constexpr int DEFAULT_Y = 0;
    static constexpr int DEFAULT_X = 6;

    // Odds of making a bad move for each difficulty level
    static constexpr int BAD_MOVE = 3;
    static constexpr int NOVICE_MISTAKE_CHANCE = 5;
    static constexpr int GOOD_MISTAKE_CHANCE = 10;


    // Difference between lowercase and uppercase ASCII values
    static constexpr int LOWER_UPPER_DIFF = 32;

    // Points earned per cleared line
    static constexpr int POINTS_PER_LINE = 10;

    // Color codes for different tetris block colors
    static const int RED = FOREGROUND_RED | BACKGROUND_RED;
    static const int GREEN = FOREGROUND_GREEN | BACKGROUND_GREEN;
    static const int BLUE = FOREGROUND_BLUE | BACKGROUND_BLUE;
    static const int ORANGE = FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN;
    static const int CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_BLUE;
    static const int MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE;
    static const int YELLOW = ORANGE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
    static const int GREY = 0 | BACKGROUND_INTENSITY | FOREGROUND_RED;
    static const int WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    static const int BLACK = 0;
};

#endif // !GAMECONFIG_H