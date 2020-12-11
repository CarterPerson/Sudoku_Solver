/************ STRUCTURE *************/
//typedef struct board board_t;
//typedef struct vector vector_t;
typedef struct board {
	int empty; // number of blank '0' tiles
	bool uniq;
	int arr[9][9];
} board_t;

typedef struct vector {
	int arr[9];
} vector_t;

/************ board_new *************/
/* Returns pointer to new board
-- Initializes empty board to all zeros with 81 empty slots
-- Initializes uniq to false
--
-- MEMORY CONTRACT:
-- user is requred to call free board later */
board_t* board_new();

/************** copyBoard ************/
/*  Returns: 
--	A board pointer that points to a copy of the board that
--  was passed in as an input if everything goes right.
--  
--  NULL if the input is invalid
--  
--
-- MEMORY CONTRACT:
-- The user is responsible for freeing the old board and the new board */
board_t* copyBoard(board_t* board);

/************** tileOptions ************/
/* Returns a nine element integer array containing the avaliable
-- options for the input tile. These integers are stored towards 
-- the begining of the array. The rest of the array indexes are
-- set to 0
--
-- If there are no options for that tile, the function returns NULL */
vector_t* tileOptions(board_t* board, int x, int y);

/**************** fillBoard ****************/
/* Returns a board pointer to a full board
-- Returns NULL if it was unable to generate a full board
-- 
-- Uses fillSquare as a helper function
--
-- MEMORY CONTRACT:
-- User must clear the board later */
board_t* fullBoard();

/*************** setTile ****************/
/* This is very self explanatory */
void setTile(board_t* board, int x, int y, int val);

/*************** getTile ****************/
/* Returns tile value specified by x and y
-- Returns -1 if indexes are out of bounds */
int getTile(board_t* board, int x, int y);

/*************** writeBoard ****************/
/* Writes the contents of a board to a file
-- must receive file open for writing
-- Prints an error if the file pointer is null */
void writeBoard(FILE* fp, board_t* board);

/*************** isSolved ****************/
/* iterates through the given board in 3 ways, checking to see if the board is solved.  
a solved board must have all numbers (1-9) in every row, column, and 3x3 box.  This function
returns true if those criteria are met, otherwise false.*/
bool isSolved(board_t *board);

board_t* readBoard();

