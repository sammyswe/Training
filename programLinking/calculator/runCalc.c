#include <stdio.h>
#include "calcFunctions.h"

int main(void){

    int a;
    int b;
    printf("Please enter your 1st number (a): ");
    scanf("%d", &a);
    printf("\nPlease enter your 2nd number (b): ");
    scanf("%d", &b);

    int c = add(a,b);
    int d = multiply(a,b);
    int e = square(a);
    int f = cube(a);

    printf("\na+b = %d \na*b = %d \na^2 = %d \na^3 = %d",c,d,e,f);

    printf("\nChecking calculator functions working correctly.....\n");
    if (c == a+b){
        printf("Add function working correctly :)");
    }else{
        printf("Add function failing - check function logic");
    }


    

}