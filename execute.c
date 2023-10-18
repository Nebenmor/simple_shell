#include "Shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * execute - function that executes a command
 * @cmd: command
 * @av: argument
 * Return: Exit status of the executed command
 */
int execute(char **cmd, char **av)
{
	pid_t pid;
	int status = 0;

	if (cmd)
	{
	pid = fork();
	if (pid == -1)
	{
	perror("Error: fork");
	exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
	if (execve(cmd[0], cmd, environ) == -1)
	{
	perror(av[0]);
	freeBuff(cmd);
	exit(EXIT_FAILURE);
	}
	}
	else
	{
	waitpid(pid, &status, 0);
	freeBuff(cmd);
	}
	}
	return (WEXITSTATUS(status));
}
