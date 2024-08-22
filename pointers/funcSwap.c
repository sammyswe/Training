#include <stdio.h>

void swap(int * pnta, int * pntb){


    int temp = *pnta;
    *pnta = *pntb; 
    *pntb = temp;
}


int main(int argc, char *argv[]) {
   int val_a = 50;
   int val_b = 20;
   swap(&val_a, &val_b);

   printf("val_a is %d (should be 20)\n", val_a);
   printf("val_b is %d (should be 50)\n", val_b);
  return 0;
}