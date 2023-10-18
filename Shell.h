#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


#define delim " \t\r\n\a\""
#define MAX_INPUT_SIZE 1024
extern char **environ;

char *__getCommand(void);
char **tokenCmd(char *line);
int execute(char **cmd, char **av);
ssize_t _getline(char **line, size_t *buffsize, FILE *stream);
void Comments(char ***cmd);

char *__env(char *args);
int __exxit_sh(char **toks, char *buff);
void __puts(char *str);
int __atoi(char *ptr);

void freeBuff(char **buff);
char *__strcpy(char *dest, char *src);
char *__strcat(char *dest, char *src);
int __strlen(char *s);
int __strcmp(char *s1, char *s2);
char *__strdup(const char *str);

int _putchar(char c);

#endif
