CC = g++
CFLAGS = -Wall
LDFLAGS = -lm

all: A B

A: PartA_Main.o
	$(CC) $(CFLAGS) PartA_Main.o $(LDFLAGS) -o A

PartA_Main.o: PartA_Main.cpp PartA_DataChecks.h
	$(CC) $(CFLAGS) -c PartA_Main.cpp

B: PartB_Main.o
	$(CC) $(CFLAGS) PartB_Main.o $(LDFLAGS) -o B

PartB_Main.o: PartB_Main.cpp PartB_DataChecks.h
	$(CC) $(CFLAGS) -c PartB_Main.cpp

clean:
	rm A PartA_Main.o B PartB_Main.o