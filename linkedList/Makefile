CC=gcc
BINS=linkedList.o linkedListLib.a linkedList

all: $(BINS)

linkedList.o: linkedList.c linkedList.h
	$(CC) -c linkedList.c -o linkedList.o

linkedListLib.a: linkedList.o
	ar rcs linkedListLib.a linkedList.o

linkedList: linkedList.c linkedListLib.a
	$(CC) linkedList.c linkedListLib.a -o linkedList

clean:
	rm -f $(BINS) linkedList


#target: dependencies
#    command



#Makefile syntax includes:
#Targets: The file to create (e.g., output.o).
#Dependencies: Files needed to build the target.
#Commands: Actions to create the target (start with a tab)