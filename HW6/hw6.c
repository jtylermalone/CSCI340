#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

char *global_string;
char *string_characters = "Tyler + c == disaster ";

pthread_mutex_t lock;


struct params {

	int string_length;
	int thread_number;
	int thread_count;

};

void *construct_string(void *arg) {
	struct params *parameters = (struct params *) arg;
		
	printf("\nCurrent thread ID: %d\n", parameters->thread_number);
	//printf("current string length: %ld\n", strlen(global_string));
	//printf("parameters->string_length: %d\n", parameters->string_length);
	//printf("mod value: %ld\n", strlen(global_string) % parameters->thread_count);
	//while (strlen(global_string) < parameters->string_length) {
	for (int i = 0; i < parameters->string_length; i++) {
		if (i % parameters->thread_count == parameters->thread_number) {
		//printf("max length: %d\n", parameters->string_length);
		//printf("strlen(global_string): %ld\n", strlen(global_string));
		assert(pthread_mutex_lock(&lock) == 0);
		int add_char = strlen(global_string) % strlen(string_characters);
		//printf("add char: %d\n", add_char);
		global_string[strlen(global_string)] = (char)string_characters[add_char];
		assert(pthread_mutex_unlock(&lock) == 0);
		printf("Character being added: %c\n\n", global_string[strlen(global_string) - 1]);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	
	int number_of_threads = atoi(argv[1]);
	int length_of_string = atoi(argv[2]);
	global_string = malloc(length_of_string * sizeof(char));
	memset(global_string, '\0', (length_of_string * sizeof(char)));
	pthread_t *threads = malloc(sizeof(pthread_t) * number_of_threads);
	assert(pthread_mutex_init(&lock, NULL) == 0);

	for (int i = 0; i < number_of_threads; i++) {
		struct params *parameters = malloc(sizeof(struct params));
		parameters->string_length = length_of_string;
		parameters->thread_number = i;
		parameters->thread_count = number_of_threads;
		if (pthread_create(&threads[i], NULL, &construct_string, (void *)parameters) != 0) {
			printf("Unable to create thread\n");
			exit(1);

		}
	}

	for (int i = 0; i < number_of_threads; i++) {
		 pthread_join(threads[i], NULL); 
	}

	printf("Final string: %s\n", global_string);	
}
