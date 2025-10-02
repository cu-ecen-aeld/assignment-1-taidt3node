#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int data;
int data_ready = 0;
int finished = 0;   // signal when producer is done
pthread_cond_t cond;
pthread_cond_t cond;
pthread_mutex_t lock;

int random_number_generator() {
    return (rand() % 100); // Generate a random number between 0 and 99
}

void *threadProducer(void *arg) {
    int count = 10;
    for (int i = 0; i < count; i++)
    {
        printf("Producer thread...\n");
        pthread_mutex_lock(&lock);
        data = random_number_generator();
        data_ready = 1;
        pthread_cond_signal(&cond);  // wake one waiting thread
        pthread_mutex_unlock(&lock);
        sleep(1); // Sleep for a while to simulate time taken to produce data
    }
    // notify consumer that we are finished
    pthread_mutex_lock(&lock);
    finished = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *threadConsumer(void *arg) {
    while (1) 
    {
        pthread_mutex_lock(&lock);
         while (!data_ready && !finished) {
            pthread_cond_wait(&cond, &lock);
        }

        if (finished && !data_ready) {
            break;  // exit gracefully after all data consumed
        }
        printf("Consumer thread...\n");
        printf("Data = %d\n", data);
        data_ready = 0;
        pthread_mutex_unlock(&lock);
    }   
    return NULL;
}

int main() {
    pthread_t thread_1;
    pthread_t thread_2;

    int result;

    // Init Mutex lock
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    // Create the thread 1
    result = pthread_create(&thread_1, NULL, threadProducer, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }
    // Create the thread 2
    result = pthread_create(&thread_2, NULL, threadConsumer, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }
    
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("Thread has finished execution\n");
    return EXIT_SUCCESS;
}