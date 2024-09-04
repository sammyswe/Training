#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>  

#define BUFFER_SIZE 10


char buffer[BUFFER_SIZE];
int i = 0;

// Semaphores
sem_t *SpaceLeft; 
sem_t *SpaceUsed;
 
pthread_mutex_t mutex; //stops race condition with buffer index (i)

void *producer(void *tid) { //infinitely produces 1 per second until program stopped or spaceleft sem = 0 (space used up)
    while (1) {
        sem_wait(SpaceLeft);

        pthread_mutex_lock(&mutex);

        
        if (i < BUFFER_SIZE) { // Ensure the index is within bounds
            buffer[i] = 'A';
            printf("Producer: Inserted '%c' at position %d\n", buffer[i], i);
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(SpaceUsed); //spaceused +1

        sleep(1); //produce 1 per second
    }

    return NULL;
}

void *consumer(void *tid) { //consumes 1 every three left.
    while (1) {

        sem_wait(SpaceUsed); // make sure there is something to consume
        
        pthread_mutex_lock(&mutex);

        if (i > 0) { // Ensure we don't access below 0
            i--;
            printf("Consumer: Consumed '%c' from position %d\n", buffer[i], i);
        }

        pthread_mutex_unlock(&mutex);
        sem_post(SpaceLeft); //spaceleft +1, because char has been consumed
        sleep(4);
    }

    return NULL;
}

int main(void) {
    int nThreads = 2;
    pthread_t threads[nThreads];

    //close semaphores from previous run
    sem_close(SpaceLeft);
    sem_close(SpaceUsed);
    sem_unlink("/SpaceLeft");
    sem_unlink("/SpaceUsed");

    SpaceLeft = sem_open("/SpaceLeft", O_CREAT, 0644, BUFFER_SIZE);  // 0 items - Space left = whole buffer
    SpaceUsed = sem_open("/SpaceUsed", O_CREAT, 0644, 0);  // 0 space used

    if (SpaceLeft == SEM_FAILED || SpaceUsed == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    // Wait for the threads to finish (which in this case, they never will)
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

