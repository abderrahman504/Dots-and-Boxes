#ifndef _CONSTANTS_
#define _CONSTANTS_
#include <windows.h>
#include <stdio.h>

#define MAX_NAME 30
//Constants related to drawing the grid.
#define VLine 186
#define HLine 205
#define SmallBox 254
#define BigBox 219
#define HLineWidth 4
//Constants related to starting a game.
#define MODE_1 1
#define MODE_2 2
//Constants for control messages.
#define MS_EXIT 0
#define MS_NEWGAME 1
#define MS_MENU 2

enum COLOUR{
    Black,
    Dark_blue,
    Dark_green, 
    Dark_cyan, 
    Dark_red, 
    Dark_pink, 
    Dark_yellow, 
    Pale_white, 
    Grey, 
    Blue, 
    Green, 
    Cyan, 
    Red, 
    Pink,
    Yellow, 
    White
};


void color_printf(char* str, int fore, int back)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, fore + 16*back);
    printf(str);
    SetConsoleTextAttribute(hConsole, White + 16*Black);
}

#endif