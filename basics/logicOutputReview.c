#include <stdio.h>
/*
Output Will Be:

B>A
C>A
C>B

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