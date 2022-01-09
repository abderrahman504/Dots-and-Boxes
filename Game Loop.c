#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
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
static int set_grid(int difficulty);
static void set_mode(char game_mode);
static void reset_stats();
static void reset_player(struct player fplayer);
static void update_stats(char line_drawn, int new_line[2]);
static char check_new_boxes(int new_line[2]);
static void update_grid(int new_line[2]);
static void update_screen();
static void take_game_input();
void send_message();


//game stats
struct player player1; //Structure that contains player 1's stats.
struct player player2; //Structure that contains player 2's stats.
struct player playingPlayer;
char** gameGrid; //The grid of the game.
char gameMode;
int gridSize;
int gridWidth;
int gridHeight;
int turn = 0;
int linesRemaining;
double gameTime; 
char** lines; //This is a 2d array that stores the state and color of all lines in the game.
char** boxed; //This is a 2d array that stores the state and color of all boxes in the game



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
        take_game_input();
    }
    printf("About to end execution.");
    getchar();
    return 0;
}



//Determines the size of the grid based on the difficulty then constructs the grid that will be drawn.
//Also sets the lines 2d array to all zeroes.
static int set_grid(int difficulty)
{
    switch (difficulty)
    {
        case DIFF_EASY:
            gridSize = GRID_SMALL;
            gridWidth = GRID_SMALL;
            gridHeight = GRID_SMALL;
            break;
        case DIFF_HARD:
            gridSize = GRID_LARGE;
            gridWidth = GRID_LARGE;
            gridHeight = GRID_LARGE;
            break;
        default:
            printf("Error at set_grid(). Unexpected value for difficulty.\n");
            getchar(); //Pausing execution with getchar().
            fflush(stdin);
    }
    gameGrid = (char**) malloc((2*gridHeight+1)*sizeof(char*));
    if (gameGrid == NULL)
    {
        printf("Could not allocate memory for Gamegrid.\n");
        return -1;
    }
    lines = (char**) malloc((2*gridHeight+1)*sizeof(char*));
    if (lines == NULL)
    {
        printf("Could not allocate memory for lines.\n");
        return -1;
    }
    for (int i=0; i<2*gridHeight+1; i++)
    {
        char* row = (char*) malloc((3+gridWidth*(HLineWidth+1))*sizeof(char));
        if (row == NULL)
        {
            printf("Could not allocate memory for a row in gameGrid.\n");
            return -1;
        }
        switch (i%2)
        {
            char* lineRow;
            case 0:
            //Setting a row in gameGrid.
                for (int j=0; j<gridWidth; j++)
                {
                    row[(HLineWidth+1)*j] = SmallBox;
                    for (int k=1; k<=HLineWidth; k++) row[5*j+k] = ' ';
                }
                row[gridWidth*(HLineWidth+1)] = SmallBox;
            //Setting a row in lines.
                lineRow = (char*) malloc(gridWidth*sizeof(char));
                for (int j=0; j<gridWidth; j++) lineRow[j] = 0;
                lines[i] = lineRow;
                break;
            case 1:
            //Setting a row in gameGrid.
                for (int j=0; j<gridWidth*(HLineWidth+1)+1; j++) row[j] = ' ';
            //Setting a row in lines.
                lineRow = (char*) malloc((gridWidth+1)*sizeof(char));
                for (int j=0; j<gridWidth+1; j++) lineRow[j] = 0;
                lines[i] = lineRow;
                break;
        }
        row[gridWidth*(HLineWidth+1)+1] = '\n';
        row[gridWidth*(HLineWidth+1)+2] = '\0';
        gameGrid[i] = row;
    }
}



static void set_mode(char game_mode)
{
    gameMode = game_mode;
}



static void reset_stats()
{
    player1.id = 1;
    player2.id = 2;
    reset_player(player1);
    reset_player(player2);
    turn = 0;
    gameTime = 0;
    linesRemaining = gridHeight*(gridWidth+1) + gridWidth*(gridHeight+1); 

}

static void reset_player(struct player fplayer)
{
    fplayer.score = 0;
    fplayer.linesDrawn = 0;

    return;
}



static void update_stats(char line_drawn, int new_line[2])
{
    if (line_drawn)
    {
        lines[new_line[0]][new_line[1]] = playingPlayer.id;
        char boxDrawn = check_new_boxes(new_line);
    }
}

static char check_new_boxes(int new_line[2])
{
    switch (new_line[0]%2)
        {
            case 0: //Need to check:
            //1.The row above and below; the lines at the same column and the next column
            //2.The row above and below by 2; the lines at the same column.

                break;
        }
}



static void update_screen()
{
    system("cls");
    char* HNumbers = (char*) malloc(((HLineWidth+1)*gridWidth + 3)*sizeof(char));
    HNumbers[0] = '1';
    for (int i=1; i<=gridWidth; i++)
    {
        for (int j=1; j<=HLineWidth; j++)
        {
            HNumbers[(i-1)*(HLineWidth+1)+j] = ' ';
        }
        HNumbers[i*(HLineWidth+1)] = '0' + i+1;
    }
    HNumbers[(HLineWidth+1)*gridWidth + 1] = '\n';
    HNumbers[(HLineWidth+1)*gridWidth + 2] = '\0';
    printf("\t");
    color_printf(HNumbers, Yellow, Black);

    for (int row=0; row< 2*gridHeight+1; row++)
    {
        printf("\t");
        color_printf(gameGrid[row], Yellow, Black);
    }
}



static void take_game_input()
{
    getchar();

}
