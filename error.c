#include "shell.h"

/**
 * generateerrorMsg - function to display error msg
 * @testInstance: status code
 * @arguments: the argument for exit if any
 * @errorMsg: the program name
 * Return: void
 */
void generateerrorMsg(test *testInstance, char *arguments[], char *errorMsg)
{
	char error_msg[100];

	s_strcpy(error_msg, errorMsg);
	s_strcat(error_msg, ": 1");
	s_strcat(error_msg, ": ");
	s_strcat(error_msg, arguments[0]);
	s_strcat(error_msg, ": Illegal number: ");
	s_strcat(error_msg, arguments[1]);
	s_strcat(error_msg, "\n");
	write(STDERR_FILENO, error_msg, s_strlen(error_msg));
	testInstance->status = 2;
}

/**
 * handleExitWithCode - function to handle exit with code
 * @testInstance: the status code
 * @exitcode: the argument code
 * Return: void
 */
void handleExitWithCode(test __attribute__((__unused__)) *testInstance, int exitCode)
{
	if (exitCode >= 0)
		exit(exitCode);
}

/**
 * handle_exit - funcnction to handle exit command
 * @arguments: the command pass to execute
 * @statusCheck: the number of token return
 * @errorMsg: the program name
 * Return: 0 for success and 1 otherwise
 */
int processExit(char *arguments[], int statusstatusCheck, char *errorMsg)
{
	test testInstance;

	if (statusCheck > 0 && s_strcmp(arguments[0], "exit") == 0)
	{
		if (statusCheck == 1)
		{
			testInstance.status = 0;
			exit(testInstance.status);
		}
		else if (statusCheck == 2)
		{
			char *exitarg = arguments[1];

			if (ispositiveInt(exitarg))
			{
				int exitCode = atoi(exitarg);

				handleExitWithCode(&testInstance, exitCode);
			}
			else if (isnegativeInt(exitarg))
			{
				generateerrorMsg(&testInstance, arguments, errorMsg);
				exit(testInstance.status);
			}
			else
			{
				generateerrorMsg(&testInstance, arguments, errorMsg);
				exit(testInstance.status);
			}
		}
		return (0);
	}
	return (1);
}
