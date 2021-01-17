CC= gcc
CFLAGS= -Wall -ansi

all: clean Exercice1 Exercice2 Exercice3 Exercice4

run: run_1 run_2 run_3 run_4

run_1: clean Exercice1
		./Exercice1

run_2: clean Exercice2
		./Exercice2

run_3:  clean Exercice3
		./Exercice3 "TEST"

run_4:  clean Exercice4
		./Exercice4

Exercice1: Exercice1.o
	$(CC) -o Exercice1 Exercice1.o $(CFLAGS)

Exercice1.o: Exercice1.c
	$(CC) -c Exercice1.c $(CFLAGS)

Exercice2: Exercice2.o
	$(CC) -o Exercice2 Exercice2.o $(CFLAGS)

Exercice2.o: Exercice2.c
	$(CC) -c Exercice2.c $(CFLAGS)

Exercice3: Exercice3.o
	$(CC) -o Exercice3 Exercice3.o $(CFLAGS)

Exercice3.o: Exercice3.c
	$(CC) -c Exercice3.c $(CFLAGS)

Exercice4: Exercice4.o
	$(CC) -o Exercice4 Exercice4.o $(CFLAGS)

Exercice4.o: Exercice4.c
	$(CC) -c Exercice4.c $(CFLAGS)

clean: 
	rm -f *.o
	rm -f *~