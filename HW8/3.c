#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t signal;

void thr_signal() {
    assert(sem_post(&signal) == 0);
}

void thr_wait() {
    assert(sem_wait(&signal) == 0);
}

void *child(void *arg) {
    printf("Child Start\n");
    thr_signal();
    printf("child: After Signal\n");
    return NULL;
}

int main(int argc, char*argv[]) {
    printf("Parent: Start\n");

    assert(sem_init(&signal, 0, 1) == 0);
    
    pthread_t p;
    assert(pthread_create(&p, NULL, child, NULL) == 0);

    thr_wait();
    printf("Parent: After waiting for child\n");

    void * rc;
    assert(pthread_join(p, &rc) == 0);

    printf("Parent: End\n");
    return 0;
}
