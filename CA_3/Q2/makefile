CC=g++

CFLAGS=-c
LIBS=-lpthread 


all: main

main: main.o 
	$(CC) main.o -o main $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp $(LIBS)

clean:
	rm -f *o main
