#include <stdio.h> 

int main(void){

    int A = 0;
    int B = 0;

    for (int i = 1;i<=20;i++){
        A+=3;
        B+=7;

        if(i%5 == 0 && i!=20){
            printf("This is iteration number %d, and the current values are A = %d, B = %d\n",i,A,B);
            continue;
        }

        if (i==20){
            printf("Final values are \n A = %d \n B = %d\n",A,B);
        }

        if(i%2 == 1 && i%5!=0){
            printf("Odd iteration, A = %d\n", A);
        }
        if(i%2 == 0 && i!=20){
            printf("Even iteration, B = %d\n", B);
        }


    }
}