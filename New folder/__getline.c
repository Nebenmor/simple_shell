#include "Shell.h"

/**
 * Reads a line from user/file.
 * @line: Pointer to store the line.
 * @buffsize: Size of the buffer.
 * @stream: File descriptor.
 * Returns the number of characters read, -1 on failure.
 */
ssize_t __getline(char **line, size_t *buffsize, FILE *stream)
{
    size_t n_chars = 0;
    char c;
    char *temp;

    switch (!*line || !*buffsize)
    {
        case 1:
            *buffsize = MAX_INPUT_SIZE;
            *line = (char *)malloc(*buffsize);
            switch (!*line)
            {
                case 1:
                    return -1;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    while (1)
    {
        c = fgetc(stream);
        switch (c)
        {
            case '\n':
            case EOF:
                (*line)[n_chars] = '\0';
                break;
            default:
                (*line)[n_chars] = c;
                n_chars++;
                if (n_chars >= *buffsize)
                {
                    *buffsize *= 2;
                    temp = (char *)realloc(*line, *buffsize);
                    switch (!temp)
                    {
                        case 1:
                            return -1;
                        default:
                            *line = temp;
                            break;
                    }
                }
                break;
        }

        if (c == '\n' || c == EOF)
            break;
    }

    return n_chars;
}
