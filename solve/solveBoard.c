/*
 * #################### solveBoard #######################
 *
 * solveBoard contains only one function, solveBoard() see 
 * header file, solveBoard.h, for details. 
 */


#include "solveBoard.h"

board_t* solveBoard(board_t* board) {
	bool changedBoard = false;
	bool alreadySolved = true;
	int n = 1;

	board->uniq = true;
	while(board->empty > 0) {
		changedBoard = false;
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				// Check if tile is empty
				if (getTile(board, x, y) == 0) {
					alreadySolved = false;
					vector_t* vec = tileOptions(board, x, y);
					int options[9] = {0,0,0,0,0,0,0,0,0};
					int oplen = 0;
					for (int i = 0; i < 9; i++) {
						options[i] = vec->arr[i];
						if (options[i] != 0) oplen++;
					}
					free(vec);

					// If no options
					if (options[0] == 0) {
						return NULL;
					
					} else if (options[1] == 0) {
						// One option
						setTile(board, x, y, options[0]);
						n = 1;
						changedBoard = true;
					
					} else if (n >= oplen) {
						// Multiple options
						for (int i = 0; i < n; ++i)
						{	
							board->uniq = false;
							board_t* copy = copyBoard(board);
							setTile(copy, x, y, options[i]);
							changedBoard = true;
							
							board_t* oldboard = board;	
							// call function recursively
							board = solveBoard(copy);
								
							if (board == NULL) {
								free(copy);
								board = oldboard;
							} else {
								
								free(oldboard);
								return board;
							}
						}
						return NULL;
					}
				}
			}
		}
		if (!changedBoard) {
			n++;
		}
	}
	if(alreadySolved == false && isSolved(board) == true){
		return board;
	}else{
		return NULL;
	}
}
