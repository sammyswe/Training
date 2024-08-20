#include <stdio.h>

int main (void){
    int x;
    int y;
    int z;

    printf("Enter number 1: \n");
    scanf("%d", &x);
    printf("Enter number 2: \n");
    scanf("%d", &y);
    printf("Enter number 3: \n");
    scanf("%d", &z);
    
    int a = x+y+z;

    printf("%d", a);
}