CC= gcc
CFLAGS= -Wall -ansi
ALLexe= Exercice2 Exercice2_arg Exercice3 Exercice4 Exercice5

all: clean Exercice2 Exercice2_arg Exercice3 Exercice4 Exercice5 

run: run_2 run_2_arg run_3 run_4 run_5



run_2: clean Exercice2
		./Exercice2

run_2_arg: clean Exercice2_arg
		./Exercice2_arg 20 20

run_3:  clean Exercice3
		./Exercice3

run_4:  clean Exercice4
		./Exercice4

run_5:  clean Exercice5
		./Exercice5


Exercice2: Exercice2.o
	$(CC) -o Exercice2 Exercice2.o $(CFLAGS)

Exercice2.o: Exercice2.c
	$(CC) -c Exercice2.c $(CFLAGS)

Exercice2_arg: Exercice2_arg.o
	$(CC) -o Exercice2_arg Exercice2_arg.o $(CFLAGS)

ExerciceRec.o: Exercice2_arg.c
	$(CC) -c Exercice2_arg.c $(CFLAGS)

Exercice3: Exercice3.o
	$(CC) -o Exercice3 Exercice3.o $(CFLAGS)

Exercice3.o: Exercice3.c
	$(CC) -c Exercice3.c $(CFLAGS)

Exercice4: Exercice4.o
	$(CC) -o Exercice4 Exercice4.o $(CFLAGS)

Exercice4.o: Exercice4.c
	$(CC) -c Exercice4.c $(CFLAGS)

Exercice5: Exercice5.o
	$(CC) -o Exercice5 Exercice5.o $(CFLAGS)

Exercice5.o: Exercice5.c
	$(CC) -c Exercice5.c $(CFLAGS)

clean: 
	rm -f *.o
	rm -f *~
	rm -f $(ALLexe)