CC=gcc
CFLAGS=-Wall
OBJ= game.o shootemup.o draw.o background.o

shoot: clean $(OBJ)
	$(CC) -o shoot $(OBJ) $(CFLAGS) -lMLV -lm

game.o: game.c shootemup.h draw.h
	$(CC) -c game.c $(CFLAGS) 

shootemup.o: shootemup.c shootemup.h 
	$(CC) -c shootemup.c $(CFLAGS) -lMLV 


draw.o: draw.c draw.h shootemup.h
	$(CC) -c draw.c $(CFLAGS) -lMLV 

clean:
	rm -f *.o
	rm -f *~
	rm -f shoot