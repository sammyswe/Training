#include <stdio.h>
/*
Output Will Be:

Underflow of A as is an unsigned int, so A is larger than b and c

A>B
A>C
B>C

*/

int main(void)
{
   unsigned int    A = -10;
   int             B = 5;
   unsigned int    C = 100;
   
   if(A > B)
   {
       printf("A > B\n");
   }
   else
   {
       printf("B > A\n");        
   }
   
   
   if(A > C)
   {
       printf("A > C\n");
   }
   else
   {
       printf("C > A\n");        
   }
   
   
   if(B > C)
   {
       printf("B > C\n");
   }
   else
   {
       printf("C > B\n");        
   }
   
  return 0;

}