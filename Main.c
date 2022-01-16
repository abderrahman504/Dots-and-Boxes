#include <windows.h>
#include "Game Loop.c"
#include "Menu.c"
#include "Constants.h"



int message = MS_MENU;



int main()
{
    
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, White + 16*Black);
    while (1)
    {
        switch (message)
        {
            case MS_NEWGAME:
                message = load_game(gDifficulty,gMode);
                break;
            case MS_MENU:
                message = load_menu();
                break;
            case MS_EXIT:
                goto end;
            default:
                printf("Unidentified message value sent to main.\n");
                getchar(); //pausing the program with getchar().
                return 0;
        }
    }
    end:
    return 0;
}
