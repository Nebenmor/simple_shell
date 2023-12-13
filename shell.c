#include "shell.h"

/**
 * main - this is the main function Entry point
 * @argc: this helps to keep count of the number of argument
 * @argv: array to store the argument
 * @envp: the parent environment
 * Return: 0 for success 1 otherwise
 */

int main(int argc, char *argv[], char *envp[]);
int main(int argc, char *argv[], char *envp[])
{
	char user_command[INPUT_SIZE];
	ssize_t input_byte;
	char *exp_cmd;
	int last_status;

	if (argc == 2)
	{
		last_status = executing_file_commands(argv[1], envp, argv[0]);
	}
	else
	{
		signal(SIGINT, handling_signal);
		while (LOOP)
		{
			prompt_func("$ ", s_strlen("$ "));
			input_byte = taking_input(user_command);
			if (input_byte == -1)
				continue;
			else if (input_byte == 0)
			{
				prompt_func("\n", s_strlen("\n"));
				break;
			}

			delete_comments(user_command);
			exp_cmd = deal_with_double_dollars(user_command, envp);
			last_status = run_command(exp_cmd, argv[0], envp);
			free(exp_cmd);
		}
	}
	return (last_status);
}

/**
 * is_Positive_Int - this function checks for digit inputs
 * @str: the string enter
 * Return: 1 if int
 */

int is_Positive_Int(char *str);
int is_Positive_Int(char *str)
{
	int index;

	index = 0;
	while (str[index] != '\0')
	{
		if (!isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

/**
 * is_Negative_Int - this function checks for negative integers
 * @str: the string to check
 * Return: 0 on success
 */

int is_Negative_Int(char *str);
int is_Negative_Int(char *str)
{
	int index;

	index = 1;

	if (str[0] == '-')
		return (1);
	while (str[index] != '\0')
	{
		if (!isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}
