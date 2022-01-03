#include <stdio.h>
#include <windows.h> // WinApi header
#include <stdlib.h>
#include "Constants.h"
#include "Menu.c"
#define MAX_NAME 50
#define GRID_SMALL 2
#define GRID_LARGE 5


struct player
{
    char id;
    int score;
    char name[MAX_NAME];
    int linesDrawn;
};

int load_game(int difficulty, char game_Mode);
int set_grid(int difficulty);
void set_mode(char game_mode);
void reset_stats();
void reset_player(struct player fplayer);
void update_stats(char line_drawn, int new_line[2]);
char check_new_boxes(int new_line[2]);
void update_grid(int new_line[2]);
void update_screen();
void take_input();
void send_message();

void color_printf(char *str, int fore, int back);

//game stats
struct player player1; //Structure that contains player 1's stats.
struct player player2; //Structure that contains player 2's stats.
struct player playingPlayer;
char** gameGrid; //The grid of the game.
char gameMode;
int gridSize;
int turn = 0;
int linesRemaining;
double gameTime; 
char** lines; //This is a 2d array that stores the state of all lines in the game.



//The function that runs while a game is being played.
int load_game(int difficulty, char game_mode)
{
    char lineDrawn = 0; //Boolean to check if a line has been drawn this turn. 
    int newLine[2];//Index of the new line in the lines array.
    char err = 0; //Variable that's used to check if a function faced an error during execution.
    playingPlayer = player1;

    err = set_grid(difficulty);
    if (err == -1)
    {
        getchar();
        return -1;
    }

    set_mode(game_mode);
    reset_stats(playingPlayer);
    while (1)
    {
        update_stats(lineDrawn, newLine);
        update_screen();
        take_input();
    }
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
    player1.id = 1;
    player2.id = 2;
    
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
    turn = 0;
    gameTime = 0;
    linesRemaining = 2*gridSize*(gridSize+1); 

}

void reset_player(struct player fplayer)
{
    fplayer.score = 0;
    fplayer.linesDrawn = 0;

    return;
}



void update_stats(char line_drawn, int new_line[2])
{
    if (line_drawn)
    {
        lines[new_line[0]][new_line[1]] = playingPlayer.id;
        char boxDrawn = check_new_boxes(new_line);
    }
}

char check_new_boxes(int new_line[2])
{
    switch (new_line[0]%2)
        {
            case 0: //Need to check:
            //1.The row above and below; the lines at the same column and the next column
            //2.The row above and below by 2; the lines at the same column.

                break;
        }
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