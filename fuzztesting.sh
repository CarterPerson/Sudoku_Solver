#!/bin/bash

# Fuzztesting for sudoku program
# This script takes an integer n from user and runs sudoku create and solve n times.
# to test the program's ability to randomly generate and solve multiple boards.


if [ "$#" -ne 1 ];
then
	echo "Error: must provide exactly 1 parameter"
fi

echo "Running $1 tests on sudoku create and solve"
echo "FUZZTESTING OUTPUT FOR SUDOKU" > fuzztesting.out
for (( i = 1; i <= $1; i++ )); 
do
	echo "Test: $i" >> fuzztesting.out
	./sudoku create > testout
	./sudoku solve < testout >>testout
	cat testout >> fuzztesting.out
	sleep 1
done 
rm -f testout
echo "Testing Complete.  Results printed to fuzztesting.out"
