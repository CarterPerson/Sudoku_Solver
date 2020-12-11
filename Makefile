# object files, and the target library  
TARGET = sudoku

FLAGS = # -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

OBJS = sudoku.o ./create/createBoard.o ./solve/solveBoard.o ./common/board.o

# Build the library by archiving object files 
$(TARGET): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

board.o: ./common/board.h
	$(CC) $(CFLAGS) $^ -o #@

solveBoard.o: ./solve/solveBoard.h
	$(CC) $(CFLAGS) $^ -o #@

createBoard.o: ./create/solveBoard.h
	$(CC) $(CFLAGS) $^ -o #@

clean:
	rm -f $(TARGET)
	rm -f *~
	rm -f *.o
	rm -f testout
	rm -f *.out
	$(MAKE) -C common clean
	$(MAKE) -C solve clean
	$(MAKE) -C create clean

test:
	make
	chmod 777 fuzztesting.sh
	chmod 777 unittesting.sh
	./fuzztesting.sh 20 > testing.out
	cat fuzztesting.out >> testing.out
	./unittesting.sh >> testing.out
	cat unittesting.out >> testing.out
fuzztest:
	make
	./fuzztesting.sh 20
unittest:
	make
	./unittesting.sh
