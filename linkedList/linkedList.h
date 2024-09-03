//this will contain all of the linked list functions


/*
Insertion: Adding a node at the beginning, end, or a specific position.
Deletion: Removing a node from the beginning, end, or a specific position.
Traversal: Accessing each node to read or process data.
Search: Finding a node with a specific value.
Update: Modifying the data in a node.
*/

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

struct node{
    int value;
    struct node * next;
    struct node * prev;
};
typedef struct node node_t;

node_t *createNode(int thisValue){ //returns pointer to created node
    node_t * result = malloc(sizeof(node_t));
    result->value = thisValue;

    return result;
}

void printList(node_t *head){
    node_t *temp = head;
    printf("-- ");
    while (temp != NULL){
        printf("%d -- ", temp->value); //this is the same as doing *temporary.value (dereference to find the actual node then looking at its value.)
        temp = temp->next; // same as *temporary.next

    }
    printf("\n");
}

node_t *findTail(node_t *head) { //returns pointer to tail
    node_t * temp = head;
    if (temp == NULL) {
        return NULL; // If the list is empty, return NULL
    }
    while (temp->next != NULL) { 
        temp = temp->next;
    }
    return temp;
}

void backwardsPrintList(node_t *head){
    node_t *temp = findTail(head);
    printf("-- ");
    while (temp != NULL){
        printf("%d -- ", temp->value); //this is the same as doing *temporary.value (dereference to find the actual node then looking at its value.)
        temp = temp->prev; // same as *temporary.next

    }
    printf("\n");
}


node_t *append(int thisValue, node_t* tail){ //returns pointer to appended node
    
    node_t *result = createNode(thisValue);
    node_t *temp = tail;
    tail->next = result;
    result->value = thisValue;
    result->next = NULL; 
    result->prev = tail;
    
    return result;

}


/*void insert(int value, int position, node_t * head){ //this will be 1 indexed, if position 1, new node will become head.
    
    node_t *Fresh = createNode(value);
    node_t *currentpos = head;

    for (int i = 1; i<position; i++){
        //if it is 1 before, changed the next value to the adress of Fresh
        //adress of next node
    }


}*/

#endif

