# object files, and the target library  
TARGET = solve

PATH2 = ../common/

FLAGS = -I$(PATH2) # -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

OBJS = solveBoard.o boardtest.o $(PATH2)board.o

# Build the library by archiving object files 
$(TARGET): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

board.o: $(PATH2)board.h
	$(CC) $(CFLAGS) $^ -o #@

clean:
	rm -f $(OBJS)
	rm -f $(Target)
	rm -f testout
	rm -f solve
	rm -f core*

test:
	make
	./solve blah < Testboard2
