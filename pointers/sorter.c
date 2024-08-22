#include <stdio.h>

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
    int x[]={4,1,7,3,10,5,55,34234234,21};
    int i;

    sort(x,9); // sort() function sorts the array x in ascending order

    printf("The sorted array is as follows:\n");

    for(i=0; i<9; i++){
        printf("%d ",x[i]);
    }
    printf("\n");
    return 0;
}