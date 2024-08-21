#include <stdio.h>

int howmany =0;
void printer();

int main(void){
    for (int i =0; i<10;i++){
        printer();
    }


}

void printer(){
    printf("This function has been used %d times before \n", howmany);
    howmany++;
}