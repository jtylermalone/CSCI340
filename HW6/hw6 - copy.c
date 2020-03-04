#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

char *global_string;
char *string_characters = "Tyler";

pthread_mutex_t lock;


struct params {

	int string_length;
	int thread_number;
	int thread_count;

};

void *construct_string(void *arg) {
	struct params *parameters = (struct params *) arg;
	
	int current_string_length = strlen(global_string);	
	printf("\nCurrent thread ID: %d\n", parameters->thread_number);
	printf("current string length: %d\n", current_string_length);
	printf("parameters->string_length: %d\n", parameters->string_length);
	for (int i = 0
	if (strlen(global_string) < parameters->string_length) {
		//printf("max length: %d\n", parameters->string_length);
		printf("strlen(global_string): %d\n", strlen(global_string));
		assert(pthread_mutex_lock(&lock) == 0);
		int add_char = strlen(global_string) % strlen(string_characters);
		printf("add char: %d\n", add_char);
		global_string[current_string_length] = (char)string_characters[add_char];
		assert(pthread_mutex_unlock(&lock) == 0);
		printf("Character being added: %c\n\n", global_string[current_string_length]);
		current_string_length = current_string_length + 1;
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
		parameters->thread_number = i + 1;
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
