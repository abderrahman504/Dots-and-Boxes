#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Constants.h"
#define MAX_NAME 50


struct player
{
    char id;
    char name[MAX_NAME];
    int score;
    int edgesDrawn;
};

struct position
{
    int row;
    int col;
};


int load_game(int grid_size[2], char game_Mode, char save_file[]);
static int set_grid();
static void set_mode(char game_mode);
static void reset_stats();
static void reset_player(struct player fplayer);
static void update_stats(char edge_drawn, struct position new_edge);
static char handle_new_boxes(struct position new_edge);
static void update_grid(struct position new_edge);
static void update_screen(char afterStatsMessage[]);
static void declare_winner();
static char* take_game_input();
static char check_points_legality(struct position p1, struct position p2);
static int set_new_edge(struct position p1, struct position p2); //Sets the newEdge variable. returns 0 if the edge is already drawn and 1 otherwise.
static void free_memory();

static int afterMSColor;
static char EmptyMS[] = "\n";
static char SaveMS[] = "Your game was saved to \"save file %d.save\".\n";
static char UndoMS[] = "You performed an undo.\n";
static char RedoMS[] = "You performed a redo.\n";
static char InvalidInputMS[] = "Your input is invalid. Try again.\n";
static char WrongPointsMS[] = "The points you typed cannot be connected. Try again.\n";
static char EdgeDrawnMS[] = "This line is already drawn.\n";
static char ExitSignal = '0';

//game stats
static struct player player1; //Structure that contains player 1's stats.
static struct player player2; //Structure that contains player 2's stats.
static struct player playingPlayer;
static char gameMode;
static int gridWidth;
static int gridHeight;
static int turn;
static int edgesRemaining;
static clock_t gameStart;
static double gameTime; 
static char** edges; //This is a 2d array that stores the state of all edges in the game.
static char ** boxes;

static char edgeDrawn = 0; //Boolean to check if an edge has been drawn this turn. 
static struct position newEdge;//Index of the new edge in the edges array.



//The function that runs while a game is being played.
int load_game(int grid_size[2], char game_mode, char save_file[])
{
    char err = 0; //Variable that's used to check if a function faced an error during execution.
    gridHeight = grid_size[0];
    gridWidth = grid_size[1];

    err = set_grid(grid_size);
    if (err == -1)
    {
        getchar();
        return -1;
    }

    set_mode(game_mode);
    reset_stats();
    playingPlayer = player1;
    edgeDrawn = 0;
    char* afterStatsMessage = EmptyMS; //Message will be printed after the stats.
    while (1)
    {
        update_stats(edgeDrawn, newEdge);
        update_screen(afterStatsMessage);
        
        if (edgesRemaining == 0)
        {
            declare_winner();
            break;
        }
        afterStatsMessage = take_game_input();
        if (afterStatsMessage[0] == ExitSignal) break;
    }
    color_printf("About to end execution of load_game().", White, Black);
    free_memory();
    getchar();
    fflush(stdin);
    return MS_MENU;
}



//Determines the size of the grid based on the difficulty then constructs the grid that will be drawn.
//Also sets the edges 2d array to all zeroes.
static int set_grid()
{
    boxes = (char**) malloc (gridHeight*sizeof(char*));
    if (boxes == NULL)
    {
        printf("Could not allocate memory for boxes.\n");
        return -1;
    }
    edges = (char**) malloc((2*gridHeight+1)*sizeof(char*));
    if (edges == NULL)
    {
        printf("Could not allocate memory for edges.\n");
        return -1;
    }
    for (int i=0; i<2*gridHeight+1; i++)
    {
        char* edgeRow;
        switch (i%2)
        {
            case 0: // The rows with the horizontal edges.

            //Setting a row in edges.
            edgeRow = (char*) malloc(gridWidth*sizeof(char));
            for (int j=0; j<gridWidth; j++) edgeRow[j] = 0;
            break;
//----------------------------------------------------------
            case 1: ;// The rows with the vertical edges.
            //Setting a row in boxes
            char* boxRow = (char*) malloc(gridWidth*sizeof(char));
            for (int j=0; j<gridWidth; j++)
            {
                boxRow[j] = 0;
            }
            boxes[i/2] = boxRow;

            //Setting a row in edges.
            edgeRow = (char*) malloc((gridWidth+1)*sizeof(char));
            for (int j=0; j<gridWidth+1; j++) edgeRow[j] = 0;
            break;
        }

        edges[i] = edgeRow;
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
    turn = 1;
    gameStart = clock();
    edgesRemaining = gridWidth*(gridHeight+1) + gridHeight*(gridWidth+1); 

}

static void reset_player(struct player fplayer)
{
    fplayer.score = 0;
    fplayer.edgesDrawn = 0;

    return;
}



static void update_stats(char edge_drawn, struct position new_edge)
{
    if (edge_drawn)
    {
        turn++;
        edgesRemaining--;
        playingPlayer.edgesDrawn++;
        edges[new_edge.row][new_edge.col] = playingPlayer.id;
        char boxDrawn = handle_new_boxes(new_edge);
        //Copying any stat changes from playingPlayer variable to the actual player variable.
        if (playingPlayer.id == player1.id) player1 = playingPlayer;
        else player2 = playingPlayer;
        //Switching the playing player if a box hasn't been drawn.
        if (!boxDrawn)
        {
            playingPlayer = (playingPlayer.id == player1.id) ? player2 : player1;
        }
    }
    clock_t timeEnd = clock();
    gameTime = ((double) (timeEnd-gameStart)) / CLOCKS_PER_SEC;
}

static char handle_new_boxes(struct position new_edge)
{
    struct position newBox;
    char boxDrawn = 0;
    switch (new_edge.row%2)
    {
        case 0://Horizontal edge,
        //Edges to check:
        //1.The row above by 1; at the same column and the next one. The row above by 2 at the same column, and...
        //2.The row below by 1; at the same column and the next one. The row below by 2 at the same column.
        //Checking the above square.
        if (new_edge.row != 0)
        {
            if ((edges[new_edge.row-2][new_edge.col] == 0) || (edges[new_edge.row-1][new_edge.col] == 0) || (edges[new_edge.row-1][new_edge.col+1] == 0)) goto BottomSquare;
            newBox.row = new_edge.row / 2 - 1;
            newBox.col = new_edge.col;
            boxes[newBox.row][newBox.col] = playingPlayer.id;
            playingPlayer.score++;
            boxDrawn = 1;
        }
    //Checking the below square.
        BottomSquare:
        if (new_edge.row != 2*gridHeight)
        {
            if ((edges[new_edge.row+2][new_edge.col] == 0) || (edges[new_edge.row+1][new_edge.col] == 0) || (edges[new_edge.row+1][new_edge.col+1] == 0)) break;
            newBox.row = new_edge.row / 2;
            newBox.col = new_edge.col;
            boxes[newBox.row][newBox.col] = playingPlayer.id;
            playingPlayer.score++;
            boxDrawn = 1;
        }
        break;
//-----------------------------------------------------------------------------------
        case 1: //Vertical Edges.
        //Edges to check:
        //1.The row above an below; the previous column. The same row; the prevoius column, and....
        //2.The row above an below; the same column. The same row; the next column.
        //Left Square.
        if (new_edge.col != 0)
        {
            if (edges[new_edge.row][new_edge.col-1] == 0 || edges[new_edge.row-1][new_edge.col-1] == 0 || edges[new_edge.row+1][new_edge.col-1] == 0) goto RightSquare;
            newBox.row = (new_edge.row-1) / 2;
            newBox.col = new_edge.col-1;
            boxes[newBox.row][newBox.col] = playingPlayer.id;
            playingPlayer.score++;
            boxDrawn = 1;
        }
        //Right Square.
        RightSquare:
        if (new_edge.col != gridWidth)
        {
            if (edges[new_edge.row][new_edge.col+1] == 0 || edges[new_edge.row-1][new_edge.col] == 0 || edges[new_edge.row+1][new_edge.col] == 0) break;
            newBox.row = (new_edge.row-1) / 2;
            newBox.col = new_edge.col;
            boxes[newBox.row][newBox.col] = playingPlayer.id;
            playingPlayer.score++;
            boxDrawn = 1;
        }
        break; 
    }
    return boxDrawn;
}



static void update_screen(char afterStatsMessage[])
{
    system("cls");
    set_color(Yellow, Black);
    printf("\t   ");
    
    for(int i=0; i<gridWidth+1; i++) // Printing the numbers at the top of the grid.
    {
        printf("%-5d", i+1); //Should change the -5 if HLineWidth is changed later.
    }
    printf("\n");
    for (int row=0; row<2*gridHeight+1; row++) // Printing the grid.
    {
        printf("\t");
        switch (row%2)
        {
            case 0: //Even row with dots, hlines and numbers.
            set_color(Yellow, Black);
            printf("%-3d", row/2+1);
            for (int i=0; i<2*gridWidth+1; i++)
            {
                switch (i%2)
                {
                    case 0: //Dots.
                    printf("%c", SmallBox);
                    break;
                //----------------------
                    default:// Horizontal edges.
                    if (edges[row][i/2] == 0)
                    {
                        for (int j=0; j<HLineWidth; j++) printf(" ");
                        break;
                    }
                    int edgeColor = edges[row][i/2] == player1.id ? Blue : Red;
                    set_color(edgeColor, Black);
                    for (int j=0; j<HLineWidth; j++) printf("%c", HLine);
                    set_color(Yellow, Black);
                }
            }
            break;
//----------------------------------------------------------------------------------------------
            default: //Odd row with boxes and vlines.
            printf("   ");
            for (int i=0; i<2*gridWidth+1; i++)
            {
                switch(i%2)
                {
                    case 0: //Vertical edge.
                    if (edges[row][i/2] == 0)
                    {
                        printf(" ");
                        break;
                    }
                    int edgeColor = edges[row][i/2] == player1.id ? Blue : Red;
                    set_color(edgeColor, Black);
                    printf("%c", VLine);
                    set_color(Yellow, Black);
                    break;
                //------------------------------------------------
                    default://Box.
                    if(boxes[row/2][i/2] == 0)
                    {
                        for(int j=0; j<HLineWidth; j++) printf(" ");
                        break;
                    }
                    int boxColor = boxes[row/2][i/2] == player1.id ? Blue : Red;
                    set_color(boxColor, Black);
                    for(int j=0; j<HLineWidth; j++) printf("%c", BigBox);
                    set_color(Yellow, Black);
                    break;
                }
            }
            break;
        }
        printf("\n");
    }
    printf("\n");
    color_printf("Score:\n", Yellow, Black);// Print scores.
    set_color(Blue, Black);
    printf("%s: %d      ", player1.name, player1.score);
    set_color(Red, Black);
    printf("%s: %d\n", player2.name, player2.score);

    color_printf("Lines Drawn:\n", Yellow, Black);// Print number of lines drawn.
    set_color(Blue, Black);
    printf("%s: %d     ", player1.name, player1.edgesDrawn);
    set_color(Red, Black);
    printf("%s: %d\n", player2.name, player2.edgesDrawn);
    set_color(Yellow, Black);

    int seconds, minutes;
    clock_t end = clock();
    seconds = (int)(gameTime) % 60;
    minutes = (int)(gameTime) / 60;
    printf("Game time: %dm %ds\n", minutes, seconds); // Print game time.


    set_color(afterMSColor, Black);
    printf(afterStatsMessage);

}



static void declare_winner()
{
    if (player1.score == player2.score)
    {
        color_printf("It's a draw!\n", White, Black);
    }
    else
    {
        struct player winner =  player1.score > player2.score ? player1 : player2; 
        int winnerColor = winner.id == 1 ? Blue : Red;
        color_printf(winner.name, winnerColor, Black);
        color_printf(" is the winner!\n", White, Black);
    }
}



static char* take_game_input()
{
    color_printf("It's ", Yellow, Black); // Printing which player's turn it is.
    int turnColor = playingPlayer.id == player1.id ? Blue : Red;
    set_color(turnColor, Black);
    printf("%s's ", playingPlayer.name);
    set_color(Yellow, Black);
    printf("turn.\n");

    set_color(Yellow, Black);
    printf("Enter two points: ");

    char input[12] = {};
    fgets(input, 12, stdin);
    fflush(stdin);
    if (input[11] != '\n' && input[11] != 0) // Case of too long input.
    {
        afterMSColor = Red;
        edgeDrawn = 0;
        return InvalidInputMS; 
    }
    if (input[0] == '\n') // Case of empty input.
    {
        afterMSColor = Red;
        edgeDrawn = 0;
        return InvalidInputMS;
    }
    if(strcmp(input, "exit\n") == 0)// Case of exit input.
    {
        afterMSColor = Yellow;
        edgeDrawn = 0;
        return "0"; //The exit signal.
    }
    //Check for save input.
    //Check for undo input.
    //Check for redo input.
    
    struct position p1, p2;   
    char tracking_num = 1, r1, c1, r2, c2;
    r1 = r2 = c1 = c2 = 0;
    int num = 0;
    for(int i=0; i<11; i++)
    {
        if(input[i] == ' ')
        {
            tracking_num++;
            num = 0;
            continue;
        }
        if (input[i] == '\n') 
        {
            if (r1*r2*c1*c2) goto coordinateCheckLoopEnd;
            afterMSColor = Red;
            edgeDrawn = 0;
            return InvalidInputMS;
        }
        if (input[i] > '9' || input[i] < '0') 
        {
            afterMSColor = Red;
            edgeDrawn = 0;
            return InvalidInputMS;
        }
        //At this point in the code, input[i] is supposed to be a digit.
        num = num*10 + (input[i] - '0');
        switch(tracking_num)
        {
            case 1:
            r1 = 1;
            p1.row = num - 1;
            goto coordinateCheckLoopNext;
            
            case 2:
            c1 = 1;
            p1.col = num - 1;
            goto coordinateCheckLoopNext;

            case 3:
            r2 = 1;
            p2.row = num - 1;
            goto coordinateCheckLoopNext;

            case 4:
            c2 = 1;
            p2.col = num - 1;
            goto coordinateCheckLoopNext;

            default:
            if (!(r1*c1*r2*c2)) // Not all coordinates were provided.
            {
                afterMSColor = Red;
                edgeDrawn = 0;
                return InvalidInputMS;
            }
            goto coordinateCheckLoopEnd;
        }
        
        coordinateCheckLoopNext:
        continue;
        coordinateCheckLoopEnd:
        break;
    }

    char legalPoints = check_points_legality(p1, p2);
    if (legalPoints)
    {
        edgeDrawn = set_new_edge(p1, p2);
        if (edgeDrawn)
        {
            afterMSColor = Yellow;
            return EmptyMS;
        }
        afterMSColor = Red;
        return EdgeDrawnMS;
    }
    edgeDrawn = 0;
    afterMSColor = Red;
    return WrongPointsMS;
}

static char check_points_legality(struct position p1, struct position p2)
{   
    if (p1.row < 0 || p1.row > gridHeight || p2.row < 0 || p2.row > gridHeight || p1.col < 0 || p1.col > gridWidth || p2.col < 0 || p2.col > gridWidth) return 0;
    if ((p1.row == p2.row && abs(p1.col - p2.col) == 1) || (p1.col == p2.col && abs(p1.row - p2.row) == 1)) return 1;
    else return 0;
}

static int set_new_edge(struct position p1, struct position p2)
{
    //There are two cases; we're connecting a horizontal edge or a vertical one.
    //In case of a horizontal one, the edge's row is the row of the points times 2, and the column is the smaller point's column. 
    //In case of a vertical one, the edge's row is the smaller point's row times 2 plus 1, and the column is the column of the points.
    if (p1.row == p2.row) //Case 1: Horizontal edge.
    {
        newEdge.row = p1.row*2;
        newEdge.col = p1.col<p2.col ? p1.col : p2.col;
    }
    else //Case 2: Vertical edge.
    {
        newEdge.row = 2*(p1.row<p2.row ? p1.row : p2.row) + 1;
        newEdge.col = p1.col;
    }
    if (edges[newEdge.row][newEdge.col] == 0) return 1;
    else return 0;
}



static void free_memory() //Free the edges and boxes arrays.
{
    //Free the edges array.
    for (int i=0; i<2*gridHeight+1; i++)
    {
        free(edges[i]);
    }
    free(edges);
    //Free the boxes array.
    for (int i=0; i<gridHeight; i++)
    {
        free(boxes[i]);
    }
    free(boxes);
}
