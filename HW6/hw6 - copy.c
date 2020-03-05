#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

char *global_string;
char *string_characters = "Tyler";

void *construct_string(void *arg) {
	printf("Current thread ID: %u\n", pthread_self());
	int desired_string_length = arg;
	int current_string_length = strlen(global_string);
	if (current_string_length < desired_string_length) {
		char add_char = current_string_length % 5;
		global_string[current_string_length] = (char)string_characters[add_char];
		printf("Character being added: %c\n", global_string[current_string_length]);
		current_string_length = current_string_length + 1;
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	
	int number_of_threads = atoi(argv[1]);
	int length_of_string = atoi(argv[2]);
	global_string = malloc(length_of_string * sizeof(char));
	memset(global_string, '\0', (length_of_string * sizeof(char)));
	pthread_t thread_names[number_of_threads];

	pthread_t *threads = malloc(sizeof(pthread_t) * number_of_threads);
	for (int i = 0; i < number_of_threads; i++) {
		if (pthread_create(&threads[i], NULL, &construct_string, length_of_string) != 0) {

			printf("Unable to create thread\n");
			exit(1);

		}
	}

	for (int i = 0; i < number_of_threads; i++) {
		 pthread_join(threads[i], NULL); 
	}

	printf("Final string: %s\n", global_string);	
}
