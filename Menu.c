#include "Constants.h"

const char* MENUTEXT = "\nWelcome to Dots and Boxes\n\
\n\
\t1-New Game\n\
\t2-Load Game\n\
\t3-Leaderboard\n\
\t4-Exit\n\
\n\
Select an option (for example, enter \"1\" to select \"New Game\")\n";

int load_menu();
static void draw_menu();
static int take_menu_input();


int load_menu()
{
    int message;
    draw_menu();
    while(1)
    {
        int inputResult = take_menu_input();
        switch (inputResult)
        {
            case 0:
                message = MS_EXIT;
                goto end;
        }
    }

    end:
    return MS_EXIT;
    
}

static void draw_menu()
{
    printf(MENUTEXT);
}

static take_menu_input()
{
    return 0;
}
