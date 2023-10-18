#include "Shell.h"

/*
 * This program frees the memory allocated for an array of strings.
 * @param tokens: This represents the array of strings to be freed.
 */
void freeTokens(char **tokens)
{
	int i = 0;
	if (tokens == NULL)
	return;

	while (tokens[i] != NULL)
	{
	free(tokens[i]); /* Free each string in the array */
	i++;
	}

	free(tokens); /* The array itself is freed */
}

/**
 * Main program for a simple shell
 * @param ac: Number of arguments
 * @param av: Array of arguments
 * @return: 0
 */

int main(__attribute__((unused)) int ac, char **av)
{
	char *line = NULL;
	char **cmd = NULL;
	int status = 0;

	while (1)
	{
	line = _getCommand();
	if (line == NULL)
	{
	if (isatty(STDIN_FILENO) == 1)
	write(1, "\n", 1);
	free(line);
	freeTokens(cmd);
	return (status);
	}

	cmd = tokenCmd(line);
	if (cmd == NULL)
	{
	free(line);
	continue;
	}

	Comments(&cmd);
	status = execute(cmd, av);
	free(line);
	freeTokens(cmd);
	}
	return (0);
}
