CC=gcc
CFLAGS=-Wall -ansi
OBJ=sudoku.o main.o in_out.o draw.o

sudoku: $(OBJ)
	$(CC) -o sudoku $(OBJ) $(CFLAGS) -lMLV

main.o: main.c sudoku.h in_out.h draw.h
	$(CC) -c main.c $(CFLAGS) -lMLV

sudoku.o: sudoku.c sudoku.h
	$(CC) -c sudoku.c $(CFLAGS)

in_out.o: in_out.c in_out.h sudoku.h
	$(CC) -c in_out.c $(CFLAGS)

draw.o: draw.c draw.h sudoku.h
	$(CC) -c draw.c $(CFLAGS) -lMLV

clean: 
	rm -f *.o
	rm -f *~
	rm -f sudoku


