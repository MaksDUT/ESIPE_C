CC=gcc
CFLAGS=-Wall -ansi -g
OBJ=exercice2.o 


exercice2: $(OBJ)
	$(CC) -o exercice2 $(OBJ) 

exercice2.o: exercice2.c 
	$(CC) -c exercice2.c -o exercice2.o $(CFLAGS)

exercice3: exercice3.o
	$(CC) -o exercice3 exercice3.o

exercice3.o: exercice3.c 
	$(CC) -c exercice3.c -o exercice3.o $(CFLAGS)

exercice3.o: exercice4.c 
	$(CC) -c exercice4.c -o exercice4.o $(CFLAGS)

clean:
	rm -f *.o
	rm -f exercice2
	rm -f exercice3
	rm -f *~