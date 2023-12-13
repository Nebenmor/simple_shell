#include "shell.h"


/**
 * s_getenv - function to get environment variable
 * @string: the environment varibale to get
 * @envp: parent environment
 * Return: pointer to the string result
 */

char *s_getenv(const char *string, char *envp[]);
char *s_getenv(const char *string, char *envp[])
{
	int index = 0;

	while (envp[index] != NULL)
	{
		char *start = envp[index];

		if (s_strncmp(start, string, s_strlen(string)) == 0
			&& start[s_strlen(string)] == '=')
		{
			return (start + s_strlen(string) + 1);
		}
		index++;
	}
	return (NULL);
}

/**
 * sep_cmd - function to seperate command
 * @user_command: the user command
 * @result: the array where the seperated command will be store
 * @num: maximum number of command
 * Return: the number of command seperated
 */

int sep_cmd(const char *user_command, char *result[], int num);
int sep_cmd(const char *user_command, char *result[], int num)
{
	int index = 0;
	char *duplicate = s_strdup(user_command);
	char *token = s_strtok(duplicate, ";");

	while (token != NULL && index < num)
	{
		result[index] = token;
		token = s_strtok(NULL, ";");
		index++;
	}

	free(duplicate);
	return (index);
}

/**
 * replace_the_status_variable - this function replaces the status variable
 * @args: the command
 * @count: number of count being executed
 * @last_status: variable to hold status code
 * Return: void
 */

void replace_the_status_variable(char *args[],
                int count, int *last_status);
void replace_the_status_variable(char *args[],
		int count, int *last_status)
{
	int index;

	index = 0;

	while (index < count)
	{
		if (s_strcmp(args[index], "$?") == 0)
		{
			char last_status_str[12];

			convert_int_to_string(*last_status, last_status_str, sizeof(last_status_str));
			args[index] = s_strdup(last_status_str);
		}
		index++;
	}
}

/**
 * convert_int_to_string - function that converts int to string
 * @num: the num to convert
 * @str: the string to convert to
 * @str_size: the size
 * Return:void
 */

void convert_int_to_string(int num, char *str, int str_size);
void convert_int_to_string(int num, char *str, int str_size)
{
	int temp = num;
	int numDigits = 1;

	while (temp / 10 != 0)
	{
		numDigits++;
		temp /= 10;
	}
	if (str_size <= numDigits)
	{
		return;
	}
	str[numDigits] = '\0';

	while (numDigits > 0)
	{
		numDigits--;
		str[numDigits] = '0' + (num % 10);
		num /= 10;
	}
}
