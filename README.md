## Sudoku Creator and Solver
**Group:** Henry Phipps, Carter Person, Jason Cushman (Celina5)
**Overview:** This program can both solve provided sudoku puzzles, and create new, random sudoku boards with 40 empty tiles and one unique solution.
**Documentation:** Please see `DESIGN.md` for a detailed description of the design of
this program, `IMPLEMENTATION.md` for in depth descriptions of the implementation of
the functions in this program . Finally, see 'TESTING.md' for details of the testing
of this program.
|Program Contents|  |
|--|--|
|**Create**|
|createBoard.c|
|**Solve**| |
|solveBoard.c | solveBoard.h |
|**common**| |
|board.c | board.h| 

**Compiling Instructions:**
1. To compile sudoku: `make`
2. To compile and run fuzztesting (bash script): `make fuzztest`
3. To compile and run unittesting (bash script): `make test`
