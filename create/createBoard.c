#include "createBoard.h"

/*
 * ###################### createBoard ####################
 * This program contains only one function that creates a new
 * random sudoku board with 40 empty tiles and 1 unique solution.
 * see header file, createBoard.h for details.
 */


/********** CreateBoard() *****************/
board_t* createBoard(int tries) {
	srand(tries);
	int iterations = 0; //counter to prevent loop from taking too long in the case of a board which cannot be created using this method
	board_t* board = fullBoard();

	//writeBoard(stdout, board);

	board = solveBoard(board);
	while(board->empty < 40){ //continue until 40 open spaces
		//randomly select a tile and remove the value
		int randX = rand() % 9;
		int randY = rand() % 9;
		int val = getTile(board, randX, randY); 
		if(val != 0){ 
			vector_t *options = tileOptions(board, randX, randY);
			if (options->arr[1] == 0) { //ensure only one option possible
				setTile(board, randX, randY, 0); //remove tile
			}
			free(options);
		}
		if(board->empty >= 20){ //after the first 20 are empty, initialize a for loop to remove 20 more squares, if not use recursion to call function again
			bool isChanged = false;
			for(int y = 0; y<9; y++){
				for(int x = 0; x<9; x++){
					vector_t *options = tileOptions(board, y, x);
					if(options->arr[1] == 0 && getTile(board, y, x) != 0){
						isChanged = true;
						setTile(board, y, x, 0);
					}
					free(options);
				}
			}
			if(!isChanged){
				sleep(1); //This set of random numbers fails to produce a unique board, waiting for next set.
				return createBoard(tries+1);
			}
		}
		if(iterations > 50000){
			fprintf(stderr, "Error: Board could not be created in a reasonable amount of time\n");
			return NULL;
		}
		iterations++;
	}
	return board;
}

