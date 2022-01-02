#include <stdio.h>
#include <windows.h> // WinApi header
#include <stdlib.h>
#include "Grid&Colors.h"
#include "Menu.c"
#define MAX_NAME 50
#define GRID_SMALL 2
#define GRID_LARGE 5
#define MODE_1 1
#define MODE_2 2

struct player
{
    int score;
    char name[MAX_NAME];
    int linesDrawn;
};

int load_game(int difficulty, char game_Mode);
int set_grid(int difficulty);
void set_mode(char game_mode);
void reset_stats();
void reset_player(struct player player);
void update_stats();
void update_screen();
void take_input();
void send_message();

void color_printf(char *str, int fore, int back);


//game stats
struct player player1; //Structure that contains player 1's stats.
struct player player2; //Structure that contains player 2's stats.
char** gameGrid; //The grid of the game.
char gameMode;
int gridSize;
int turn = 0;
int linesRemaining;
double gameTime; 
char** lines; //This is a 2d array that stores the state of all lines in the game.

int load_game(int difficulty, char game_mode)
{
    int err = 0;
    struct player playingPlayer = player1;

    err = set_grid(difficulty);
    if (err == -1)
    {
        getchar();
        return -1;
    }
    set_mode(game_mode);
    reset_stats();
    update_stats();
    update_screen();
    take_input();

    printf("About to end execution.");
    getchar();
    return 0;
}



//Determines the size of the grid based on the difficulty then constructs the grid that will be drawn.
//Also sets the lines 2d array to all zeroes.
int set_grid(int difficulty)
{
    switch (difficulty)
    {
        case DIFF_EASY:
            gridSize = GRID_SMALL;
            break;
        case DIFF_HARD:
            gridSize = GRID_LARGE;
            break;
        default:
            printf("Error at set_grid(). Unexpected value for difficulty.\n");
            getchar(); //Pausing execution with getchar().
            fflush(stdin);
    }
    gameGrid = (char**) malloc((2*gridSize+1)*sizeof(char*));
    if (gameGrid == NULL)
    {
        printf("Could not allocate memory for Gamegrid.\n");
        return -1;
    }
    lines = (char**) malloc((2*gridSize+1)*sizeof(char*));
    if (lines == NULL)
    {
        printf("Could not allocate memory for lines.\n");
        return -1;
    }
    for (int i=0; i<2*gridSize+1; i++)
    {
        char* row = (char*) malloc((3+gridSize*(HLineWidth+1))*sizeof(char));
        if (row == NULL)
        {
            printf("Could not allocate memory for a row in gameGrid.\n");
            return -1;
        }
        switch (i%2)
        {
            case 0:
            //Setting a row in gameGrid.
                for (int j=0; j<gridSize; j++)
                {
                    row[5*j] = SmallBox;
                    for (int k=1; k<=HLineWidth; k++) row[5*j+k] = ' ';
                }
                row[gridSize*(HLineWidth+1)] = SmallBox;
            //Setting a row in lines.
                char* lineRow = (char*) malloc(gridSize*sizeof(char));
                for (int j=0; j<gridSize; j++) lineRow[j] = 0;
                lines[i] = lineRow;
                break;
            case 1:
            //Setting a row in gameGrid.
                for (int j=0; j<gridSize*(HLineWidth+1)+1; j++) row[j] = ' ';
            //Setting a row in lines.
                char* lineRow = (char*) malloc((gridSize+1)*sizeof(char));
                for (int j=0; j<gridSize+1; j++) lineRow[j] = 0;
                lines[i] = lineRow;
                break;
        }
        row[gridSize*(HLineWidth+1)+1] = '\n';
        row[gridSize*(HLineWidth+1)+2] = '\0';
        gameGrid[i] = row;
    }
}

void set_mode(char game_mode)
{
    gameMode = game_mode;
}

void reset_stats()
{
    printf("Player 1, Enter your name: ");
    gets(player1.name);
    printf("\n");
    reset_player(player1);
    strcpy(player2.name, "Computer");
    if (gameMode == MODE_2)
    {
        printf("Player 2, Enter your name: ");
        gets(player2.name);
        printf("\n");
    }
    reset_player(player2);    
}

void reset_player(struct player fplayer)
{
    fplayer.score = 0;
    fplayer.linesDrawn = 0;

    return;
}

void update_stats()
{

}

void update_screen()
{
    system("cls");
    for (int row=0; row< 2*gridSize+1; row++)
    {
        printf("\t");
        color_printf(gameGrid[row], Black, White);
    }
}

void color_printf(char* str, int fore, int back)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, fore + 16*back);
    printf(str);
    SetConsoleTextAttribute(hConsole, White + 16*Black);
}