#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

/**
 * split_string - Splits a string into words.
 *
 * @input: The input string to be split.
 * @delimiters: The delimiters used for splitting.
 * @num_words: A pointer to store the number of words found.
 *
 * Return: An array of strings containing the split words.
 */
char **split_string(const char *input, const char *delimiters, int *num_words)
{
    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    char *copy = strdup(input);
    if (copy == NULL)
    {
        perror("Memory allocation failed");
        free(words);
        return NULL;
    }

    char *token = strtok(copy, delimiters);
    *num_words = 0;

    while (token != NULL)
    {
        if (*num_words >= MAX_WORDS)
        {
            fprintf(stderr, "Maximum number of words exceeded\n");
            break;
        }

        words[*num_words] = strdup(token);
        if (words[*num_words] == NULL)
        {
            perror("Memory allocation failed");
            break;
        }

        (*num_words)++;
        token = strtok(NULL, delimiters);
    }

    free(copy);
    return words;
}

int main(void)
{
    const char *input = "Hello, world! This is a test.";
    const char *delimiters = " ,.!"; // Delimiters: space, comma, period, and exclamation mark
    int num_words;

    char **words = split_string(input, delimiters, &num_words);

    if (words != NULL)
    {
        for (int i = 0; i < num_words; i++)
        {
            printf("Word %d: %s\n", i + 1, words[i]);
            free(words[i]);
        }
        free(words);
    }

    return 0;
}
