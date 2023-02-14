#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
/**
* main - simple shell
* @ac: number of items in av
* @av: NULL terminated array of strings
*
* Return: 0
*/
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	pid_t child;
	int status;

	while (1)
	{
		printf("#shell$ ");
		if (getline(&line, &len, stdin) == -1)
			return (1);
		line[strcspn(line, "\n")] = 0;
		av[0] = line;
		av[1] = NULL;
		child = fork();
		if (child == 0)
		{
			if (execve(line, av, NULL) == -1)
			{
				perror("./shell");
				return (1);
			}
		}
		else if (child > 0)
			wait(&status);
		else
			perror("./shell");
	}
	free(line);
	return (0);
}
