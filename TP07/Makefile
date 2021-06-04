CC=gcc
CFLAGS=-Wall -ansi

test: clean test.o 
	$(CC) -o test test.o $(CFLAGS) -lMLV

test.o: test.c 
	$(CC) -c test.c $(CFLAGS)

clean:
	rm -f *.o
	rm -f *~
	rm -f test
