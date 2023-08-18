#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function Declarations */
void cleanUpAndExit(char *line);
void executeCommand(char *command);

/**
 * main - Entry point for the shell program.
 *
 * This program implements a basic shell that repeatedly prompts the user
 * for a command and then executes that command in a child process.
 * The user can exit the shell by pressing Ctrl+D or entering an
 * end-of-file marker.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	ssize_t read;
	size_t len = 0;
	pid_t pid;

	/* Main Loop */
	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
	if (read == -1)
	{
		if (feof(stdin))
		{
			putchar('\n');
			break;
		}
		else
		{
			perror("getline");
			cleanUpAndExit(line);
		}
	}

	if (line[read - 1] == '\n')
	line[read - 1] = '\0';
/**
* Forking and Execution
*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		cleanUpAndExit(line);
	}
	else if (pid == 0)
	{
		executeCommand(line);
	}
	else
	{
		wait(NULL);
	}
	}

	cleanUpAndExit(line);
	return (0);
}

/**
 * cleanUpAndExit - Frees memory and exits the program.
 * @line: Pointer to the memory allocated for input line.
 */
void cleanUpAndExit(char *line)
{
	free(line);
	exit(EXIT_SUCCESS);
}

/**
 * executeCommand - Executes a command using the execve function.
 * @command: The command to be executed.
 */
void executeCommand(char *command)
{
	if (access(command, X_OK) == 0)
	{
	if (execve(command, (char *[])
				{
				command, NULL
				}
				, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	}
	else
	{
		char *systemPath = "/bin/";
		char *fullPath = malloc(strlen(systemPath) + strlen(command) + 1);

		if (fullPath == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

strcpy(fullPath, systemPath);
strcat(fullPath, command);

	if (execve(fullPath, (char *[])
				{
				fullPath, NULL
				}
				, NULL) == -1)
	{
		perror("execve");
		free(fullPath);
		exit(EXIT_FAILURE);
	}
	free(fullPath);
	}
}

