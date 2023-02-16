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
	char *line = NULL, *stkn, *command, *token, *path;
	size_t len = 0;
	pid_t child;
	int status, i;

	while (1)
	{
		printf("#shell$ ");
		if (getline(&line, &len, stdin) == -1)
			return (1);
		stkn = strtok(line, "\n");
		path = getenv("PATH");
		token = strtok(path, ":");
		av = malloc(sizeof(char *) * 32);
		command = malloc(1024);
		if (!av || !command)
			return (0);
		line[strcspn(line, "\n")] = 0;
		av[0] = stkn;
		i = 1;
		while (stkn != NULL)
		{
			stkn  = strtok(NULL, "\n");
			av[i] = stkn;
			i++;
		}
		if (strcmp(av[0], "exit") == 0 && (av[1] == NULL))
			exit(0);
		if (access(av[0], X_OK) == 0)
		{
			child = fork();
			if  (child == -1)
			{
				perror("./shell");
				return (1);
			}
			else if (child == 0)
			{
				if (execve(av[0], av, NULL) == -1)
				{
					perror("./shell");
					return (1);
				}
			}
			else
				wait(&status);
		}
		else
		{
			while (token)
			{
				strcpy(command, token);
				strcat(command, "/");
				strcat(command, av[0]);
				if (access(command, X_OK) == 0)
				{
					child = fork();
					if (child == -1)
					{
						perror("./shell");
						return (1);
					}
					else if(child == 0)
					{
						if (execve(command, av, NULL) == -1)
						{
							perror("./shell");
							return (1);
						}
					}
				else
					wait(&status);
				}
				token = strtok(NULL, ":");
			}
		}
		perror("./shell");
		return (1);
	}
	free(line);
	free(av);
	free(command);
	return (0);
}
