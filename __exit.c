#include "Shell.h"

/**
 * Exits the shell.
 * @tokens: Tokens.
 * @buffer: Buffer.
 * Return: Integer.
 */
int exitShell(char **tokens, char *buffer)
{
    int counter = 0;
    int exitStatus = 0;

    while (tokens[counter])
        counter++;

    switch (counter)
    {
        case 1:
            freeBuffer(tokens);
            free(buffer);
            exit(0);
            break;

        default:
            break;
    }

    if (convertStringToInt(tokens[1]) == -1)
    {
        fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", tokens[1]);
        return 2;
    }

    exitStatus = convertStringToInt(tokens[1]);
    freeBuffer(tokens);
    free(buffer);
    exit(exitStatus);
}
