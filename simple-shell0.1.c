#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

/**
 * executeCommand - Execute the user's command using execlp.
 * @command: The command to execute.
 */
void executeCommand(char *command);

/**
 * main - Entry point of the simple shell program.
 * 
 *
 * Main : A basic shell that repeatedly prompts the user
 * for a command and then executes that command using execlp.
 * The user can exit the shell by pressing Ctrl+D or entering an
 * end-of-file marker.
 *
 * Return: Always 0.
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

    return 0;
}

/**
 * executeCommand - Execute the user's command using execlp.
 * @command: The command to execute.
 */
void executeCommand(char *command)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        if (execlp(command, command, NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
    }
}
