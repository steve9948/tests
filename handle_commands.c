#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

/**
 * executeCommand - Execute the user's command with arguments using execvp.
 * @command: The command to execute.
 */
void executeCommand(char *command);

/**
 * main - Entry point of the simple shell program.
 *
 * This program implements a basic shell that repeatedly prompts the user
 * for a command and its arguments, then executes that command using execvp.
 * The user can exit the shell by pressing Ctrl+D or entering an
 * end-of-file marker.
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("$ ");
		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		executeCommand(input);
	}

	return (0);
}

void executeCommand(char *command)
{
	char *args[MAX_INPUT_LENGTH];
	char *token;
	int argCount = 0;

	for (token = strtok(command, " "); token != NULL; token = strtok(NULL, " "))
	{
		args[argCount++] = token;
	}
	args[argCount] = NULL;

	pid_t pid = fork();

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

