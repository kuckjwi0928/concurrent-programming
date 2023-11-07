#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *mutex() {
    if (pthread_mutex_lock(&mut) != 0) {
        perror("pthread_mutex_lock");
        exit(-1);
    }
    if (pthread_mutex_unlock(&mut) != 0) {
        perror("pthread_mutex_unlock");
        exit(-1);
    }
    return NULL;
}

int main() {
    pthread_t th1, th2;
    if (pthread_create(&th1, NULL, mutex, NULL) != 0) {
        perror("pthread_create");
        return -1;
    }
    if (pthread_create(&th2, NULL, mutex, NULL) != 0) {
        perror("pthread_create");
        return -1;
    }
    if (pthread_join(th1, NULL) != 0) {
        perror("pthread_join");
        return -1;
    }
    if (pthread_join(th2, NULL) != 0) {
        perror("pthread_join");
        return -1;
    }
    if (pthread_mutex_destroy(&mut) != 0) {
        perror("pthread_mutex_destroy");
        return -1;
    }
    uint64_t tid;
    pthread_threadid_np(NULL, &tid);
    printf("thread id %llu\n", tid);
    return 0;
}
