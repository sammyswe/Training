#include <stdio.h>

int main(void){
    char array[] = "String";
    char * arrayptr = &array[0];
    int length = 0;

    for(int i = 0; *(arrayptr+i)!= "\0";i++){
        length++;
    }

    printf("This string has length %d", length);

}