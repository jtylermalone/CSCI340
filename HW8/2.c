#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int max = 5;
int counter = 0;

sem_t lock;

void *mythread(void *arg) {

    char *letter = arg;
    
    for (int i = 0; i < max; i++) {
        printf("thread %s: in loop\n", letter);
        assert(sem_wait(&lock) == 0);
        printf("lock...%d", lock);
        counter = counter + 1;
        printf("counter: %d\n", counter);
        assert(sem_post(&lock) == 0);

    }
    
    printf("%s: done\n", letter);
    return NULL;
}

int main(int argc, char *argv[]) {

    if (argc!= 2) {
        fprintf(stderr, "usage: SemaphoreLocking <loopcount>\n");
        exit(1);
    }
  
    max = atoi(argv[1]);

    printf("main: begin[counter = %d] [%p]\n", counter, &counter);

    // Initialize the lock
    assert(sem_init(&lock, 0, 1) == 0);

    // Create the threads
    pthread_t p1;
    assert(pthread_create(&p1, NULL, mythread, "A") == 0);

    pthread_t p2;
    assert(pthread_create(&p2, NULL, mythread, "B") == 0);

    // join waits for the threads to finish

    assert(pthread_join(p1, NULL) == 0);
    assert(pthread_join(p2, NULL) == 0);

    printf("main: done\n [counter:%d]\n [should: %d\n",
           counter, max*2);

    return 0;
}





