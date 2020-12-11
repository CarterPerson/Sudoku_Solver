### Authored by Carter Person, Henry Phipps, and Jason Cushman

# Implementation

### Main function

In the main function, we first check the quantity of arguments and ensure that the user provided one. If the argument provided by the user is "create", then we run the boardcreate() function and then write the board to stdout, and if the argument is "solve", then we read the board from stdin and then run the solve function, solveBoard(), on that board.

If the input argument is neither "create" or "solve", we return an error statement saying that the argument must be either create or solve.


## Board

One very important aspect of our implementation is our board structure. This structure stores a 9x9 array of integers, where these integers represent the sudoku board's values. Inside of this board structure, we also hold an integer that represents the amount of empty spaces in our soduku board, which are integers in the 9x9 array that hold a value of 0.

### Vector structure

In order to more easily pass information in the form of 9 item arrays between functions, we created this vector structure. This is simply a 9 item integer array which is primarily used in our function to pass all of the possible numbers that can be put in a tile.


### Board functions


#### board_new()

Creates a new board and mallocs the space necessary to hold it. Initializes all of the values in the 9x9 int array to 0. Also initializes the "empty" integer to 81, representing the 81 tiles on the board.


#### vector_new()

Creates a new vector and mallocs the space necessary to hold it. initializes the 9 item array to be filled with zeros, then return the pointer to the vector.


#### writeBoard(FILE *fp, board_t *board)

This function writes the board from the arguments to the output file provided. It will write the board out in the same format that it is read from.


#### getTile(board_t *board, int x, int y)

This function will return the integer value that exists at a specific tile within the 9x9 array in the board. This function uses the x and y values to get that specific value.


#### setTile(board_t *board, int x, int y, int val)

This function is used whenever a value needs to be altered inside of the board's 9x9 int array (essentially whenever we add a number to the sudoku board to get closer to a solution). At the same time, It looks at the value being changed, and the value that it is being changed to. This function will either add to or subtract from the board's "empty" value to keep it updated. It will subtract from it if a tile is being changed from 0 to a nonzero value, and will add to the empty value if it is changing a tile from a nonzero value to zero. This function also makes sure that the value the tile is being changed to is between 0 and 9.


#### fullboard()

This function is primarily used when we create a new board that will be filled with random values. This function will initialize the top left, middle, and bottom right 3x3 boxes of values. This is primarily because these boxes don't have any interference with eachother's values, and thus we are able to easily start the creation of a unique board. This function will return a pointer to the newly created board with the stated boxes filled with values.


#### fillSquare()

This function is a helper function for fullboard(). This function will randomly fill a box, ensuring that it contains only one instance of the values 1-9 for each box and that all of the tiles are filled.


#### copyBoard(board_t *board)

This function is designed to be able to be used in our iterative functions. When we perform our solve function, There is a chance that it will need to run recursively to always find a solution to a sudoku puzzle that has a solution. When we make those recursive calls, we cannot change the board from the initial function that is calling itself, as that same "state" of the board might need to be used again if the first recursive path fails. This function is used to create a copy of the current state of the board in a separate object, so that we can then pass the copy into the recursive function while maintaining the same initial state of the board prior to recursion.


#### tileOptions(board_t *, int x, int y)

This function is used widely throughout our program. The purpose of this function is to return an ordered vector object that contains all of the possible values that can go in a specific tile, all shifted to the low indices of the vector's array.

This function is widely used throughout our program to check how many possible values can be placed at any given tile. This is because once int[n] = 0, then we know that the specified tile has n possible values that can be placed there.


#### isSolved(board_t *)

This function is mainly used to check the validity of a filled out board. It iterates over the entire board and make sure that each tile only has one possible value.


#### readboard()

This function will read a board from stdin and return a pointer to the board structure created from reading it in. This function depends on the board being passed in as 9 rows of 9 values, which must be separated by spaces.


## solveBoard(board_t *board)

This is the backbone of all of the functionality of our program. This function repeatedly iterates through all of the tiles in the board and keeps track of a few values while it does so. It will keep track of whether or not the board was changed for each iteration, the maximum amount of options it will accept on a tile when it is deciding which tiles to change, and also if the initial board passed in was full from the very start.

The iteration through the board is done within a while loop. The while loop will continue until the amount of empty tiles in the sudoku board is equal to zero, which would mean that the entire board is filled.

With each iteration of this while loop, the function will iterate over every value in the 9x9 array in a nested for loop. As it passes through each tile, it will only try to solve tiles that currently have a value of zero, skipping over any locations in the 9x9 array that are nonzero.

For each tile that currently has a value of 0, there are a 3 possible outcomes of tileOptions that we care about. The function checks these possibilies in the following order, only checking later possibilities if earlier statements fail (ie if 1  works it won't check 2 or 3, if 2 works it won't check 3).

1. tileOptions(...) ->arr[0] == 0
    - This means that the current tile has no values that can possibly go inside of it. This represents a failed solution. The function will return a NULL pointer.

2. tileOptions(...) ->arr[1] == 0 
    - This statement is only hit if the function has already shown the tile has at least one value that can be placed in it.
    - This function checks to see whether the second value in the vector returned by tileOptions is equal to zero. If the second value in the array is 0, then that indicates that the tile only has one possible value that can go into it while staying within the rules of sudoku.
    - Under the circumstance that this is true, then the function will change that tile's value to arr[0], which is the only valid value that can go there.
    - This function will also reset the value of n to 1.

3. tileOptions(...) ->arr[n] == 0
    - its important to note that this statement will only be hit if 2 is false.
    - For this statement to both be hit and to be true, it means that n >= 2, and that the current tile has a total of n options. Should this statement be true, This would mean that the current state of the sudoku board has hit a deadend, where there is no tile in the whole board that only has one value that it could possibly be. This function solves this issue by, within a for loop that represents all of the possible tile values, creating a copy of the current state of the board, changing the value of the tile to one of the possible values, and then recursively calling the solveBoard function on the copy of the board.
    - Still within the for loop, it will check and see if the board returned by the solveBoard(copy) call is NULL. if it is NULL, that means that the recursive path we were checking ended up not having a solution. HERE is where the for loop ends
    - This is designed to iterate over all of the possible values that fit into the tile and then solve the board, in order to overcome any instances where there is no obvious number to place into a tile.

After this function iterates over all of the tiles, it checks to see whether or not the board was changed in that iteration. If the board was not changed, it increases its "maximum" amount of options that it will accept a board having by incrementing n, and then repeat the iteration. This iteration will continue until every single tile is filled with a value.

After the while loop ends, This function will then check the solved board it produced. It will make sure that the board that was passed in was not already in it's solved state (it does this by checking the boolean that checked if any tile was ever changed), and it also checks to make sure that every tile only has one possible value that it can be. 

This function returns NULL if it fails either of those checks, as if either of those checks fail it either means that the initial board was already solved and didn't need to be solved, or that the initial board had some kind of mistake that made it impossible to create a valid solution (ie if multiple 2's existed in the same row in the initial sudoku board given by the user).

Else, if it passes both of the above checks, This function returns a pointer to the solved sudoku board. Throughout the entire function, the function itself deals with all of the memory, including the argument passed in. This means that the only malloced space at the end of the function will be held at the pointer being returned.


## createBoard()

This function is highly dependant on the solveBoard() function.

1. This function starts off by using the fullBoard() function from board.c. This creates a board with the first diagonal of 3x3 boxes initialized randomly. 
2. The createBoard function then passes this board into the solveBoard() function. This fills out the board initialized in fullBoard() into a solution.
    - Due to the initial condition of the board being randomized, this solveBoard call has many possible outcomes. Although it cannot create any possible sudoku puzzle, it can create nearly 1.1 million different "end" boards.
3. Using the board returned by the solveBoard function, the function then enters a while loop that will repeat while the board has less than 40 empty tiles.
    - This while loop starts by finding 20 random tiles that only have 1 possible value, and then sets those tile's values to 0.
    - The while loop will then continually iterate through the board, and change any tile with only one possible value to an empty tile. Should The function fail to encounter any tile that only has one possible value, The function will wait one second, and then call createBoard() again. This situation can only arise from a board that cannot have 40 tiles removed while maintaining a unique solution, meaning that we will need a new initial board. Due to the random value function, we need to wait until time(0) returns a new value, meaning we need to wait for a second to pass.

    - The reason why we started by removing 20 random tiles is because the for-loop that iterates over all of the tiles has a preference for removing values along the top and to the left , meaning that there would be a very uneven balance of empty tiles throughout the board without starting off with random tiles being removed.

    - The uniqueness of the board generated is guaranteed by the way we remove tiles. By only removing tiles with one possible value, we leave a "path" of tiles that only have one possible value that lead back to the solution.

4. Should the function successfully get through the while loop, This would mean that it has successfully created a board with 40 empty slots and a unique solution. This board is then returned from the function.

