#include "shell.h"

/**
 * custom_program_entry - custom_program_entry function Entry point
 * @custom_argc: t keep count the number of argument
 * @custom_argv: array to store the argument
 * @custom_envp: the parent environment
 * Return: 0 for success 1 otherwise
 */
int custom_program_entry(int custom_argc, char *custom_argv[], char *custom_envp[])
{
	char user_command[INPUT_SIZE];
	ssize_t input_byte;
	char *exp_cmd;
	int last_status;

	if (custom_argc == 2)
	{
		last_status = execute_commands_from_file(custom_argv[1], custom_envp, custom_argv[0]);
	}
	else
	{
		signal(SIGINT, signal_handler);
		while (LOOP)
		{
			prompt("$ ", s_custom_strlen("$ "));
			input_byte = take_input(user_command);
			if (input_byte == -1)
				continue;
			else if (input_byte == 0)
			{
				prompt("\n", s_custom_strlen("\n"));
				break;
			}

			remove_comment(user_command);
			exp_cmd = handle_double_dollars(user_command, custom_envp);
			last_status = run_command(exp_cmd, custom_argv[0], custom_envp);
			free(exp_cmd);
		}
	}
	return (last_status);
}

/**
 * check_positive_integer - function to check if input is digit
 * @custom_str: the custom_string enter
 * Return: 1 if int
 */
int check_positive_integer(char *custom_str)
{
	int index;

	for (index = 0; custom_str[index] != '\0'; index++)
	{
		if (!isdigit(custom_str[index]))
			return (0);
	}
	return (1);
}

/**
 * is_negative_integer - function to check if a number is negative integer
 * @custom_str: the custom_string to check
 * Return: 0 on success
 */
int is_negative_integer(char *custom_str)
{
	int index;

	if (custom_str[0] == '-')
		return (1);
	for (index = 1; custom_str[index] != '\0'; index++)
	{
		if (!isdigit(custom_str[index]))
			return (0);
	}
	return (1);
}
