#include "shell.h"
/**
* get_full_path - finds full path of PATH
* @command: input from user
*
* Return: full path. NULL if unsuccessful
*/
char *get_full_path(char *command)
{
	char *path, *token, *full_path;

	setenv("PATH", "/bin:/usr/bin", 1);
	path = getenv("PATH");
	if (access(command, X_OK) == 0)
		return (command);
		token = strtok(path, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
