#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

void executeCommand(char *command);

/**
 * executeCommand - Execute the user's command with arguments using execvp.
 * @command: The command to execute.
 *
 * This function tokenizes input into arguments and attempts to execute
 * the provided command with its arguments using the execvp system call.
 * It forks a child process to execute command, and the pp waits for it.
 * If the command is not found or encounters an erroet nu.
 */

int main(void)
{
	char input[MAX_LENGTH];

	while (1)

	{
		printf("$ ");
		if (fgets(input, MAX_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		executeCommand(input);
	}

	return (0);
}
/**
 *
 * Tokenize the command
 * Add argument token to args array
 * Get the next argument token
 * Null-terminate the args array
 * Print an error message
 *
 */

void executeCommand(char *command)
{
	pid_t pid;
	char *args[MAX_LENGTH];
	char *argToken;
	int argCount = 0;

	argToken = strtok(command, " ");
	while (argToken != NULL)
	{
		args[argCount++] = argToken;
		argToken = strtok(NULL, " ");
	}
	args[argCount] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

