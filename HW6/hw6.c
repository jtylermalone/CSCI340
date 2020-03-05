#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>



// this is the string that will ultimately
// be constructed/printed at the end
char *global_string;

// these are the characters that will be 
// added to global_string one at a time.
char *string_characters = "Tyler + c == disaster ";

// using locks but not sure if it's necessary
// or actually doing anything
pthread_mutex_t lock;

// this struct is the set of parameters that will be
// passed to each thread.
struct params {

	int string_length; // holds 2nd parameter (desired length of string)
	int thread_id; // holds thread id
	int thread_count; // holds 1st parameter (total number of threads)

};

// method that each thread executes
void *construct_string(void *arg) {

	// instantiating passed parameter struct so we can
	// access it in here
	struct params *parameters = (struct params *) arg;
		
	// printing thread id as required
	printf("\nCurrent thread ID: %d\n", parameters->thread_id);
	
	// this checks whether the string has reached the specified length
	// ... I'm using a for loop because I need the 'i' throughout
	// the loop (truthfully I probably don't *NEED* the 'i', but I
	// finally got this to work by using the 'i' so that's what we're
	// sticking with)
	for (int i = 0; i < parameters->string_length; i++) {

		// we only add to global_string if i % number of threads == current thread id...
		// this works for some reason.
		if (i % parameters->thread_count == parameters->thread_id) {

			// locking... again, not sure if necessary
			assert(pthread_mutex_lock(&lock) == 0);
			// getting index of string_characters to add to global_string
			int add_char = strlen(global_string) % strlen(string_characters);
			// adding character @ string_characters[add_char] to global_string
			global_string[strlen(global_string)] = (char)string_characters[add_char];
			// unlocking
			assert(pthread_mutex_unlock(&lock) == 0);

		// printing character being added to string
		printf("Character being added: %c\n\n", global_string[strlen(global_string) - 1]);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	
	// getting both command line arguments
	int number_of_threads = atoi(argv[1]);
	int length_of_string = atoi(argv[2]);

	// making space for global_string and setting all characters
	// to NULL
	global_string = malloc(length_of_string * sizeof(char));
	memset(global_string, '\0', (length_of_string * sizeof(char)));

	// creating array of threads
	pthread_t *threads = malloc(sizeof(pthread_t) * number_of_threads);

	// initializing lock...not sure if locking is
	// necessary or if it's actually doing anything 
	// here but I'm doing it
	assert(pthread_mutex_init(&lock, NULL) == 0);

	// adding to threads array and creating each thread
	// as it's added to the array
	for (int i = 0; i < number_of_threads; i++) {

		// creating params struct and populating its fields
		// with the appropriate data.
		struct params *parameters = malloc(sizeof(struct params));
		parameters->string_length = length_of_string;
		parameters->thread_id = i;
		parameters->thread_count = number_of_threads;

		// here's where each thread gets created
		if (pthread_create(&threads[i], NULL, &construct_string, (void *)parameters) != 0) {
			printf("Unable to create thread\n");
			exit(1);

		}
	}
	
	// must joing threads here so they will execute
	for (int i = 0; i < number_of_threads; i++) {
		 pthread_join(threads[i], NULL); 
	}

	// printing final string
	printf("Final string: %s\n", global_string);	
}
