#include <stdio.h> 
void printPhrase(char string[]); 

int main(void){

    char printString[] = "Print this string";

    printPhrase(printString);

    return 0;

}

void printPhrase(char string[]){

    for (int i = 0; string[i] != '\0'; i++){
        printf("%c", string[i]);
    }
   printf("\n"); 

   return 0;
}