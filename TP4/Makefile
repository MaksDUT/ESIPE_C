CC=gcc
CFLAGS=-Wall -ansi -g
OBJ=stack.o 


stack: $(OBJ)
	$(CC) -o stack $(OBJ) 

stack.o: stack.c stack.h
	$(CC) -c stack.c -o stack.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f stack
	rm -f *~
