#include "shell.h"

/**
 * run_command - function for run_command
 * @user_command: the user input
 * @argv: the program name
 * @envp: parent environment
 * Return: status
 */

int run_command(char *user_command, char *argv, char *envp[]);
int run_command(char *user_command, char *argv, char *envp[])
{
	int handled = 0;
	int i, last_status = 0;
	char *cmd_list[ARG_SIZE];
	int num_cmd = 0;
	char *copy = strdup(user_command);
	char *cmd_token = s_strtok(user_command, ";\n");

	while (cmd_token != NULL)
	{
		if (!is_checking_whitespace_string(cmd_token))
		{
			cmd_list[num_cmd] = cmd_token;
			num_cmd++;
		}
		cmd_token = s_strtok(NULL, ";\n");
	}

	i = 0;

	while (i < num_cmd)
	{
		char *mycmd = cmd_list[i];
		char *args[ARG_SIZE];
		int check = tokenize_the_command(mycmd, args);

		replace_the_status_variable(args, check, &last_status);
		handled = handling_noninbuilt_command(mycmd, args, check,
				&last_status, argv, envp);
		if (handled != 1)
			return (handled);
		executing_the_logical_commands(copy, args, check,
				&last_status, argv, envp);
		i++;
	}
	free(copy);
	return (last_status);
}

/**
 * splitting_the_logical_operator - an operand splitting function
 * @input: user input
 * @delimiter: delimiter to sepperate user input
 * @output: where to store it
 * Return: the number of seperated command
 */

int splitting_the_logical_operator(char *input, const char *delimiter,
                char *output[]);
int splitting_the_logical_operator(char *input, const char *delimiter,
		char *output[])
{
	int num_parts = 0;
	char *token = s_strtok(input, delimiter);

	while (token != NULL)
	{
		output[num_parts] = token;
		num_parts++;
		token = s_strtok(NULL, delimiter);
	}
	return (num_parts);
}

/**
 * executing_the_logical_commands - function to perform logical function
 * @copy: the command
 * @args: the argument
 * @check: to check the command for inbuilt
 * @last_status: the status code
 * @argv: the program name
 * @envp: parent environment
 * Return: void
 */

void executing_the_logical_commands(char *copy, char *args[], int check,
                int *last_status, char *argv, char *envp[]);
void executing_the_logical_commands(char *copy, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	if (s_strstr(copy, "&&"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int num_parts = splitting_the_logical_operator(copy, "&&", cmd_parts);

		j = 0;
		while (j < num_parts)
		{
			int part_check = tokenize_the_command(cmd_parts[j], args);

			if (executing_comm(args, part_check, last_status,
						argv, envp) != 0)
			{
				return;
			}
			j++;
		}
	}
	else if (s_strstr(copy, "||"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int num_parts = splitting_the_logical_operator(copy, "||", cmd_parts);

		j = 0;
		while (j < num_parts)
		{
			int part_check = tokenize_the_command(cmd_parts[j], args);

			if (executing_comm(args, part_check, last_status,
						argv, envp) == 0)
			{
				return;
			}
			j++;
		}
	}
	else
	{
		executing_comm(args, check, last_status, argv, envp);
	}
}

/**
 * is_whitespace_string- this is a function checks for continuous whitespace
 * @str: the string to search for
 * Return: 0 if not all otherwise 1
 */

int is_checking_whitespace_string(char *str);
int is_checking_whitespace_string(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * handling_noninbuilt_command - this function to handles non inbuilt command
 * @mycmd: user command
 * @args: the argument if any
 * @check: checker for non_inbuilt cmd
 * @last_status: the status of command
 * @argv: the program name
 * @envp: parent environment
 * Return: the handle status
 */

int handling_noninbuilt_command(char *mycmd, char *args[], int check,
                int *last_status, char *argv, char *envp[]);
int handling_noninbuilt_command(char *mycmd, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	int handled = 1;

	handled = handle_cd_command(mycmd, args, check, last_status, argv, envp);
	if (handled != 1)
		return (handled);

	handled = handle_exit_command(args, check, argv);
	if (handled != 1)
		return (handled);

	handled = handling_setenv_command(mycmd, args, check, last_status);
	if (handled != 1)
		return (handled);

	handled = handling_unsetenv_command(mycmd, args, check, last_status);
	if (handled != 1)
		return (handled);

	return (handled);
}
