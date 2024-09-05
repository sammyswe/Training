#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>  

#define MAX_READERS 5 //Readers precedence

int shared_data = 0;
int reader_count = 0;

sem_t *resource_access;  // Protects access to shared data
pthread_mutex_t reader_count_mutex;  // avoid race condition on read count

void *reader(void *tid) {
    while (1) {
        pthread_mutex_lock(&reader_count_mutex);
        reader_count++;
        if (reader_count == 1) //check only on first reader (after that we know resource is free to read)
            sem_wait(resource_access);  
        pthread_mutex_unlock(&reader_count_mutex);

        printf("Reader %d: read shared_data = %d\n", *((int *)tid), shared_data);
        sleep(1);  

        pthread_mutex_lock(&reader_count_mutex);
        reader_count--;
        if (reader_count == 0)
            sem_post(resource_access);  
        pthread_mutex_unlock(&reader_count_mutex);

        sleep(1);  
    }

    return NULL;
}

void *writer(void *tid) {
    while (1) {
        sem_wait(resource_access);  // When theres no readers, it can update

        shared_data++;
        printf("Writer %d: updated shared_data to %d\n", *((int *)tid), shared_data);

        sem_post(resource_access);  // allows readers to enter

        sleep(2);  
    }

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writer_thread;
    int ids[MAX_READERS];

    sem_close(resource_access);
    sem_unlink("/resource_access");  // Unlink if a previous run did not clean it up
    resource_access = sem_open("/resource_access", O_CREAT, 0644, 1);  //create if not exist


    pthread_mutex_init(&reader_count_mutex, NULL);

    for (int i = 0; i < MAX_READERS; i++) {//creates threads for many readers.
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    int writer_id = 1;
    pthread_create(&writer_thread, NULL, writer, &writer_id);//creates single writing thread

    for (int i = 0; i < MAX_READERS; i++) //joins all threads
        pthread_join(readers[i], NULL);
    pthread_join(writer_thread, NULL);

    
    pthread_mutex_destroy(&reader_count_mutex);

    return 0;
}
