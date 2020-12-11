**Main function**

1. Checks inputs
	- If second input is "create":

		1. Call a function called createBoard()

			2. Randomly generates “boxes” 1, 5, and 9, creating a diagonal of “boxes” that don’t interfere with each other using the function fullBoard
			3. Pass this into the SolveBoard function to fill out the remainder of the board with a solution
			4. While the board’s counter of empties is <40, pulls out the value of a random tile, checks and sees if it still a unique solution
				- If it has a unique solution, continues to pull more out, increments the board’s counter
				- If it does not still have a unique solution, then it puts the value back into the board

		3. Prints this unsolved board to stdout

	- If second input is "solve":

		1. Read in board from stdin using ReadInBoard()

			- We will use a structure called board_t that holds a 9x9 array of integers, a boolean that tracks if it has a unique solution, a int that keeps track of unset tiles

		2. Pass that board into SolveBoard(board_t *)

			- Has a while loop that loops until the board is solved (counts down a counter that keeps track of unsolved tiles)
			- Iterates through every tile, looking for unset tiles with only one possible value (using function tileoptions(board_t *board, int x, int y))

				- If no tiles have 1 option, we then look for tiles with 2 options and recursively call the solve function for each options after copying the board

					- Change boolean “multiple solutions” to true in the board’s copy

		3. Prints this solved board to stdout

  

  

Other notes:

Whenever we call the SolveBoard function, we pass in a copy of the board we are working with. This is because the recursive formula is designed to make changes to a board that may/may not be the final solution, and is designed to return a pointer to a solved version of the board that was passed in. This function will deal with all memory allocation issues, so the user won't need to worry about freeing anything that is used by the function.