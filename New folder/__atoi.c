#include "Shell.h"

/**
 * Converts strings to integers.
 * @str: String to convert.
 * Returns the converted value.
 */
int __atoi(char *str)
{
    int i = 0;
    int result = 0;

    switch (str[i])
    {
        case '+':
            i++;
            break;
        default:
            break;
    }

    while (str[i])
    {
        switch (str[i])
        {
            case '-':
            case '_':
                return -1;
            default:
                result = (result * 10) + (str[i] - '0');
                i++;
                break;
        }
    }

    return result;
}
