# object files, and the target library 
CC = gcc
MAKE = make  

CFILES = board.c
HFILES = board.h
OBJS = board.o

# Build the object files
$(OBJS): $(CFILES) $(HFILES)
	$(CC) -c $(CFILES)

clean:
	rm -f *.o
	rm -f $(OBJS)
