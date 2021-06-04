CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=
OBJ=sudoku.o main.o in_out.o


run_1: sudoku
	./sudoku data/grid1.txt
run_2: sudoku
	./sudoku data/grid2.txt
run_3: sudoku
	./sudoku data/grid3.txt
run_4: sudoku
	./sudoku data/grid4.txt
run_5: sudoku
	./sudoku data/grid5.txt


sudoku: $(OBJ)
	$(CC) -o sudoku $(OBJ) $(CFLAGS) -lMLV 

main.o: main.c sudoku.h in_out.h
	$(CC) -c main.c $(CFLAGS)

sudoku.o: sudoku.c sudoku.h
	$(CC) -c sudoku.c $(CFLAGS)

in_out.o: in_out.c in_out.h
	$(CC) -c in_out.c $(CFLAGS)

clean: 
	rm -f *.o
	rm -f *~
	rm -f sudoku
