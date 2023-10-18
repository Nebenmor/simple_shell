#include "Shell.h"

/**
 * Gets a command from the user.
 * Returns a pointer to the command.
 */
char *__getCommand(void)
{
    size_t n_chars = 0;
    char *command = NULL;
    int result;

    switch (isatty(STDIN_FILENO))
    {
        case 1:
            write(1, "$ ", 2);
            break;
        default:
            break;
    }

    result = getline(&command, &n_chars, stdin);

    switch (result)
    {
        case -1:
            free(command);
            return NULL;
        default:
            return command;
    }
}
