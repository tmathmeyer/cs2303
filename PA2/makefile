CFLAGS = -g -m32


words: tree.o words.o
	gcc $(CFLAGS) -Wall tree.o words.o -o words

tree.o: tree.h tree.c
	gcc $(CFLAGS) -Wall -c tree.c

words.o: tree.h words.c
	gcc $(CFLAGS) -Wall -c words.c

clean:
	rm -f *.o out.txt