#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count =0;
pthread_mutex_t mutex;



void *identifyThread(void* tid){ //this is a routine because it is a funciton that is identified by a pointer
    
    int ID = *(int*)tid;
    int threadNum = ID+1;
    for (int i =0; i<100000;i++){
        printf("count = %d\n",count);

        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}

int main(void){
    int rc, t;
    int nThreads = 12;
    pthread_t threads [nThreads];
    int *taskIDs [nThreads];
    pthread_mutex_init(&mutex,NULL);

    for (int i=0; i<nThreads;i++){

        taskIDs[i] = (int*) malloc(sizeof(int));
        *taskIDs[i] = i;
        

        rc = pthread_create(&threads[i],NULL,identifyThread,(void*)taskIDs[i]);
        //pthread create takes for paramaters
        //1. the pointer to the thread
        //2. the attributes of the thread.
        //3. A pointer to a routine to start
        //4. Any arguments that the routine will need.

         
    }
    pthread_exit(NULL);
    

    




    return 0;


}