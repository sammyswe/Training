#include <stdio.h> 
/*

wont compile unless we declare j in line 21

variable i (2) is bigger than j (1)
variable i (3) is bigger than j (2)
variable i (4) is bigger than j (3)
variable i (5) is bigger than j (4)
variable i (6) is bigger than j (5)
variable i (7) is bigger than j (6)
variable i (8) is bigger than j (7)
variable i (9) is bigger than j (8)

last values: i (garbage value), j (garbage value)

*/
int main(void)
{
    int i; //holds garbage value
    //int j; //holds garbage value
    for( i = 0; i < 10; i++ )
    {
        int j = 0;
        for( j = 10; j > 0; j-- )
        {
            if( i > j )
            {
                printf("Variable i (%d) is bigger than j (%d) \n", i, j);
                break; //breaks out of for loop at first instance of i>j
            }
        }
    }
    
    /* print result */
    printf("Last values: i (%d), j (%d) \n", i, j);
    //j doesnt exist here, i will display a garbage value
    
    return 0;
}