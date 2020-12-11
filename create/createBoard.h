/* 
 * ################# createBoard.h ####################
 * This function creates a new randomly generated board with 40 empty tiles
 * and only one unique solution.  It is implemented in createBoard.c
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "../solve/solveBoard.h"

/****************** CreateBoard() *****************************/
/* This function accomplishes its task in two steps: creating a random board, 
 * and removing random tiles while ensuring a unique solution.
 *
 * First,  createBoard initializes a new struct_board and calls
 * the fullboard function from board.h which creates a board where
 * the 3x3 boxes, 1, 5, and 9 are all filled randomly forming a mostly
 * empty board with filled squares across the diagonal from
 * top left to bottom right.  It then utilizes the solveBoard
 * function (solve/solveBoard.h) to fill in the board, creating
 * a random sudoku board. 
 * 
 * Next, createBoard uses a whileloop and randomly selects 20 tiles 
 * to remove.  Before removing a tile, it checks to ensure that only
 * one number (1-9) or option can be used to fill that square to ensure
 * the board will have only one unique solution.  Once 20 squares have
 * been removed, the function enters nested for loops that iterate through
 * the entire puzzle, attempting to remove 20 more tiles that only have
 * one option.  If a tile cannot be changed throughout the entire puzzle,
 * the function is re-run (recursive).  This is done to ensure that 
 * the function can handle a puzzle that after the first 20 empty squares
 * does not have 20 more squares that can be removed while ensuring a unique
 * solution.
 */
board_t* createBoard(int tries);
