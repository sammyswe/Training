#include <stdio.h>

int main(void){

    char string [5] = "Sammy"; //printing weird characters at the end - Why is this?

    for(int i =0; string[i] != '\0'; i++){
        printf("%c", string[i]);
    }
}