#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"

#include <math.h>
#define CR "\x1b[31m"
#define CB "\x1b[34m"
#define CG "\x1b[32m"
#define CReset "\x1b[0m"
#define MAX_NAME 50


struct player
{
    char id;
    int score;
    char name[MAX_NAME];
    int linesDrawn;
} player1, player2;

int size, n = 0, remaining_lines = 0, ver_lines = 0, hor_lines = 0, number_of_player = 0;
int array[100][100] = {0};


int load_game(int difficulity, int mode);
void reset_player(struct player fplayer);
int greater(int x,int y);
void control_line(int row, int col, int hor_line[n + 1][n], int ver_line[n][n + 1], char grid[size][size], int player);
void write_grid(char grid[size][size], int size);
void first_player(char grid[size][size], int hor_line[n + 1][n], int ver_line[n][n + 1]);
void second_player(char grid[size][size], int hor_line[n + 1][n], int ver_line[n][n + 1]);
void info(void);
void add_to_leaderboard(char name[MAX_NAME], int score);

int load_game(int difficulty, int mode)
{
    system("cls");
    getName1:
    printf("Player 1, Enter your name: ");
    fgets(player1.name, MAX_NAME, stdin);
    if (player1.name[0] == '\n')
    {
        system("cls");
        color_printf("You didn't enter a name.\n", Red, Black);
        goto getName1;
    }
    for (int i=0; i<MAX_NAME; i++)
    {
        if (player1.name[i] == '\n')
        {
            player1.name[i] = 0;
            break;
        }
    }
    printf("\n");
    strcpy(player2.name, "Computer");
    if (mode == MODE_2)
    {
        getName2:
        printf("Player 2, Enter your name: ");
        fgets(player2.name, MAX_NAME, stdin);
        if (player2.name[0] == '\n')
        {
            system("cls");
            color_printf("You didn't enter a name.\n", Red, Black);
            goto getName2;
        }
        for (int i=0; i<MAX_NAME; i++)
    {
        if (player2.name[i] == '\n')
        {
            player2.name[i] = 0;
            break;
        }
    }
        printf("\n");
    }
    player1.id = 1;
    player2.id = 2;
    reset_player(player1);
    reset_player(player2);
    n = difficulty;
    number_of_player = mode;

    /* Old Code to get the difficulity and game mode.
    // read size of grid game from user
    do {
        system("cls");
		printf(CG "\tlevel(2 for beginner and 5 for expert): " CReset);
	} while (!scanf("%d", &n) && getchar());
    // read game mode from user
    do {
        system("cls");
		printf(CG "\t\tone or two player?: " CReset);
	} while (!scanf("%d", &number_of_player) && getchar() && (number_of_player != 1 || number_of_player != 2));
*/

    // create array to store horizontal lines
    int hor_line[n + 1][n], ver_line[n][n + 1];
    for (int r = 0; r < n + 1; r++){
        for (int t = 0; t < n; t++){
            hor_line[r][t] = 0;
        }
    }
    // create array to store vertical lines
    for (int f = 0; f < n; f++){
        for (int u = 0; u < n + 1; u++){
            ver_line[f][u] = 0;
        }
    }
    // size of grid
    size = 2 * n + 2;
    // create array which represent the grid on the screen
    int z = 1;
    char grid[size][size];
    // put numbers before rows and above columns
    for (int m = 1; m < size; m++){
        grid[0][m] = z;
        grid[m][0] = z;
        z++;
    }
    grid[0][0] = 0;
    remaining_lines = 2 * n *(n + 1);
    // store empty element in grid array
    for (int i = 1; i < size; i++){
        for (int j = 1; j < size; j++){
             grid[i][j] = 32;
        }
    }
    // create dots on grid
    for (int x = 1; x < size; x = x + 2){
        for (int y = 1; y < size; y = y + 2){
            grid[x][y] = 254;
        }
    }
    // write grid on the screen
    write_grid(grid, size);
    info();
    // call first player function
    first_player(grid, hor_line, ver_line);
    printf("Press Enter to go to Menu.\n");
    fflush(stdin);
    getchar();
    fflush(stdin);
    return MS_MENU;
}

//Function that resets each player structure.
void reset_player(struct player fplayer)
{
    fplayer.score = 0;
    fplayer.linesDrawn = 0;
    
}

// function for first player
void first_player(char grid[size][size], int hor_line[n + 1][n], int ver_line[n + 1][n]){
    if (remaining_lines == 0){
        return;
    }else{
        int row, col,row_1, row_2, col_1, col_2;
        // take a move from first player
        do {
            system("cls");
            write_grid(grid, size);
            info();
            printf(CR " player(1)(row row col col): " CReset);
        } while (!scanf("%d %d %d %d", &row_1, &row_2, &col_1, &col_2) && getchar() );

        if (row_1 == row_2){  // check if the player chooses horizontal line
            row = row_1;
            col = greater(col_1, col_2) - 1;
            // check a move is valid or not
            if ((row % 2 == 0 && col % 2 == 0)|| fabs(col_1 - col_2) != 2){
                system("cls");
                write_grid(grid, size);
                info();
                first_player(grid, hor_line, ver_line);
            }else{
                // check the place which first player chooses is empty or not
                if (grid[row][col] == 32){
                grid[row][col] = 196;
                array[row][col] = 1;
                remaining_lines--;
                player1.linesDrawn++;
                system("cls");
                write_grid(grid, size);
                info();

                // call control function to check the player close boxes or not
                control_line(row, col, hor_line, ver_line, grid, 1);
                }else{
                    system("cls");
                    write_grid(grid, size);
                    info();
                    first_player(grid, hor_line, ver_line);
                }
            }

        }else if (col_1 == col_2){ //check if the player chooses vertical line
            col = col_1;
            row = greater(row_1, row_2) - 1;
            // check a move is valid or not
            if ((row % 2 == 0 && col % 2 == 0) || fabs(row_1 - row_2) != 2){
                system("cls");
                write_grid(grid, size);
                info();
                first_player(grid, hor_line, ver_line);
            }else{
                if (grid[row][col] == 32){
                grid[row][col] = 179;
                array[row][col] = 1;
                remaining_lines--;
                player1.linesDrawn++;
                system("cls");
                write_grid(grid, size);
                info();

                // call control function to check the player closes boxes or not
                control_line(row, col, hor_line, ver_line,grid, 1);
                }else{
                    system("cls");
                    write_grid(grid, size);
                    info();
                    first_player(grid, hor_line, ver_line);
                }
            }

        }else{
            system("cls");
            write_grid(grid, size);
            info();
            first_player(grid, hor_line, ver_line);
        }
    }
}
// function for computer player(if player vs computer, call it)
void computer(char grid[size][size], int hor_line[n + 1][n], int ver_line[n][n + 1]){
    int found = 0, row = 0, col = 0;
    if (remaining_lines == 0){
        return;
    }else{
        // choose horizontal line and check is empty or not
        for (int i = 0; i < n + 1;i++){
            for (int j = 0; j < n;j++){
                if (hor_line[i][j] == 0){
                    grid[2 * i + 1][2 * j + 2] = 196;
                    array[2 * i + 1][2 * j + 2] = 2;
                    player2.linesDrawn++;
                    system("cls");
                    write_grid(grid, size);
                    info();
                    row = 2 * i + 1;
                    col = 2 * j + 2;
                    remaining_lines--;
                    found = -1;
                    // call control function to check the player close boxes or not
                    control_line(row, col, hor_line, ver_line,grid, 2);
                    break;
                }else if (ver_line[j][i] == 0){//choose vertical line and check is empty or not
                    grid[2 * j + 2][2 * i + 1] = 179;
                    array[2 * j + 2][2 * i + 1] = 2;
                    player2.linesDrawn++;
                    system("cls");
                    write_grid(grid, size);
                    info();
                    row = 2 * j + 2;
                    col = 2 * i + 1;
                    remaining_lines--;
                    found = -1;
                    control_line(row, col, hor_line, ver_line,grid, 2);
                    break;
                }
            }
            if (found == -1){
                found = 0;
                break;
            }
        }

    }


}

// second player function
void second_player(char grid[size][size], int hor_line[n + 1][n], int ver_line[n][n + 1]){
    if (remaining_lines == 0){
        return;
    }
    else{
        int row, col,row_1, row_2, col_1, col_2;
        // take a move from first player
        do {
            system("cls");
            write_grid(grid, size);
            info();
            printf(CB " player(2)(row row col col): " CReset);
        } while (!scanf("%d %d %d %d", &row_1, &row_2, &col_1, &col_2) && getchar() );
        if (row_1 == row_2){ // check if the player chooses horizontal line
            row = row_1;
            col = greater(col_1, col_2) - 1;
            // check a move is valid or not
            if ((row % 2 == 0 && col % 2 == 0) || fabs(col_1 - col_2) != 2){
                system("cls");
                write_grid(grid, size);
                info();
                second_player(grid, hor_line, ver_line);
            }else{   // check the place which first player chooses is empty or not
                if (grid[row][col] == 32){
                grid[row][col] = 196;
                array[row][col] = 2;
                remaining_lines--;
                player2.linesDrawn++;
                system("cls");
                write_grid(grid, size);
                info();

                // call control function to check the player close boxes or not
                control_line(row, col, hor_line, ver_line,grid, 2);
                }else{
                    system("cls");
                    write_grid(grid, size);
                    info();
                    second_player(grid, hor_line, ver_line);
                }
            }

        }else if (col_1 == col_2){ // check if the player chooses vertical line
            col = col_1;
            row = greater(row_1, row_2) - 1;
            // check a move is valid or not
            if ((row % 2 == 0 && col % 2 == 0) || fabs(row_1 - row_2) != 2){
                system("cls");
                write_grid(grid, size);
                info();
                second_player(grid, hor_line, ver_line);
            }else{ // check the place which first player chooses is empty or not
                if (grid[row][col] == 32){
                grid[row][col] = 179;
                array[row][col] = 2;
                remaining_lines--;
                player2.linesDrawn++;
                system("cls");
                write_grid(grid, size);
                info();

                // call control function to check the player close boxes or not
                control_line(row, col, hor_line, ver_line,grid, 2);
                }else{
                    system("cls");
                    write_grid(grid, size);
                    info();
                    second_player(grid, hor_line, ver_line);
                }
            }

        }else{
            system("cls");
            write_grid(grid, size);
            info();
            second_player(grid, hor_line, ver_line);
        }
    }
}
// control line function
void control_line(int row, int col, int hor_line[n + 1][n], int ver_line[n][n + 1], char grid[size][size], int player){
    int score_player = 0, box_win_row_af = 0, box_win_col_af = 0, box_win_row_bef = 0, box_win_col_bef = 0;
    if (row % 2 == 1 && col % 2 == 0){ // player chooses horizontal line
        hor_line[row/2][col/2 - 1] = player;
        // check if the player close box below the horizontal line played by him
        if (row != size - 1){
            if (hor_line[row/2 + 1][col/2 - 1] != 0){
                if (ver_line[row / 2][(col - 1)/2] != 0 && ver_line[row / 2][(col + 1)/2] != 0){
                    score_player++;
                    box_win_row_af = row + 1;
                    box_win_col_af = col;
                }
            }
        }
        // check if the player close box above the horizontal line played by him
        if (row != 1){
           if (hor_line[row/2 - 1][col/2 - 1] != 0){
                if (ver_line[row / 2 - 1][(col - 1)/2] != 0 && ver_line[row / 2 - 1][(col + 1)/2] != 0){
                    score_player++;
                    box_win_row_bef = row - 1;
                    box_win_col_bef = col;
                }
            }
        }
        // check to let player to play another move or not
        if (score_player > 0 && player == 1){
            player1.score += score_player;
            if (box_win_row_af != 0){
                grid[box_win_row_af][box_win_col_af] = 254;
                array[box_win_row_af][box_win_col_af] = 1;
            }
            if (box_win_row_bef != 0){
                grid[box_win_row_bef][box_win_col_bef] = 254;
                array[box_win_row_bef][box_win_col_bef] = 1;
            }
            system("cls");
            write_grid(grid, size);
            info();
            first_player(grid, hor_line, ver_line);
            score_player = 0;
        }else if (score_player > 0 && player == 2){
             player2.score += score_player;
            if (box_win_row_af != 0){
                grid[box_win_row_af][box_win_col_af] = 254;
                array[box_win_row_af][box_win_col_af] = 2;
            }
            if (box_win_row_bef != 0){
                grid[box_win_row_bef][box_win_col_bef] = 254;
                array[box_win_row_bef][box_win_col_bef] = 2;
            }
            system("cls");
            write_grid(grid, size);
            info();
            if (number_of_player == 2){
                second_player(grid, hor_line, ver_line);
            }else {
                computer(grid, hor_line, ver_line);
            }
            score_player = 0;
        }else{
            if (score_player == 0 && player == 1){
                if (number_of_player == 2){
                    second_player(grid, hor_line, ver_line);
                }else {
                    computer(grid, hor_line, ver_line);
                }
            }else if (score_player == 0 && player == 2){
                first_player(grid, hor_line, ver_line);
            }
        }
    }
    else if (row % 2 == 0 && col % 2 == 1){ // player choose vertical line
        ver_line[row/2 - 1][col/2 ] = player;
        // check if the player close box on the right of the vertical line played by him
        if (col != size - 1){
            if (ver_line[row/2 - 1][col/2 + 1] != 0){
                if (hor_line[row/2 - 1][col/2] != 0 && hor_line[row/2][col/2] != 0){
                    score_player++;
                    box_win_row_af = row;
                    box_win_col_af = col + 1;
                }
            }
        }
        // check if the player close box on the left of the vertical line played by him
        if (col != 1){
            if (ver_line[row/2 - 1][col/2 - 1] != 0){
                if (hor_line[row/2 - 1][col/2 - 1] != 0 && hor_line[row/2][col/2 - 1] != 0){
                    score_player++;
                    box_win_row_bef = row;
                    box_win_col_bef = col - 1;
                }
            }
        }
        // check to let player to play another move or not
        if (score_player > 0 && player == 1){
             player1.score += score_player;
            if (box_win_row_af != 0){
                grid[box_win_row_af][box_win_col_af] = 254;
                array[box_win_row_af][box_win_col_af] = 1;
            }
            if (box_win_row_bef != 0){
                grid[box_win_row_bef][box_win_col_bef] = 254;
                array[box_win_row_bef][box_win_col_bef] = 1;
            }
            system("cls");
            write_grid(grid, size);
            info();
            first_player(grid, hor_line, ver_line);
            score_player = 0;
        }else if (score_player > 0 && player == 2){
            player2.score += score_player;
            if (box_win_row_af != 0){
                grid[box_win_row_af][box_win_col_af] = 254;
                array[box_win_row_af][box_win_col_af] = 2;
            }
            if (box_win_row_bef != 0){
                grid[box_win_row_bef][box_win_col_bef] = 254;
                array[box_win_row_bef][box_win_col_bef] = 2;
            }
            system("cls");
            write_grid(grid, size);
            info();
            if (number_of_player == 2){
                second_player(grid, hor_line, ver_line);
            }else {
                computer(grid, hor_line, ver_line);
            }
            score_player = 0;
        }else{
            if (score_player == 0 && player == 1){
                if (number_of_player == 2){
                    second_player(grid, hor_line, ver_line);
                }else {
                    computer(grid, hor_line, ver_line);
                }
            }else if (score_player == 0 && player == 2){
                first_player(grid, hor_line, ver_line);
            }
        }
    }
}
int greater(int x,int y){

    if (x > y){
        return x;
    }
    else{
        return y;
    }
}
// write grid
void write_grid(char grid[size][size], int size){

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (j == 0){
                printf(CG "%2d " CReset, grid[i][j]);
            }
             else if(i == 0){
                printf(CG "%d " CReset, grid[i][j]);
            }else{
                if (array[i][j] == 1){
                    printf(CR "%c " CReset, grid[i][j]);
                }else if (array[i][j] == 2){
                    printf(CB "%c " CReset, grid[i][j]);
                }else{
                    printf(CG "%c " CReset, grid[i][j]);
                }
            }
        }
        printf("\n");
    }
}
// write information about player
void info(void){

    printf(CG "\n remaining lines: %d\n" CReset, remaining_lines);
    printf(CG " ------------------------------------------\n" CReset);
    printf(CR " player(1) score: %d\t Number of moves: %d\n" CReset, player1.score, player1.linesDrawn);
    printf(CG " ------------------------------------------\n" CReset);
    printf(CB " player(2) score: %d\t Number of moves: %d\n" CReset, player2.score , player2.linesDrawn);
    printf(CG " ------------------------------------------\n" CReset);
    if (remaining_lines == 0){
        if (player1.score > player2.score){
            printf(CR " player 1 is the winner \n" CReset);
            add_to_leaderboard(player1.name, player1.score);
        }else if (player1.score < player2.score){
            printf(CB " player 2 is the winner\n" CReset);
            add_to_leaderboard(player2.name, player2.score);
        }else{
            printf(" Equal\n");
            add_to_leaderboard(player1.name, player1.score);
            add_to_leaderboard(player2.name, player2.score);
        }
    }
}
//int check[][4] = {0};
//check[][]

void add_to_leaderboard(char name[MAX_NAME], int score)
{
    FILE*  board = fopen("Leaderboard.txt","a");
    fprintf(board, name);
    fprintf(board, "\t%d\n", score);
    fclose(board);
}
