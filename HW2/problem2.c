#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	// the variable 'size' will hold, as an int, the paramater passed through
	// the command line. atoi(argv[1]) converts argv[1] from an ascii character
	// to a usable integer.
	int size = atoi(argv[1]);

  	// malloc(size) allots size bytes. since each int is 4 bytes, we need to
	// allocate 4 * size bytes (i think!).... sizeof(int) == 4. 
	int *memBlock = malloc(size * sizeof(int));

	// below, we are filling in a chunk of memory with zeros, starting at the 
	// address of memblock. each 4 bytes will hold a zero. Since each
	// int is 4 bytes, we need to fill size * 4 bytes with zeros.
	memset(memBlock, 0, size * sizeof(int));

	// here, we are simply printing the address of memBlock. This is the 
	// address where memBlock starts.
	printf("Location of memory block: <%p>\n", &memBlock);
	printf("\nHere is each element of the allocated memory in hex value:\n"); 
	
	// here, we loop through every 4 bytes of memBlock and print the value (in hex) located
	// at each 4 bytes. it should always print zero.
	for (int i = 0; i < size; i++)
	{	
		printf("hex: %x\n", *(memBlock + i)); // print memory block contents in hex
	}
	
	// it would be wasteful to keep using the memory allotted above, so
	// here we are freeing it up.
	free(memBlock);
}

