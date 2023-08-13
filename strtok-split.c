#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

/**
 * split_string - Splits a string into words without using strtok.
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

    int input_length = strlen(input);
    char *copy = (char *)malloc((input_length + 1) * sizeof(char));
    if (copy == NULL)
    {
        perror("Memory allocation failed");
        free(words);
        return NULL;
    }
    strcpy(copy, input);

    char *token_start = copy;
    char *token_end = NULL;
    *num_words = 0;

    while (*token_start != '\0')
    {
        token_end = token_start;
        while (*token_end != '\0' && strchr(delimiters, *token_end) == NULL)
        {
            token_end++;
        }

        if (*num_words >= MAX_WORDS)
        {
            fprintf(stderr, "Maximum number of words exceeded\n");
            break;
        }

        int token_length = token_end - token_start;
        words[*num_words] = (char *)malloc((token_length + 1) * sizeof(char));
        if (words[*num_words] == NULL)
        {
            perror("Memory allocation failed");
            break;
        }
        strncpy(words[*num_words], token_start, token_length);
        words[*num_words][token_length] = '\0';

        (*num_words)++;
        if (*token_end != '\0')
        {
            token_start = token_end + 1;
        }
        else
        {
            break;
        }
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
