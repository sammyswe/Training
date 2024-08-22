#include <stdio.h>
#include <stdlib.h>

int *pointer;

void allocatePointer(int a, int b){
    int y = a+b;
    pointer = &y;
}

int main(void){

    allocatePointer(3,10);
    int x = *pointer;
    printf("%d\n", x);

}

