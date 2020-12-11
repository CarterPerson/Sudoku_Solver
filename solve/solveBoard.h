/*
 * ############### SolveBoard Header File ####################
 * solveBoard contains only one function that is implemented
 * in solveBoard.c This function is used to solve a given
 * sudoku board.
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "../common/board.h"


/************************* solveBoard() ***********************/
/* SolveBoard is a recursive function that iterates through a
 * given struct board, filling in empty tiles.  It does this
 * using nested for loops to iterate through the board, finding
 * all empty squares.  It then uses the IsOptions function found
 * in board.h to check how many solutions there are for that tile
 * If there is only one option, the tile is filled.  If there
 * if there are multiple options, the function copies the board,
 * and tries to solve that board, trying one of the options.  
 * If a solution to the entire board is found, the function returns
 * that board, otherwise it deletes the copied board and tries the
 * next option in a new copy.  If no options are found, the function
 * prints that no solution could be found to stdout and returns NULL.
 */
board_t* solveBoard(board_t* board);
