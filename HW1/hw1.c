#include<stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		// argv[i] will contain each parameter in succession as the loop runs
		printf("%p\n", argv[i]);
	}
}
