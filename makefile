CC=gcc
CFLAGS=-std=c99 -g3 -pedantic -Wall -Wextra

hw4: hw4.o dnasearch.o
	$(CC) -o hw4 hw4.o dnasearch.o

hw4.o: hw4.c dnasearch.h
	$(CC) $(CFLAGS) -c hw4.c

dnasearch.o: dnasearch.c dnasearch.h
	$(CC) $(CFLAGS) -c dnasearch.c

clean:
	rm -f *.o hw4
