CC = g++
CFLAGS = -Wall
LDFLAGS = -lm

all: main

main: Main.o
	$(CC) $(CFLAGS) Main.o $(LDFLAGS) -o main

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c Main.cpp

clean:
	rm main Main.o