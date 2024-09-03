CC=gcc
CFLAGS=-Wall -g
BINS=calculator.o staticCalcLib.a calcTest

all: $(BINS)

calculator.o: calcTest.c calcFunctions.h
	$(CC) $(CFLAGS) -c calcTest.c -o calculator.o

staticCalcLib.a: calculator.o
	ar rcs staticCalcLib.a calculator.o

calcTest: calcTest.c staticCalcLib.a
	$(CC) $(CFLAGS) calcTest.c staticCalcLib.a -o calcTest

clean:
	rm -f $(BINS) calcTest


#target: dependencies
#    command



#Makefile syntax includes:
#Targets: The file to create (e.g., output.o).
#Dependencies: Files needed to build the target.
#Commands: Actions to create the target (start with a tab)