#include <stdio.h>

int main(void){

    char string [] = "Sammy"; 

    for(int i =0; string[i] != '\0'; i++){
        printf("%c", string[i]);
    }
    printf("\n");

    return 0;
}