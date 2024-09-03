#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void *identifyThread(void* tid){ //this is a routine because it is a funciton that is identified by a pointer
    
    int ID = *(int*)tid;
    int threadNum = ID+1;
    for (int i =0; i<4;i++){
        printf("I am thread %d\n", threadNum);
        sleep(threadNum);
    }
    pthread_exit(tid);

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
    
    void * retval;
    int join = pthread_join(threads[1], retval);


    if(join == 0){
        printf("Thread %d Joined successfully\n", *(int*) retval);
    }

    pthread_exit(NULL);
    return 0;


}