#include <stdio.h>

/**
 * main - Entry point of the program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: Always 0 (success).
 */
int main(int argc, char *argv[])
{
    char **arg = argv; // Initialize a pointer to the argument vector.

    while (*arg != NULL) // Iterate through the argument vector.
    {
        printf("%s\n", *arg); // Print the current argument.
        arg++; // Move the pointer to the next argument.
    }

    return 0; // Indicate successful program execution.
}

