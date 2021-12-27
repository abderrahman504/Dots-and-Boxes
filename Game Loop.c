#include <stdio.h>
#include <windows.h> // WinApi header
#include "Grid&Colors.h"


void color_printf(char *str, int fore, int back);
int load_game(int difficulty, int gameMode);



const char grid2x2[5][14] = {
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'}, 
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'}, 
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'}}; 
const char grid5x5[11][29] = {
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'},
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'},
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'},
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'},
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'},
    {'\t', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, ' ', BigBox, BigBox, ' ', VLine, '\n', '\0'},
    {'\t', SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, HLine, HLine, HLine, HLine, SmallBox, '\n', '\0'}};



int load_game(int difficulty, int game_mode)
{
    
    return 0;
}



void color_printf(char* str, int fore, int back)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, fore + 16*back);
    printf(str);
    SetConsoleTextAttribute(hConsole, White + 16*Black);
}