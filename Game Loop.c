#include <stdio.h>
#include <windows.h> // WinApi header
#include "Grid&Colors.h"


const unsigned char* GRID[20] = {};



int main()
{
    enum COLOUR fontColor = Cyan;
    enum COLOUR background = Black;
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,fontColor + 16*background);
    while (1)
    {
        unsigned char character;
        scanf("%d", &character);
        if (!character) break;
        fflush(stdin);
        fflush(stdout);
        printf("%c\n", character);
    }

    return 0;
}