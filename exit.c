#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

/**
 * executeCommand - Execute command with arguments using execvp function.
 * @command: The command to be executed.
 *
 * Return (Always 0)
 */

void executeCommand(char *command);

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
		/* Check for built-in command "exit" */
		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting the shell.\n");
			break;
		}
		executeCommand(input);
	}
	return (0);
}

/**
 * executeCommand - Execute command with arguments using execvp function.
 * @command: The command to be executed.
 *
 */
void executeCommand(char *command)
{
	pid_t pid;
	char *args[MAX_LENGTH];
	int argCount = 0;
	/*Tokenize the command into arguments*/
	char *argToken = strtok(command, " ");
	while (argToken != NULL)

	{
		args[argCount++] = argToken;
		argToken = strtok(NULL, " ");
	}
	/* Null-terminate the args array */
	args[argCount] = NULL
	/*Create a child process*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)  /*Child process*/
	{
		/* Execute the command with arguments*/
		execvp(args[0], args);
		/*Print an error message if execvp fails*/
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);  /*Parent process waits for child to complete*/
	}
}
