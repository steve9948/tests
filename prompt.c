#include <stdio.h>

/**
 * main - Entry point of the program.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
    printf("$ "); // Print the prompt

    char command[100]; // Array to store user input

    // Read user input (command) from the console
    if (fgets(command, sizeof(command), stdin) != NULL)
    {
        // Print the entered command on the next line
        printf("You entered: %s", command);
    }

    return 0; // Indicate successful program execution
}

