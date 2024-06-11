#include "io_utils.h"

void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    std::cout << std::flush;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


void hideCursor()
{
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}


void clear_screen()
{
    system("cls");
}
