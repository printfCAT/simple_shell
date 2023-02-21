#include "shell.h"
/**
* main - simple shell
*
* Return: 0
*/
int main(void)
{
	char *command = (char *) malloc(sizeof(char *) * MAX_COMMAND_LENGTH);
	char *args[MAX_NUM_ARGUMENTS], *token, **env, *full_path;
	char prompt[MAX_COMMAND_LENGTH] = "#shell$ ";
	int i, status;
	ssize_t bytes_read;
	size_t size = 0;
	pid_t pid;

	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);

		bytes_read = getline(&command, &size, stdin);
		if (bytes_read == -1)
		{
			printf("\n");
			break;
		}
		command[bytes_read - 1] = '\0';
		i = 0;
		token = strtok(command, " ");
		while (token != NULL && i < MAX_NUM_ARGUMENTS - 1)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		if (strcmp(args[0], "exit") == 0)
			exit(0);
		if (strcmp(args[0], "env") == 0)
		{
			env = environ;
			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			continue;
		}
		full_path = get_full_path(args[0]);
		if (full_path == NULL)
		{
			printf("%s: command not found\n", args[0]);
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			execve(full_path, args, environ);
			perror(full_path);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			free(full_path);
		}
	}
	free(command);
	return (0);
}
