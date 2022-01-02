#include "Game Loop.c"

#define MS_EXIT 0
#define MS_STARTGAME 1
#define MS_MENU 2
#define MS_SAVES 3
#define MS_LEADERBOARD 4

int message = MS_STARTGAME;



int main()
{
    while (1)
    {
        switch (message)
        {
            case MS_STARTGAME:
                message = load_game(1, 1);
                break;
            case MS_MENU:
                //message = load_menu();
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