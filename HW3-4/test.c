#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(void) {
	pid_t child;
	int cstatus;
	pid_t c;
	char *args[3];

	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;

	if ((child = fork()) == 0) {
		printf("Child: PID of CHILD = %ld\n", (long) getpid());
		execvp(args[0], args);
		fprintf(stderr, "Child process could not do execvp.\n");
		_exit(1);
	}
	else {
		if (child == (pid_t)(-1)) {
			fprintf(stderr, "Fork failed.\n");
			_exit(1);
		}
		else {
			c = wait (&cstatus);
			printf("Parent: Child %ld exited with status = %d\n", (long) c, cstatus);
		}
	}
	return 0;
}
