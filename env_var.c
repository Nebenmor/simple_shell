#include "shell.h"


/**
 * get_environ - This function helps to get the value of env
 * @variable_name: this is the command
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
 * double_dollar - handle $$ symbol
 * @cmd: the command
 * @output: the output
 * @i: a counter variable
 * @j: a counter variable
 * Return: void
 */
void double_dollar(char __attribute__((__unused__))
		*cmd, char *output, int *i, int *j)
{
	char *pid_str = get_process_id_string();
	int k = 0;

	do {
		output[(*j)++] = pid_str[k++];
	} while (pid_str[k] != '\0');

	free(pid_str);
	(*i) += 2;
}

/**
 * deal_with_environ_variable - function to specify it
 * @cmd: the command
 * @output: the output result
 * @i: a counter
 * @j: counter
 * @envp: parent environment
 * Return: void
 */
void deal_with_environ_variable(char *cmd, char *output, int *i,
		int *j, char *envp[])
{
	int k = (*i);

	while (s_isalnum((unsigned char)cmd[(*i)]) || cmd[(*i)] == '_')
	{
		(*i)++;
	}

	if (k != (*i))
	{
		
		char *env_value = get_environment_variable_value(env_var, envp);

		if (env_value)
		{
			int l = 0;

			do {
				output[(*j)++] = env_value[l++];
			} while (env_value[l] != '\0');

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
 * dealing_with_double_dollars - function to handle environent variable
 * @cmd: the command enter
 * @envp: parent environment
 * Return: the absolute variable
 */
char *dealing_with_double_dollars(char *cmd, char *envp[])
{
	char *output = realloc(NULL, strlen(cmd) * 10 + 1);
	int i = 0, j = 0;

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
	return (output);
}

/**
 * get_process_id_string - function to get process id
 * Return: the process id
 */
char *get_process_id_string()
{
	pid_t pid = getpid();
	char pid_buff[16];
	int i = 0;
	char *pid_str;

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

	pid_str = realloc(NULL, malloc(i + 1));
	if (pid_str)
	{
		int j = 0;
		int k;

		for (k = i - 1; k >= 0; k--)
		{
			pid_str[j++] = pid_buff[k];
		}

		pid_str[j] = '\0';
	}

	free(pid_str);

	return (pid_str);
}
