#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void *identifyThread(void* tid){ //this is a routine because it is a funciton that is identified by a pointer
    sleep(*(int*)tid);
    int two = 2;
    void* retval = &two;
    printf("I am thread %d\n", *(int*) tid);
    pthread_exit(retval);
    return 0;
}

int main(void){
    int rc, t;
    int nThreads = 4;
    pthread_t threads [nThreads];
    int *taskIDs [nThreads];

    for (int i=0; i<nThreads;i++){

        taskIDs[i] = (int*) malloc(sizeof(int));
        *taskIDs[i] = i;
        

        rc = pthread_create(&threads[i],NULL,identifyThread,(void*) taskIDs[i]);
        //pthread create takes for paramaters
        //1. the pointer to the thread
        //2. the attributes of the thread.
        //3. A pointer to a routine to start
        //4. Any arguments that the routine will need.
    }

    pthread_exit(NULL);
    return 0;


}