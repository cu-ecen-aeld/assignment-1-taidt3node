#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int shared_data = 0;               // tài nguyên dữ liệu chung
pthread_rwlock_t rwlock;           // read-write lock

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_rwlock_rdlock(&rwlock);  // khóa đọc
        printf("Reader %d đọc giá trị: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock);
        usleep(500000); // 0.5s ngủ để mô phỏng công việc
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_rwlock_wrlock(&rwlock);  // khóa ghi
        shared_data++;
        printf("Writer %d ghi giá trị mới: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock);
        sleep(1); // ngủ để mô phỏng công việc
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int ids_readers[NUM_READERS], ids_writers[NUM_WRITERS];

    pthread_rwlock_init(&rwlock, NULL);

    // tạo các luồng Writer
    for (int i = 0; i < NUM_WRITERS; i++) {
        ids_writers[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids_writers[i]);
    }

    // tạo các luồng Reader
    for (int i = 0; i < NUM_READERS; i++) {
        ids_readers[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids_readers[i]);
    }

    // join để chờ luồng kết thúc (trong ví dụ này vòng lặp vô hạn)
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}