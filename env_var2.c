#include "shell.h"


/**
 * getEnvVarValue - function to get environment variable
 * @envVarName: the environment varibale to get
 * @envp: parent environment
 * Return: pointer to the envVarName tokens
 */
char *getEnvVarValue(const char *envVarName, char *envp[])
{
	int j = 0;

	while (envp[j] != NULL)
	{
		char *start = envp[j];

		if (s_strncmp(start, envVarName, s_strlen(envVarName)) == 0
			&& start[s_strlen(envVarName)] == '=')
		{
			return (start + s_strlen(envVarName) + 1);
		}
		j++;
	}
	return (NULL);
}

/**
 * tokenizeCommand - function to seperate command
 * @userCommand: the user command
 * @tokens: the array where the seperated command will be store
 * @maxTokens: maximum maxTokensber of command
 * Return: the maxTokensber of command seperated
 */
int tokenizeCommand(const char *userCommand, char *tokens[], int maxTokens)
{
	int j = 0;
	char *duplicate = s_strdup(userCommand);
	char *token = s_strtok(duplicate, ";");

	while (token != NULL && j < maxTokens)
	{
		tokens[j] = token;
		token = s_strtok(NULL, ";");
		j++;
	}

	free(duplicate);
	return (j);
}

/**
 * updateStatusVariable - function to replace status variable
 * @arguments: the command
 * @argumentCount: maxTokensber of argumentCount being executed
 * @lastStatus: variable to hold status code
 * Return: void
 */
void updateStatusVariable(char *arguments[],int argumentCount, int *lastStatus)
{
	int j;

	for (j = 0; j < argumentCount; j++)
	{
		if (s_strcmp(arguments[j], "$?") == 0)
		{
			char lastStatus_str[12];

			intToenvVarName(*lastStatus, lastStatus_str, sizeof(lastStatus_str));
			arguments[j] = s_strdup(lastStatus_str);
		}
	}
}

/**
 * intToenvVarName - function to converrt int to envVarName
 * @value: the value to convert
 * @result: the envVarName to convert to
 * @result_size: the size
 * Return:void
 */
void intToenvVarName(int value, char *result, int result_size)
{
	int temp = value;
	int valueDigits = 1;

	while (temp / 10 != 0)
	{
		valueDigits++;
		temp /= 10;
	}
	if (result_size <= valueDigits)
	{
		return;
	}
	result[valueDigits] = '\0';

	while (valueDigits > 0)
	{
		valueDigits--;
		result[valueDigits] = '0' + (value % 10);
		value /= 10;
	}
}
