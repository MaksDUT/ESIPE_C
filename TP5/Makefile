CC= gcc
CFLAGS= -Wall -ansi
OBJ=main.o array.o 
 
TP5: $(OBJ)
	$(CC) -o TP5 $(OBJ) $(CFLAGS)

main.o: main.c array.h
	$(CC) -c main.c $(CFLAGS)

array.o: array.c array.h
	$(CC) -c array.c $(CFLAGS)

clean: 
	rm -f *.o
	rm -f *~
	rm -f main

