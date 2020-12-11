#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> 
#include "board.h"

/************* DATA STRUCTURES *************/
/*
typedef struct board {
	int empty; // number of blank '0' tiles
	bool uniq;
	int arr[9][9];
} board_t;

typedef struct vector {
	int arr[9];
} vector_t;
*/

/********** FUNCTION PROTOTYPES ************/

board_t* board_new();
vector_t* tileOptions(board_t* board, int x, int y);
board_t* copyBoard(board_t* board);
board_t* fullBoard();
void setTile(board_t* board, int x, int y, int val);
int getTile(board_t* board, int x, int y);
void writeBoard(FILE* fp, board_t* board);
void fillSquare(board_t* board, int x, int y);
board_t* readBoard();


/********* FUNCTION DEFINITIONS ************/
// See board.h for more details

board_t* board_new() {
	board_t* board = malloc(sizeof(board_t));
	
	// initialize array to zero
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			board->arr[x][y] = 0;
		}
	}
	board->empty = 81;
	board->uniq = false;
	return board;
}

vector_t* vector_new() {
	vector_t* vector = malloc(sizeof(board_t));
	
	// initialize array to zero
	for (int x = 0; x < 9; x++) {
		vector->arr[x] = 0;
	}
	return vector;
}

void writeBoard(FILE* fp, board_t* board) {
	if (fp == NULL || board == NULL) {
		fprintf(stderr, "Error: could not write board, one of the arguments is NULL\n");
	} else {
		// print all lines
		for(int j = 0; j < 9; j++) {	
			// print line
			for (int i = 0; i < 8; i++) {
				fprintf(fp, "%d ", board->arr[j][i]);	
			}
			fprintf(fp, "%d\n", board->arr[j][8]);
		}
	}
}

int getTile(board_t* board, int x, int y) {
	int val = 0;

	if (x < 0 || x > 9 || y < 0 || y > 9) {
		fprintf(stderr, "Error: x and/or y is out of bounds. Values must be between 0 and 9\n");
		return -1;
	} else {
		val = board->arr[x][y];
		return val;
	}
}


void setTile(board_t* board, int x, int y, int val) {
	if (val < 0 || val > 9) {
		fprintf(stderr, "Error: val must be an integer from 0 to 9\n");
	} else {
		if (getTile(board, x, y) == 0 && val > 0){
			board->empty = board->empty - 1;
		}else if(getTile(board, x, y) != 0 && val ==0){
			board->empty = board->empty + 1;
		}
		board->arr[x][y] = val;
	}
}


board_t* fullBoard() {
	board_t* result = board_new();
	result->empty = 81;
	fillSquare(result, 0, 0);
	fillSquare(result, 3, 3);
	fillSquare(result, 6, 6);
	//result->empty = 54;
	//if (solveBoard(result) != NULL) 
	return result;
	// else return NULL;
}

// helper function for fullBoard
void fillSquare(board_t* board, int x, int y) {
	srand(time(0));
	int arr[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			while (getTile(board, x+i, y+j) == 0) {
				int temp = rand() % 9;

				if (arr[temp] != 0) {
					//printf("our random number is %d\n", temp);
					setTile(board, x+i, y+j, temp+1);
					arr[temp] = 0;
				}
			}
		}
	}
}


board_t* copyBoard(board_t* board) {
	
	// check to make sure input is valid
	if (board == NULL) {
		fprintf(stderr, "Error: copyBoard must take a valid board pointer\n");
		return NULL;
	}
	board_t* result = board_new();
	result->empty = board->empty;
	result->uniq = board->uniq;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			result->arr[i][j] = board->arr[i][j];
		}
	}
	return result;
}


vector_t* tileOptions(board_t* board, int x, int y) {
	int options[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	vector_t* vec = vector_new();

	/*
	// check to make sure space is currently empty
	if (getTile(board, x, y) != 0) {
		fprintf(stderr, "Error: you can only call tileOptions on an empty space\n");
		return NULL;
	} */

	// check the row to the left
	for (int i = 0; i < x; i++) {
		int temp = getTile(board, i, y);
		if  (temp != 0) {
			options[temp-1] = 0;
		}
	}
	// check the row to the right
	for (int i = x+1; i < 9; i++) {
		int temp = getTile(board, i, y);
		if  (temp != 0) {
			options[temp-1] = 0;
		}
	}
	// check the column above
	for (int i = 0; i < y; i++) {
		int temp = getTile(board, x, i);
		if  (temp != 0) {
			options[temp-1] = 0;
		}
	}
	// check the column below
	for (int i = y+1; i < 9; i++) {
		int temp = getTile(board, x, i);
		if  (temp != 0) {
			options[temp-1] = 0;
		}
	}

	// check the box
	// find top left corner of box
	int a = (x/3) * 3;
	int b = (y/3) * 3;

	// iterate over box
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a + i != x && b + j != y) {
				int temp = getTile(board, (a + i), (b + j));
				if  (temp != 0) {
					options[temp-1] = 0;
				}
			}
		}
	}
	
	// convert array into desired format
	int count = 0;
	for (int i = 0; i  < 9; i++) {
		if (options[i] > 0) {
			vec->arr[count] = i+1;
			count ++;
		}
	}
	return vec;
}


bool isSolved(board_t *board){
	bool returner = true;
	for(int x = 0; x< 9; x++){
		for(int y = 0; y<0; y++){
			if(tileOptions(board, x, y)->arr[0] == 0 || tileOptions(board, x, y)->arr[1] != 0){
				returner = false;
			}
		}
	}
	return returner;
}



/*reads a board from stdin, assuming that the board being read in is in the 
form of 9 lines of 9 numbers, separated by spaces.
If the input is invalid, this function will print that stdin did not have a valid format to stdout,
and will then return null.
Memory:
    This function will return a board pointer. the user is responsible for later freeing
    this board by calling board_delete.
*/
board_t *readBoard(){
    board_t *returner = board_new();
    for(int y = 0; y<9; y++){

        int row[9];
        if(scanf("%d %d %d %d %d %d %d %d %d\n", &row[0], &row[1], &row[2], &row[3], &row[4],&row[5],&row[6],&row[7],&row[8]) != 9){
            printf("please insert an 9x9 sudoku board in a valid format");
            return NULL;
        }
		for(int x = 0; x<9; x++){
			setTile(returner, y, x, row[x]);
		}

    }
    return returner;

}
