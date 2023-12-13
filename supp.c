#include "shell.h"

int executing_file_commands(const char *name_of_file, char *envp[],
		char *name_of_program);
int executing_file_commands(const char *name_of_file, char *envp[],
		char *name_of_program)
{
	char *exp_cmd;
	int last_status;
	char line[INPUT_SIZE];
	ssize_t bytes_read;

	int fd = open(name_of_file, O_RDONLY);

	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{
			int program_len = s_strlen(name_of_program);
			int filename_len = s_strlen(name_of_file);

			write(2, name_of_program, program_len);
			write(2, ": 0: cannot open ", 17);
			write(2, name_of_file, filename_len);
			write(2, ": No such file\n", 15);
			exit(2);
		}
	}

	while ((bytes_read = read(fd, line, sizeof(line))) > 0)
	{
		line[bytes_read] = '\0';
		delete_comments(line);
		exp_cmd = deal_with_double_dollars(line, envp);
		last_status = run_command_of_files(exp_cmd, name_of_program, envp);

		if (last_status > 0)
		{
			int status;

			waitpid(last_status, &status, 0);
		}
	}
	close(fd);
	return (0);
}

/**
 * is_whitespace_check - this function checks for whitespace
 * @c: the character to check
 * Return: escape character
 */

int is_whitespace_check(char c);
int is_whitespace_check(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n' || c == '\r'));
}

/**
 * is_word_start_check - function to check if a word start
 * @str: the string to search
 * @index: the index to iterate over
 * Return: 1 if success
 */

int is_word_start_check(char *str, int index);
int is_word_start_check(char *str, int index)
{
	if (index == 0 || is_whitespace_check(str[index - 1]))
	{
		return (1);
	}
	return (0);
}

/**
 * checking_for_cmd - function to check for external command
 * @mycmd: this is the command to be checke
 * Return: 0 on success
 */

int checking_for_cmd(char *mycmd);
int checking_for_cmd(char *mycmd)
{
	if (checking_cmd_before_fork(mycmd) == 1 && s_strcmp(mycmd, "exit") != 0 &&
		s_strcmp(mycmd, "cd") != 0 && s_strcmp(mycmd, "setenv") != 0 &&
		s_strcmp(mycmd, "unsetenv") != 0 && s_strcmp(mycmd, "alias") != 0)
	{
		return (0);
	}
	else
		return (1);
}
