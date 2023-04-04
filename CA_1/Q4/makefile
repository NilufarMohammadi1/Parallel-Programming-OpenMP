CC=g++

CFLAGS=-c -march=haswell

all: main

main: main.o 
	$(CC) $(LIBDIR) $(LIBFILE) main.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCDIR) main.cpp

clean:
	rm -f *o main
