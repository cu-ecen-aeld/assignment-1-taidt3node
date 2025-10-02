#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *threadFunction(void *arg) {
    pthread_t currentThread = pthread_self();  // Get the current thread ID
    printf("Current thread ID: %lu\n", (unsigned long)currentThread);
    return NULL;
}

int main() {
    pthread_t thread_1;
    pthread_t thread_2;
    int result;

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
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    // Wait for the thread to finish
    // pthread_join(thread, NULL);

    printf("Thread has finished execution\n");
    return EXIT_SUCCESS;
}