#include "shell.h"

/**
 * tokenizing_the_user_command - tokenize user command from argument
 * @user_command: the string passed from the xterm
 * @args: is the array of pointer to strings to store the tokenized arguments
 * Return: void
 */
void tokenizing_the_user_command(char *user_command, char **args)
{
	int index;
	char *copies, *mytoken;


	copies = s_strdup(user_command);
	mytoken = s_strtok(copies, " ");

	index = 0;

	while (mytoken != NULL)
	{
		args[index] = mytoken;
		mytoken = s_strtok(NULL, " ");
		index++;
	}

	args[index] = NULL;
}

/**
 * executing_the_command_withPath - execute command without specifield path
 * @user_command: the user command
 * @args: the flag of the command
 * @env: parent environment
 * Return: 0 for success
 */
int executing_the_command_withPath(char *user_command,
		char *args[], char **env)
{
	int index;
	int result = -1;
	char *path_of_token, *the_command_path, *duplicate_copies;

	the_command_path = getenv("PATH");

	if (the_command_path == NULL)
		return (-1);

	duplicate_copies = s_strdup(the_command_path);
	if (duplicate_copies == NULL)
		return (-1);

	path_of_token = s_strtok(duplicate_copies, ":");

	index = 0;
	while (path_of_token != NULL)
	{
		char abs_path[PATH_SIZE];

		s_strcpy(abs_path, path_of_token);
		s_strcat(abs_path, "/");
		s_strcat(abs_path, user_command);

		result = execve(abs_path, args, env);

		if (result == -1)
			path_of_token = s_strtok(NULL, ":");
		index++;
	}

	free(duplicate_copies);

	return (result);
}

/**
 * executing_the_command - function to execute the command
 * @user_command: the command pass
 * @args: the flag of the command
 * @argv: the program name
 * @envp: the parent environment
 * Return: 0 if success
 */
int executing_the_command(char *user_command, char *args[],
		char *argv, char **envp)
{
	int result;

	if (s_strchr(user_command, '/') != NULL)
	{
		result = execve(user_command, args, envp);
		return (result);
	}
	else
	{
		if (check_cmd(args[0]) == 0)
		{
			print_err(args[0], argv);
			exit(127);
		}
		result = executing_the_command_withPath(user_command, args, envp);

		if (result == -1)
		{
			print_err(args[0], argv);
			exit(127);
		}

		return (result);
	}
}

/**
 * run_command_of_files - function to run the command
 * @user_command: is the command to run
 * @argv:; the program name
 * @envp: parent environment
 * Return: child pid
 */

int run_command_of_files(char *user_command, char *argv, char *envp[])
{
	int handled = 0;
	int i, last_status = 0;
	char *cmd_list[ARG_SIZE];
	int num_cmd = 0;
	char *cmd_token = s_strtok(user_command, ";\n");

	while (cmd_token != NULL)
	{
		cmd_list[num_cmd] = cmd_token;
		num_cmd++;
		cmd_token = s_strtok(NULL, ";\n");
	}

	i = 0;

	while (i < num_cmd)
	{
		char *mycmd = cmd_list[i];
		char *args[ARG_SIZE];
		int check = token_command(mycmd, args);

		replace_status_variable(args, check, &last_status);
		handled = handling_cd_command(mycmd, args, check, &last_status, argv, envp);
		if (handled != 1)
			return (handled);
		handled = handle_exit(args, check, argv);
		if (handled != 1)
			return (handled);
		handled = handling_setenv_command(mycmd, args, check, &last_status);
		if (handled != 1)
			return (handled);
		handled = handling_unsetenv_command(mycmd, args, check, &last_status);
		if (handled != 1)
			return (handled);
		if (executing_comm(args, check, &last_status, argv, envp) == 1)
			return (2);
		i++;
	}
	return (last_status);
}
