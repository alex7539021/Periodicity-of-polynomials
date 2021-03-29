CC=g++

CFLAGS=-c -Wall

all: polyn2.o main.o
	$(CC) main.o polyn2.o -o main
	
main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp
	
polyn2.o: polyn2.h polyn2.cpp
	$(CC) $(CFLAGS) polyn2.cpp 

test: test.cpp
	$(CC) $(CFLAGS) test.cpp 
	
clean: 
	rm -rf *.o main 
