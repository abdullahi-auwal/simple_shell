#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * main - This is a UNIX command line interpreter
 *
 * Return: returns 0 when interrupted after successfully running
 */
int main(void)
{
	char *lineptr = NULL;
	pid_t pid;
	ssize_t getl;
	int status;
	size_t len = 0;

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
			exec_program(lineptr);
		}
		if (pid > 0)
		{
			wait(&status);
		}
	}
	free(lineptr);
	return (0);
}



/**
 * exec_program - execute commands
 * @lineptr: pointer to the command to execute
 */
void exec_program(char *lineptr)
{
	int n;
	char *shargv[2];
	char *shenv[] = {
		"PATH=/usr/bin:/bin:/usr/local/bin",
		NULL
	};

	shargv[0] = lineptr;
	shargv[1] = NULL;

	n = execve(lineptr, shargv, shenv);
	if (n == -1)
	{
		free(lineptr);
		perror("simple_shell: execve");
		_exit(EXIT_FAILURE);
	};
}
