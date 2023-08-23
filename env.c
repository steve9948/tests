#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

/**
 * executeCommand - Execute command with arguments using execvp.
 * @command: The command to be executed.
 *
 * Rturn: Always(0)
 */

/*Declare an external environment*/
extern char **environ;
/*Prototype to cmmand method*/
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
		
		/*Check for built-in command "exit"*/
		if (strcmp(input, "exit") == 0)
		{
			printf("Exiting the shell.\n");
			break;
		}
		/*Check for built-in command "env"*/
		else if (strcmp(input, "env") == 0)
		{
			char **env = environ;
			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else
		{
			executeCommand(input);
		}
	}
	return 0;
}

/**
 * executeCommand - Execute command with arguments using execvp.
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
	args[argCount] = NULL;  /*Null-terminate the args array*/

	/* Create a child process*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)  /* Child process*/
	{
		/* Execute the command with arguments*/
		execvp(args[0], args);
		perror("execvp");  /*Print an error message*/
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);/*Parent process awaits for child process*/
	}
}
