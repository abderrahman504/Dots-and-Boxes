#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>



int gDifficulty[2]; // Contains height and width of the grid;
char gMode;

const char MENUTEXT[] = "\nWelcome to Dots and Boxes\n\
\n\
\t1-New Game\n\
\t2-Load Game\n\
\t3-Leaderboard\n\
\t4-Exit\n\
\n\
Select an option (for example, enter \"1\" to select \"New Game\")\n";

const char DIFFTEXTWIDTH[] = "\n\
Height is %d. Enter the width of the grid. It should be a number between 2 and 99:\n\
\t0-Back to menu\n\
\t1-Enter height again\n\n";

const char DIFFTEXTHEIGHT[] = "\n\
Enter the height of the grid. It should be a number between 2 and 99:\n\
\t0-Back to menu\n\n";

const char MODETEXT[] = "\n\
Select Game Mode:\n\
\t1-One player mode\n\
\t2-Two player mode\n\
\t3-Back\n\n";

const char invalidInput[] = "Invalid input. Please try again\n"; 
const char tooLongInput[] = "Your input was too long. Please try again.\n";

int load_menu();
static void draw_menu();
static int take_menu_input();
static int get_diff();
static void draw_height_selection();
static int take_height_input();
static void draw_width_selection();
static int take_width_input();
static void draw_mode_selection();
static int take_mode_input();
static void draw_saves_selection();
static int take_saves_input();
static void draw_leaderboard();

enum inputs{
    BackToMenu,
    New,
    Diff,
    Mode,
    Load,
    Leader,
    Exit,
    Invalid,
};

int load_menu()
{
    set_color(White, Black);
    int message, inputResult;
    start:
    draw_menu();
    inputResult = take_menu_input(); //Takes input when in the menu and will handle any invalid input. returns where to proceed in the menu.
    switchStart:
    switch (inputResult)
    {
        case BackToMenu:
            goto start;
        case New: //inputResult is New when the player has chosen difficulty and mode.
            message = MS_NEWGAME;
            break;
        case Diff: //inputResult is Diff when the player chooses the new game option.
            inputResult = get_diff();
            goto switchStart;
        case Mode:
            draw_mode_selection();
            inputResult = take_mode_input();
            goto switchStart;
        case Load:
            draw_saves_selection();
            inputResult = take_saves_input();
            goto switchStart;
        case Leader:
            draw_leaderboard();
            inputResult = BackToMenu;
            goto switchStart;
        case Exit:
            message = MS_EXIT;
            break;
    }
    return message;
    
}

static void draw_menu()
{
    system("cls");
    printf(MENUTEXT);
}

static int take_menu_input()
{
    char inputStr[3];
    while (1)
    {
        fgets(inputStr, 3, stdin);
        fflush(stdin);
        if(inputStr[0] == '\n')
        {
            draw_menu();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        if (inputStr[1] != '\n')
        {
            draw_menu();
            color_printf(tooLongInput, Red, Black);
            continue;
        }
        int input = inputStr[0]-'0';
        switch (input)
        {
            case 1:
                return Diff;
            case 2:
                return Load;
            case 3:
                return Leader;
            case 4:
                return Exit;
            default:
                draw_menu();
                color_printf(invalidInput, Red, Black);
        }
    }
}

int get_diff()
{
    h_start:
    draw_height_selection();
    gDifficulty[0] = take_height_input();
    if (gDifficulty[0] == 0)
    {
        return BackToMenu;
    }
    draw_width_selection();
    gDifficulty[1] = take_width_input();
    if (gDifficulty[1] == 0)
    {
        return BackToMenu;
    }
    if (gDifficulty[1] == 1)
    {
        goto h_start;
    }
    return Mode;
}

void draw_height_selection()
{
    system("cls");
    printf(DIFFTEXTHEIGHT);
}

int take_height_input()
{
    char inputStr[4] = {}; //Height and width values should not be bigger than 2 digits
    while (1)
    {
        fgets(inputStr, 4, stdin);
        fflush(stdin);
        if(inputStr[0] == '\n')
        {
            draw_height_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        if (inputStr[2] != '\n' && inputStr[2] != 0)
        {
            draw_height_selection();
            color_printf(tooLongInput, Red, Black);
            continue;
        }

        int height = 0;
        if (inputStr[0] < '0' || inputStr[0] > '9')
        {
            draw_height_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        height = height * 10 + (inputStr[0] - '0');
        if (inputStr[1] == '\n')
        {
            goto h_input_end;
        }
        if (inputStr[1] < '0' || inputStr[1] > '9')
        {
            draw_height_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        height = height * 10 + (inputStr[1] - '0');
        h_input_end:
        if (height < 2 && height != 0)
        {
            draw_height_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        return height;
    }
}

void draw_width_selection()
{
    system("cls");
    printf(DIFFTEXTWIDTH, gDifficulty[0]);
}

int take_width_input()
{
    char inputStr[4] = {}; //Height and width values should not be bigger than 2 digits
    while (1)
    {
        fgets(inputStr, 4, stdin);
        fflush(stdin);
        if(inputStr[0] == '\n')
        {
            draw_width_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        if (inputStr[2] != '\n' && inputStr[2] != 0)
        {
            draw_width_selection();
            color_printf(tooLongInput, Red, Black);
            continue;
        }

        int width = 0;
        if (inputStr[0] < '0' || inputStr[0] > '9')
        {
            draw_width_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        width = width * 10 + (inputStr[0] - '0');
        if (inputStr[1] == '\n')
        {
            goto w_input_end;
        }
        if (inputStr[1] < '0' || inputStr[1] > '9')
        {
            draw_width_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        width = width * 10 + (inputStr[1] - '0');
        w_input_end:
        return width;
    }
}
/*
int take_diff_input()
{
    char inputStr[3];
    while (1)
    {
        fgets(inputStr, 3, stdin);
        fflush(stdin);
        if(inputStr[0] == '\n')
        {
            draw_menu();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        if (inputStr[1] != '\n')
        {
            draw_diff_selection();
            color_printf(tooLongInput, Red, Black);
            continue;
        }
        int input = inputStr[0]-'0';
        switch (input)
        {
            case 1:
                gDifficulty = DIFF_EASY;
                return Mode;
            case 2:
                gDifficulty = DIFF_HARD;
                return Mode;
            case 3:
                return BackToMenu;
            default:
                draw_diff_selection();
                color_printf(invalidInput, Red, Black);
        }
    }
}
*/
void draw_mode_selection()
{
    system("cls");
    printf(MODETEXT);
}

int take_mode_input()
{
    char inputStr[3];
    while (1)
    {
        fgets(inputStr, 3, stdin);
        fflush(stdin);
        if(inputStr[0] == '\n')
        {
            draw_mode_selection();
            color_printf(invalidInput, Red, Black);
            continue;
        }
        if (inputStr[1] != '\n')
        {
            draw_mode_selection();
            color_printf(tooLongInput, Red, Black);
            continue;
        }
        int input = inputStr[0]-'0';
        switch (input)
        {
            case 1:
                gMode = MODE_1;
                return New;
            case 2:
                gMode = MODE_2;
                return New;
            case 3:
                return Diff;
            default:
                draw_mode_selection();
                color_printf(invalidInput, Red, Black);
        }
    }
}

void draw_saves_selection()
{
    system("cls");
    printf("This should show save file selection, but we haven't done that yet.\n");

}

int take_saves_input()
{
    char str[3];
    fgets(str, 3, stdin);
    fflush(stdin);
    return BackToMenu;
}

void draw_leaderboard()
{
    system("cls");
    printf("Here should be leaderboard stuff, but we haven't done that yet so meh.\n");
    printf("Press enter to return to menu.\n");
    char str[3];
    fgets(str, 3, stdin);
    fflush(stdin);
}