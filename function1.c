#include "shell.h"

/**
 * prompt_func - function to print the $ symbol
 * @c: character pass
 * @len: represent length of the string
 * Return: void
 */
void prompt_func(char *c, int len)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, c, len);
}

/**
 * taking_input - function to take command the input
 * @input: represents the command to use
 * Return: return void
 */
ssize_t taking_input(char *input)
{
	ssize_t read_bytes = read(STDIN_FILENO, input, INPUT_SIZE);

	return ((read_bytes == -1) ? -1
		: (read_bytes == 0) ? 0
		: (input[read_bytes] = '\0', read_bytes));
}


/**
 * exit_the_Shell - this function helps to create an exit function
 * @status: shows the status code if any
 * Return: void
 */
void exit_the_Shell(int status)
{
	exit(status);
}


/**
 * checking_cmd_before_fork - function to check before creating the fork
 * @user_command: the command to check
 * Return: 0 for success and 1 otherwise
 */
int checking_cmd_before_fork(char *user_command)
{
	char *path_lookups, *duplicates, *store_paths;

	path_lookups = getenv("PATH");

	if (path_lookups == NULL)
		return (-1);

	duplicates = s_strdup(path_lookups);
	if (duplicates == NULL)
		return (-1);

	store_paths = s_strtok(duplicates, ":");

	for (; store_paths != NULL ;)
	{
		char abs_path[PATH_SIZE];

		s_strcpy(abs_path, store_paths);
		s_strcat(abs_path, "/");
		s_strcat(abs_path, user_command);

		if (access(abs_path, X_OK) == 0)
		{
			free(duplicates);
			return (0);
		}
		store_paths = s_strtok(NULL, ":");
	}
	free(duplicates);
	return (1);
}

/**
 * handling_signal - function to handle signal
 * @signal: the signal
 * Return: void
 */
void handling_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		prompt_func("$ ", s_strlen("$ "));
		fflush(stdout);
	}
}
