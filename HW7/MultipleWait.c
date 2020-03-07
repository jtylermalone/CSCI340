#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

int state_var = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t c2 = PTHREAD_COND_INITIALIZER;

void *thread_1() {
	
	assert(pthread_mutex_lock(&m) == 0);
    printf("in thread 1\n");
    state_var = 1;
    pthread_cond_signal(&c1);
    
    pthread_mutex_unlock(&m);

}

void *thread_2() {

	assert(pthread_mutex_lock(&m) == 0);
	printf("in thread 2\n");
	pthread_cond_signal(&c2);
	pthread_mutex_unlock(&m);

}

int main() {

	printf("Main task starting...\n");
	sleep(1);
	// Create the threads
    pthread_t p1;   
    if (pthread_create(&p1, NULL, thread_1, NULL) != 0) {
        printf("Unable to create thread\n");
        exit(1);
    }
  
	
    pthread_t p2;
    if (pthread_create(&p2, NULL, thread_2, NULL) != 0) {
        printf("Unable to create thread\n");
        exit(1);
    }
	

	//pthread_join(p1, NULL);
	
	if (pthread_cond_wait(&c2, &m) == 0)
		printf("thread 2 has signaled\n");
	

	if (pthread_cond_wait(&c1, &m) == 0)
		printf("thread 1 has signaled\n");

	
}





