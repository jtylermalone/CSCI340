#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int list[20];
	memset(list, -2, 10 * sizeof(int));
	for(int i = 0; i < 10; i++){
		printf("%i\n", list[i]);
	}
}
