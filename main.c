#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	extern char **environ;

	if (argc != 1)
	{
		printf("Are you mad!\n");
		return (0);
	}
	printf("%s - good boy\n", argv[0]);
	return (0);
}
