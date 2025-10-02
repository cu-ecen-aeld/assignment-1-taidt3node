#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long counter = 0;
pthread_mutex_t lock;

void *threadFunction(void *arg) {
    size_t count = 1000000;
    for (size_t i = 0; i < count; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread_1;
    pthread_t thread_2;
    pthread_t thread_3;
    int result;

    // Init Mutex lock
    pthread_mutex_init(&lock, NULL);

    // Create the thread 1
    result = pthread_create(&thread_1, NULL, threadFunction, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }

    // Create the thread 2
    result = pthread_create(&thread_2, NULL, threadFunction, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }

    result = pthread_create(&thread_3, NULL, threadFunction, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return EXIT_FAILURE;
    }
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);

    // Wait for the thread to finish
    // pthread_join(thread, NULL);
    printf("Counter = %lu\n", counter);
    printf("Thread has finished execution\n");
    return EXIT_SUCCESS;
}