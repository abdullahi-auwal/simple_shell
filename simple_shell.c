#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * main - This is a UNIX command line interpreter
 * @argc: number of arguments to the main(not the interpreter)
 * @argv: pointer to the array of the arguments
 * @envp: pointer to the environment variables
 *
 * Return: returns 0 when interrupted after successfully running
 */
int main(void)
{
	pid_t pid;
	ssize_t getl;
	int n;
	int status;
	char *lineptr = NULL;
	size_t len = 0;
	char *shenv[] = {
		"PATH=/usr/bin:/bin:/usr/local/bin",
		NULL
	};

	while (1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("simple_shell: fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			printf("simple_shell$ ");
			getl = getline(&lineptr, &len, stdin);
			if (getl == -1)
			{
				if (feof(stdin))
				{
					free(lineptr);
					return (0);
				}
				free(lineptr);
				perror("simple_shell: getline");
				_exit(EXIT_FAILURE);
			}
			if (getl > 0)
				lineptr[getl - 1] = '\0';

			char *const shargv[] = {
				lineptr,
				NULL
			};

			n = execve(lineptr, shargv, shenv);
			if (n == -1)
			{
				free(lineptr);
				perror("simple_shell: execve");
				_exit(EXIT_FAILURE);
			}
		}
		if (pid > 0)
		{
			wait(&status);
		}
	}
	free(lineptr);
	return (0);
}
