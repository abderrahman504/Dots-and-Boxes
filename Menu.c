#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>



char gDifficulty;
char gMode;

const char MENUTEXT[150] = "\nWelcome to Dots and Boxes\n\
\n\
\t1-New Game\n\
\t2-Load Game\n\
\t3-Leaderboard\n\
\t4-Exit\n\
\n\
Select an option (for example, enter \"1\" to select \"New Game\")\n";

const char DIFFTEXT[60] = "\n\
Select difficulty:\n\
\t1-Beginner\n\
\t2-Expert\n\
\t3-Back to menu\n\n";

const char MODETEXT[70] = "\n\
Select Game Mode:\n\
\t1-One player mode\n\
\t2-Two player mode\n\
\t3-Back\n\n";

const char invalidInput[40] = "Invalid input. Please try again\n"; 
const char tooLongInput[44] = "Your input was too long. Please try again.\n";

int load_menu();
static void draw_menu();
static int take_menu_input();
static void draw_diff_selection();
static int take_diff_input();
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
            draw_diff_selection();
            inputResult = take_diff_input();
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

void draw_diff_selection()
{
    system("cls");
    printf(DIFFTEXT);
}

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
            draw_menu();
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