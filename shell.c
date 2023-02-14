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
	int status, i;
	char *stkn;

	while (1)
	{
		printf("#shell$ ");
		getline(&line, &len, stdin);
		stkn = strtok(line, " \n");
		av = malloc(sizeof(char *) * 32);
		line[strcspn(line, "\n")] = 0;
		av[0] = stkn;
		if (strcmp(av[0], "exit") == 0)
			exit(0);
		i = 1;
		while (stkn != NULL)
		{
			stkn  = strtok(NULL, " \n");
			av[i] = stkn;
			i++;
		}
		child = fork();
		if  (child == -1)
		{
			perror("Error");
			return (0);
		}
		else if (child == 0)
		{
			if (execve(line, av, NULL) == -1)
			{
				perror("./shell");
				return (1);
			}
			execve(av[0], av, NULL);
		}
		else
			wait(&status);
	}
	free(line);
	return (0);
}
