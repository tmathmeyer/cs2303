CFLAGS = -g


life: game.o life.o
	gcc $(CFLAGS) -Wall game.o life.o -o life

game.o: game.c
	gcc $(CFLAGS) -Wall -c game.c

life.o: life.h life.c
	gcc $(CFLAGS) -Wall -c life.c

clean:
	rm -f *.o *.out life