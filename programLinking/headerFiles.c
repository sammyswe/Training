#include <stdio.h>
#include "fourteenXfifteen.h"


int main(void){
    int x;
    printf("Please enter your number: ");
    scanf("%d", & x);
    int y = equation(x);

    printf("The result of the equation is: %d \n", y);
}