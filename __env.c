#include "Shell.h"

/**
 * Gets an environment variable.
 * @arg: Argument.
 * Returns the environment variable.
 */
char *getenv(char *arg)
{
    char *key;
    char *temp;
    char *env_var;
    int index;

    index = 0;

    while (environ[index])
    {
        temp = strdup(environ[index]);
        key = strtok(temp, "=");
        
        switch (strcmp(key, arg))
        {
            case 0:
                env_var = strdup(strtok(NULL, "\n"));
                free(temp);
                return env_var;
            default:
                free(temp);
                break;
        }
        
        index++;
    }

    return NULL;
}
