#include "shell.h"

/**
 * executing_comm - This function creates fork and execute command
 * @args: is the command to execute
 * @check: is the number of token returned
 * @last_status: the variable that keeps the value of return
 * @argv: the program name
 * @envp: parent environment
 * Return: 0 for success
 */

int executing_comm(char *args[], int check, int *last_status,
		char *argv, char *envp[]);
int executing_comm(char *args[], int check, int *last_status,
		char *argv, char *envp[])
{
	int j = 0;
	test mytest;
	pid_t child_process_id = fork();

	if (child_process_id < 0)
		return (-1);
	if (child_process_id == 0)
	{
		char **exec_Args = realloc(NULL, ((check + 1) * sizeof(char *)));

		if (exec_Args == NULL)
			return (-1);

		while (j < check)
		{
		exec_Args[j] = s_strdup(args[j]);

		if (exec_Args[j] == NULL)
		return (-1);

		j++;
		}

		exec_Args[check] = NULL;

		if (execute_the_command(exec_Args[0], exec_Args, argv, envp) == -1)
		{
			perror(exec_Args[0]);
			exit(2);
		}

		while (j < check)
		{
			free(exec_Args[j]);
			j++;
		}


		free(exec_Args);
	}

	else
	{
		wait(&(mytest.status));
		if (WIFEXITED(mytest.status))
			mytest.status = WEXITSTATUS(mytest.status);
		*last_status = mytest.status;
	}
	return (mytest.status);
}


/**
 * handle_cd_command - this function helps to handle CD command
 * @mycmd: represents the command at the first index
 * @args: the is command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * @argv: the program name
 * @envp: parent environment
 * Return: 0 for success
 */

int handle_cd_command(char *mycmd, char *args[], int check,
		int *last_status, char *argv, char *envp[]);
int handle_cd_command(char *mycmd, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	if (checking_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "cd") == 0)
	{
		int product = implement_cd(args[1], argv, envp);

		if (product == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}

/**
 * handling_setenv_command - this function handles setenv command
 * @mycmd: the command at first index
 * @args: is the command to execute
 * @check: the number of token returned
 * @last_status: the variable that keeps the value of return
 * Return: 0 on success
 */

int handling_setenv_command(char *mycmd, char *args[],
		int check, int *last_status);
int handling_setenv_command(char *mycmd, char *args[],
		int check, int *last_status)
{
	if (checking_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "setenv") == 0)
	{
		int env_rs = setenv_cmd(mycmd);

		if (env_rs == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}


/**
 * handling_unsetenv_command - this function handles unsetenv command
 * @mycmd: is the command at first index
 * @args: is the command to execute
 * @check: is the number of token returned
 * @last_status: the variable that keeps the value of return
 * Return: 0 on success
 */

int handling_unsetenv_command(char *mycmd, char *args[],
		int check, int *last_status);
int handling_unsetenv_command(char *mycmd, char *args[],
		int check, int *last_status)
{
	if (checking_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "unsetenv") == 0)
	{
		int unset_rs = unsetenv_cmd(mycmd);

		if (unset_rs == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}
