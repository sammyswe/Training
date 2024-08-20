#include <stdio.h>

int main(void){

    char string[] = "sammy";
    long x = 0;
    
    for(int i =0; string[i] != '\0';i++){ //null terminator - marks the end of a string
        x+= (long) string[i];
    }

    printf("Long int = %ld", x);
}