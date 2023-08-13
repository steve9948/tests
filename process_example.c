#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Entry point of the program.
 *
 * This program creates 5 child processes, each executing the "ls -l /tmp" command.
 * The parent process waits for each child to exit before creating a new child.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
    // Loop to create 5 child processes
    for (int i = 0; i < 5; i++)
    {
        pid_t child_pid = fork(); // Create a new child process

        // Check for fork error
        if (child_pid == -1)
        {
            perror("fork failed");
            exit(1);
        }
        // Child process
        else if (child_pid == 0)
        {
            printf("Child %d executing...\n", i + 1);

            // Arguments for the ls command
            char *args[] = {"ls", "-l", "/tmp", NULL};
            execvp("ls", args); // Execute the ls command

            // If execvp fails, print an error
            perror("execvp failed");
            exit(1);
        }
        // Parent process
        else
        {
            int status;
            waitpid(child_pid, &status, 0); // Wait for the child to exit
        }
    }

    return 0;
}
