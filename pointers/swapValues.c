#include <stdio.h>
#include <stdlib.h>

void swapper(int **a, int **b){

    int *temp = *a;
    *a = *b;
    *b = temp;
    
}

/*  

* can mean 2 different things, depending on where it is used.
1. * is near a variable type name e.g. integer - Pointer to an integer
2. * is not near a variable type name - Go to the address pointed to by that pointer, and grab that value. 


& means 'the address of'. int * pX = &x, this means 'integer pointer called pX points to the address of x

*/


int main(void){
    int I = 0;
    int J = 5;
    int *pointI = &I; //created pointer I, makes it point to the part of memory where number 0 is stored
    int *pointJ = &J; //created pointer J, makes it point to the part of memory where number 5 is stored.

    printf("Number %d is stored at address %p \n", *pointI, pointI);
    printf("Number %d is stored at address %p \n", *pointJ, pointJ);

    swapper(&pointI, &pointJ);

    printf("Number %d is stored at address %p \n", *pointI, pointI);
    printf("Number %d is stored at address %p \n", *pointJ, pointJ);

}
