/*
malloc() takes a single argument, the size of the memory to allocate
(in bytes) and returns the address of our newly allocated memory as a void pointer
*/ 
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *my_array = (int *) malloc(sizeof(int) * 10); // (int *) casts the void pointer to an int. 
    int *my_arrayTwo = (int *) calloc(10, sizeof(int)); //calloc clears the newly assigned memory to make it all equal to 0.
    int *tmp_ptr = (int *) realloc(my_array, sizeof(int) * 20); // Used to resize an array if its too small - takes a pointer and a size as params.
    void free(void *my_array); //frees the memory.
    void free(void *my_arrayTwo);

    //filling this newly created array can be done in two ways. The normal way (below)
    my_array[0] = 1;
    my_array[1] = 2;
    my_array[9] = 10;

    //and the pointer manipulation way (below) - this is not reccomended because it is accident prone.
    *my_array = 1;
    *(my_array+1) = 2;
    *(my_array+9) = 10;

}