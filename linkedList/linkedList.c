//this file will contain some print functions etc to show that the linked list is working
//needs to check all of the functions from linked list .h 
#include <stdio.h> 
#include <stdlib.h>
#include "linkedList.h"


typedef struct node node_t;


int main(void){
    node_t * head;

    node_t n1, n2, n3;
    
    n1.value = 10;
    n2.value = 20;
    n3.value = 30;

    head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = NULL;

    n3.prev = &n2;
    n2.prev = &n1; 
    n1.prev = NULL;

    node_t n4;

    node_t * tail = findTail(head);
    append(40, tail);
    printList(head);
    backwardsPrintList(head);


}