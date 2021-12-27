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
                load_game(1, 1);
                break;
            case MS_MENU:
                //load_menu();
                break;
            case MS_SAVES:
                //load_saves();
                break;
            case MS_LEADERBOARD:
                //load_leaderboard();
                break;
            case MS_EXIT:
                goto end;
        }
    }


    end:
    return 0;
}