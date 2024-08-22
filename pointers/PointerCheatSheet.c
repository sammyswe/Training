#include <stdio.h>

/*  

* can mean 2 different things, depending on where it is used.
1. * is near a variable type name e.g. integer - Pointer to an integer
2. * is not near a variable type name - Go to the address pointed to by that pointer, and grab that value. 


& means 'the address of'. int * pX = &x, this means 'integer pointer called pX points to the address of x

array = &array = &array[0]
when you add or subtract from a pointer, the amount by which you do that is multiplied by the size of the pointer e.g 1 x sizeof(int).

*/


int main(void){
    int number = 5; // Integer 5 is assigned to variable called number

    int *number_pointer = &number; // pointer variable points to a box of memory that contains an int and is stored at the adress of number

    number_pointer = 10; // this is wrong, assigning a number directly to a pointer will change the box of memory that it points to, in this case to memory box 10.

    int bar = *number_pointer; //this looks at the address pointed to by number_pointer, and grabs the value before assigning it to bar. DEREFERENCING.

    

}