#include "shell.h"

/**
 * set_the_environ_variable - this function helps implement setenv
 * @var: this is the name of variable to set
 * @value: the value to set it to
 * Return: 0 for success and 1 otherwise
 */

int set_the_environ_variable(char *var, char *value);
int set_the_environ_variable(char *var, char *value)
{
	char *allocating_memory;

	allocating_memory = realloc(NULL, (s_strlen(value) + 1));

	if (allocating_memory == NULL)
		return (1);
	s_strcpy(allocating_memory, value);

	if (setenv(var, allocating_memory, 1) != 0)
	{
		free(allocating_memory);
		return (1);
	}
	free(allocating_memory);
	return (0);
}

/**
 * unset_env - this function helps implement unsetenv
 * @var: the variable to unset
 * Return: 0 for success 1 otherwise
 */

int unset_env(char *var);
int unset_env(char *var)
{
	if (unsetenv(var) != 0)
		return (1);
	return (0);
}

/**
 * tokenize_the_command - this function helps to tokenize command
 * @user_command: this is the user command
 * @args: array to store the command and arg
 * Return: the number of tokenize arg
 */

int tokenize_the_command(char *user_command, char *args[]);
int tokenize_the_command(char *user_command, char *args[])
{
	int index;
	char *copy = user_command;
	char *mytok = s_strtok(copy, TOK_DELIM);

	for (index = 0; mytok != NULL; index++)
	{
		args[index] = mytok;
		mytok = s_strtok(NULL, TOK_DELIM);
	}
	args[index] = NULL;

	return (index);
}

/**
 * setenv_cmd - this is a function that set environment variables
 * @user_command: this is the user command to check
 * Return: 0 for success
 */

int setenv_cmd(char *user_command);
int setenv_cmd(char *user_command)
{
	char *cmd_and_args[3];
	int tk_cnt = tokenize_the_command(user_command, cmd_and_args);

	if (tk_cnt < 1)
		return (-1);

	if (s_strcmp(cmd_and_args[0], "setenv") == 0)
	{
		if (cmd_and_args[1] == NULL || cmd_and_args[2] == NULL)
			return (1);
		return (set_the_environ_variable(cmd_and_args[1], "myvalue"));
	}
	return (-1);
}


/**
 * unsetenv_cmd - function to unset an envrionment variable
 * @user_command: the user command passed
 * Return: 0 for success
 */

int unsetenv_cmd(char *user_command);
int unsetenv_cmd(char *user_command)
{
	char *cmd_and_args[2];
	int tk_cnt = tokenize_the_command(user_command, cmd_and_args);

	if (tk_cnt < 1)
		return (-1);

	if (s_strcmp(cmd_and_args[0], "unsetenv") == 0)
	{
		if (cmd_and_args[1] == NULL)
			return (1);
		return (unset_env(cmd_and_args[1]));
	}
	return (-1);
}
