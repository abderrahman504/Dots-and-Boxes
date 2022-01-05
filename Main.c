#include "Game Loop.c"
#include "Menu.c"
#include "Constants.h"



int message = MS_NEWGAME;
char gDifficulty = DIFF_HARD;
char gMode = MODE_2;



int main()
{
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
            case MS_SAVES:
                //message = load_saves();
                break;
            case MS_LEADERBOARD:
                //message = load_leaderboard();
                break;
            case MS_EXIT:
                goto end;
            case -1:
                getchar();
                return 0;
            default:
                printf("Unidentified message value sent to main.\n");
                getchar(); //pausing the program with getchar().
                return 0;
        }
    }
    end:
    return 0;
}
