#include "shell.h"


/**
 * get_environ - This function helps to get the value of env
 * @variable_name: the command
 * @envp: the parent environment
 * Return: the environment variable
 */
char *get_environ(char *variable_name, char *envp[])
{
	int i;

	i = 0;

	while (envp[i] != NULL)
	{
	char *env_entry = envp[i];

	if (s_strstr(env_entry, variable_name) == env_entry)
	{
	const char *equals = s_strchr(env_entry, '=');

	if (equals != NULL)
	{
		return (s_strdup(equals + 1));
	}
	}

	i++;
	}

	return (NULL);
}

/**
 * double_dollar - This function handles double dollar
 * @cmd: this is the command
 * @output: this is the output
 * @i: is a  counter
 * @j: is a counter
 * Return: void
 */
void double_dollar(char __attribute__((__unused__))
		*cmd, char *output, int *i, int *j)
{


	char *pid_str = get_pid_str();
	int k;

	for (k = 0; pid_str[k] != '\0'; k++)
	{
	output[(*j)++] = pid_str[k];
	}

	free(pid_str);
	(*i) += 2;
}


/**
 * deal_with_env_variable - function to specify it
 * @cmd: the command
 * @output: the output result
 * @i: is a counter
 * @j: is a counter
 * @envp: parent environment
 * Return: void
 */
void deal_with_env_variable(char *cmd, char *output, int *i,
		int *j, char *envp[])
{
	for (int k = (*i); s_isalnum((unsigned char)
				cmd[(*i)]) || cmd[(*i)] == '_'; (*i)++)
	{
	    /* Loop body */
	}

	int k = (*i);

	if (k != (*i))
	{
		char *env_var = StrCpyM(&cmd[k], (*i) - k);

		char *env_value = get_environ(env_var, envp);

		if (env_value)
		{
			int l;

			for (l = 0; env_value[l] != '\0'; l++)
			{
			output[(*j)++] = env_value[l];
			}

			free(env_value);

		}
		free(env_var);
	}
	else
	{
		output[(*j)++] = '$';
	}
}

/**
 * deal_with_double_dollars - function to handle environent variable
 * @cmd: is the command enter
 * @envp: is the parent environment
 * Return: the absolute variable
 */

char *deal_with_double_dollars(char *cmd, char *envp[]);

char *deal_with_double_dollars(char *cmd, char *envp[])
{
	char *output;

	output = realloc(NULL, (strlen(cmd) * 10 + 1));

	int i;
	int j;

	i = 0;
	j = 0;

	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$' && cmd[i + 1] == '$')
		{
			double_dollar(cmd, output, &i, &j);
		}
		else if (cmd[i] == '$')
		{
			i++;
			deal_with_env_variable(cmd, output, &i, &j, envp);
		}
		else
		{
			output[j++] = cmd[i++];
		}
	}

	output[j] = '\0';

	free(output);
	return (output);
}

/**
 * get_pid_str - function to get the process id
 * Return: the process id
 */

char *get_pid_str();

char *get_pid_str()
{
	pid_t pid = getpid();
	char pid_buff[16];
	int i = 0;
	char *pid_string;

	if (pid == 0)
	{
		pid_buff[i++] = '0';
	}
	else
	{
		while (pid > 0)
		{
			pid_buff[i++] = '0' + (pid % 10);
			pid /= 10;
		}
	}

	pid_string = realloc(NULL, (i + 1));
	if (pid_string)
	{
		int j;
		int k;

		j = 0;

		for (k = i - 1; k >= 0; k--)
		{
			pid_string[j++] = pid_buff[k];
		}

		pid_string[j] = '\0';
	}

	return (pid_string);
}
