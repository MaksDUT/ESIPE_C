CC=gcc
CFLAGS=-Wall -ansi

Exercice2: clean Exercice2.o 
	$(CC) -o Exercice2 Exercice2.o $(CFLAGS) 

Exercice2.o: Exercice2.c 
	$(CC) -c Exercice2.c $(CFLAGS)

clean:
	rm -f *.o
	rm -f *~
	rm -f Exercice2
