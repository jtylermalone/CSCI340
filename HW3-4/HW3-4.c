#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {
    
	// args is the array that will be passed
	// to execvp below. the first element of 
	// args will be the command to be called,
	// and each subsequent element in args 
	// will be one of the arguments for that
	// command.
    char *args[10];
	// I have to keep track of the size of 
	// args because, below, I need to set the
	// last element of args as NULL. execvp
	// knows to stop reading arguments once
	// it reaches NULL.
    int argsSize = 0;

	// setting the first element in args to
	// be the command to be executed.
	args[0] = argv[1];
	
	// if argc is < 2, there aren't any 
	// arguments to pass to the command,
	// so we don't need to worry about 
	// assigning elements of args with
	// arguments.
	if (argc >= 2) {
		for (int i = 2; i < argc; i++) {
			int argsPos = i - 1;
			args[argsPos] = argv[i];
			argsSize += 1;
		}
	}

	// setting last element of args as NULL
	args[argsSize + 1] = NULL;
	
	
	// fork() returns 0 if the current
	// process is a child process, and
	// a positive integer otherwise
	int PID = fork();
	if (PID == 0) {
		// child process
		execvp(args[0], args);
		printf("\n\n");
		_exit(1);

	}
	else {
		// using wait here allows the child
		// to finish running before the parent
		// executes. when I don't use wait here,
		// these processes never really finish
		wait(NULL);
		
	
	}	

    return 0;
}
