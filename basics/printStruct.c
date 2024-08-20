#include <stdio.h>
#include <string.h>

int main(void){

    struct person{
        int age;
        char name [30];
        char faveColour [10];
    };

    struct person sam = {22, "Sam", "Red"};

    printf("This person is called %s and is %d years old and their favourite colour is %s \n", sam.name, sam.age, sam.faveColour);

    struct person bob;

    bob.age = 40;
    strcpy (bob.name, "Bob"); //cant use = to assign strings, must use strcopy
    strcpy (bob.faveColour, "blue");

    struct person bill = {.age = 30, .name = "Bill", .faveColour = "Green"};



    printf("This person is called %s and is %d years old and their favourite colour is %s \n", bob.name, bob.age, bob.faveColour);

    printf("This person is called %s and is %d years old and their favourite colour is %s", bill.name, bill.age, bill.faveColour);

}