#include "shell.h"


/**
 * create_and_write_error_messages - function that output error messages
 * @mytest: status code
 * @args: the argument for exit if any
 * @argv: the program name
 * Return: void
 */

void create_and_write_error_messages(test *mytest, char *args[], char *argv);
void create_and_write_error_messages(test *mytest, char *args[], char *argv)
{
	char error_msg[100];

	s_strcpy(error_msg, argv);
	s_strcat(error_msg, args[0]);
	s_strcat(error_msg, ": Illegal number: ");
	s_strcat(error_msg, "\n");
	s_strcat(error_msg, ": 1");
	s_strcat(error_msg, ": ");
	s_strcat(error_msg, args[1]);
	write(STDERR_FILENO, error_msg, s_strlen(error_msg));
	mytest->status = 2;
}

/**
 * handle_exit_with_code - function to handle exit with code
 * @mytest: the status code
 * @code: the argument code
 * Return: void
 */

void handle_exit_with_code(test __attribute__((__unused__)) *mytest, int code);
void handle_exit_with_code(test __attribute__((__unused__)) *mytest, int code)
{
	if (code >= 0)
		exit(code);
}

/**
 * handle_exit_command - function that handles the exit command
 * @args: is the command passed to execute
 * @check: the number of token return
 * @argv: the program name
 * Return: 0 for success and 1 otherwise
 */

int handle_exit_command(char *args[], int check, char *argv);
int handle_exit_command(char *args[], int check, char *argv)
{
	test mytest;

	if (check > 0 && s_strcmp(args[0], "exit") == 0)
	{
		if (check == 1)
		{
			mytest.status = 0;
			exit(mytest.status);
		}
		else if (check == 2)
		{
			char *exitarg = args[1];

			if (is_Positive_Int(exitarg))
			{
				int code = atoi(exitarg);

				handle_exit_with_code(&mytest, code);
			}
			else if (is_Negative_Int(exitarg))
			{
				create_and_write_error_messages(&mytest, args, argv);
				exit(mytest.status);
			}
			else
			{
				create_and_write_error_messages(&mytest, args, argv);
				exit(mytest.status);
			}
		}
		return (0);
	}
	return (1);
}
