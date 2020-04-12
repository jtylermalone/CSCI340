#include <assert.h>
#include <pthread.h>
#include <stdio.h>

int state_var = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_signal() {
    assert(pthread_mutex_lock(&m) == 0);
    state_var = 1;
    assert(pthread_cond_signal(&c) == 0);
    assert(pthread_mutex_unlock(&m) == 0);
}

void thr_wait() {
    printf("in wait\n\n");
    assert(pthread_mutex_lock(&m) == 0);
    while (state_var == 0) {
        printf("in while\n\n");
        assert(pthread_cond_wait(&c, &m) == 0);
    }
    assert(pthread_mutex_unlock(&m) == 0);
}

void *child(void *arg) {
    printf("Child: Start\n\n");
    thr_signal();
    printf("Child: After Signal\n");
    return NULL;
}

int main( int argc, char *argv[]) {
    printf("Parent: Start\n\n");
    
    pthread_t p;
    printf("creating child...\n\n");
    assert(pthread_create(&p, NULL, child, NULL) == 0);
    
    printf("about to wait\n\n");
    thr_wait();
    printf("Parent: After waiting for child\n");

    void * rc;
    assert(pthread_join(p, &rc) == 0);
 
    printf("Parent: End\n");
    return 0;
}
