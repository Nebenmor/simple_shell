#include "shell.h"

/**
 * execute_custom_command - function for execute_custom_command
 * @custom_command: the user custom_input
 * @custom_argv: the program name
 * @custom_envp: parent environment
 * Return: status
 */
int execute_custom_command(char *custom_command, char *custom_argv, char *custom_envp[])
{
	int handled = 0;
	int i, custom_last_status = 0;
	char *cmd_list[ARG_SIZE];
	int num_cmd = 0;
	char *custom_copy = custom_strdup(custom_command);
	char *cmd_token = s_custom_strtok(custom_command, ";\n");

	while (cmd_token != NULL)
	{
		if (!check_for_whitespace(cmd_token))
		{
			cmd_list[num_cmd] = cmd_token;
			num_cmd++;
		}
		cmd_token = s_custom_strtok(NULL, ";\n");
	}

	for (i = 0; i < num_cmd; i++)
	{
		char *custom_mycmd = cmd_list[i];
		char *custom_args[ARG_SIZE];
		int custom_custom_last_status = token_command(custom_mycmd, custom_args);

		replace_status_variable(custom_args, custom_custom_last_status, &custom_last_status);
		handled = custom_command_handler(custom_mycmd, custom_args, custom_custom_last_status,
				&custom_last_status, custom_argv, custom_envp);
		if (handled != 1)
			return (handled);
		execute_logical_commands(custom_copy, custom_args, custom_custom_last_status,
				&custom_last_status, custom_argv, custom_envp);
	}
	free(custom_copy);
	return (custom_last_status);
}

/**
 * custom_custom_string_parser - function to split logic operand
 * @custom_input: user custom_input
 * @custom_delimiter: custom_delimiter to sepperate user custom_input
 * @custom_output: where to store it
 * Return: the number of seperated command
 */
int custom_custom_string_parser(char *custom_input, const char *custom_delimiter, char *custom_output[])
{
	int num_parts = 0;
	char *token = s_custom_strtok(custom_input, custom_delimiter);

	while (token != NULL)
	{
		custom_output[num_parts] = token;
		num_parts++;
		token = s_custom_strtok(NULL, custom_delimiter);
	}
	return (num_parts);
}

/**
 * execute_logical_commands - function to perform logical function
 * @custom_copy: the command
 * @custom_args: the argument
 * @custom_custom_last_status: to custom_custom_last_status the command for inbuilt
 * @custom_last_status: the status code
 * @custom_argv: the program name
 * @custom_envp: parent environment
 * Return: void
 */
void execute_custom_tasks(char *custom_copy, char *custom_args[], int custom_custom_last_status,
		int *custom_last_status, char *custom_argv, char *custom_envp[])
{
	if (s_custom_strcustom_str(custom_copy, "&&"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int num_parts = custom_custom_string_parser(custom_copy, "&&", cmd_parts);

		for (j = 0; j < num_parts; j++)
		{
			int part_custom_custom_last_status = token_command(cmd_parts[j], custom_args);

			if (execute_command(custom_args, part_custom_custom_last_status, custom_last_status,
						custom_argv, custom_envp) != 0)
			{
				return;
			}
		}
	}
	else if (s_custom_strcustom_str(custom_copy, "||"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int num_parts = custom_custom_string_parser(custom_copy, "||", cmd_parts);

		for (j = 0; j < num_parts; j++)
		{
			int part_custom_custom_last_status = token_command(cmd_parts[j], custom_args);

			if (execute_command(custom_args, part_custom_custom_last_status, custom_last_status,
						custom_argv, custom_envp) == 0)
			{
				return;
			}
		}
	}
	else
	{
		execute_command(custom_args, custom_custom_last_status, custom_last_status, custom_argv, custom_envp);
	}
}

/**
 * check_for_whitespace- function to custom_custom_last_status for continuous whitespace
 * @custom_str: the custom_string to search for
 * Return: 0 if not all otherwise 1
 */
int check_for_whitespace(char *custom_str)
{
	int i;

	for (i = 0; custom_str[i] != '\0'; i++)
	{
		if (!isspace(custom_str[i]))
			return (0);
	}
	return (1);
}

/**
 * custom_command_handler - function to handle non inbuilt command
 * @custom_mycmd: user command
 * @custom_args: the argument if any
 * @custom_custom_last_status: custom_custom_last_statuser for non_inbuilt cmd
 * @custom_last_status: the status of command
 * @custom_argv: the program name
 * @custom_envp: parent environment
 * Return: the handle status
 */
int custom_command_handler(char *custom_mycmd, char *custom_args[], int custom_custom_last_status,
		int *custom_last_status, char *custom_argv, char *custom_envp[])
{
	int handled = 1;

	handled = handle_cd(custom_mycmd, custom_args, custom_custom_last_status, custom_last_status, custom_argv, custom_envp);
	if (handled != 1)
		return (handled);

	handled = handle_exit(custom_args, custom_custom_last_status, custom_argv);
	if (handled != 1)
		return (handled);

	handled = handle_setenv(custom_mycmd, custom_args, custom_custom_last_status, custom_last_status);
	if (handled != 1)
		return (handled);

	handled = handle_unsetenv(custom_mycmd, custom_args, custom_custom_last_status, custom_last_status);
	if (handled != 1)
		return (handled);

	return (handled);
}
