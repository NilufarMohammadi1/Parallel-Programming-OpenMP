CC=g++

CFLAGS=-c -fopenmp
LNKFLAGS=-fopenmp 


all: main

main: main.o 
	$(CC) $(LNKFLAGS) main.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f *o main
