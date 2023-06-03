CC = gcc
CFLAGS = -Wall -Werror

all: lab3

lab3: lab3.o
	$(CC) $(CFLAGS) lab3.o -o lab3

lab3.o: lab3.c
	$(CC) $(CFLAGS) -c lab3.c

clean:
	rm -f *.o lab3
