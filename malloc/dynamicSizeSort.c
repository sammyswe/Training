#include <stdio.h>
#include <stdlib.h>

void swap(int * pnta, int * pntb){
    int temp = *pnta;
    *pnta = *pntb; 
    *pntb = temp;
}

void sort(int * array, int size){

    for(int i =0; i<size; i++){
        for(int j =0; j<size; j++){
            if(*(array+i)< *(array+j)){
                swap(array+i, array+j);
            }
        }
    }

}

int main() {
    int size; 
    printf("Enter the size of the array you want to sort: ");
    scanf("%d", &size);
    int *user_array = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i< size; i++){
        int d;
        printf("Please enter integer number %d: ", i+1);
        scanf("%d", &d);
        user_array[i] = d; 
    }

    sort(user_array,size); // sort() function sorts the array x in ascending order

    printf("The sorted array is as follows:\n");

    for(int i=0; i<size; i++){
        printf("%d ",user_array[i]);
    }
    printf("\n");
    return 0;
}