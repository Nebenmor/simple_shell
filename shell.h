#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#define TOK_DELIM " \t\r\n\a"

#define INPUT_SIZE 200

#define LOOP 10

#define PATH_SIZE 1024

#define ARG_SIZE 200

/**
 * struct info - A struct type tracting the status of function
 * @status: variable to hold status code
 */
typedef struct info
{
	int status;
} test;

void set_executable_name(char *name);

void prompt_func(char *c, int len);

ssize_t takeing_input(char *input);

int run_command_of_files(char *user_command, char *argv, char *envp[]);

void handle_command_exit(int status, const char *user_command);

void tokenizing_the_user_command(char *user_command, char **args);

int execute_the_command(char *user_command, char *args[],
		char *argv, char **env);

int executing_the_command_withPath(char *user_command,
		char *args[], char **env);

void exit_the_Shell(int status);

int checking_cmd_before_fork(char *user_command);

int setenv_cmd(char *user_command);

int unsetenv_cmd(char *user_command);

int unset_env(char *var);

int token_command(char *user_command, char *args[]);

int set_env_var(char *var, char *value);

int cd_dir(const char *arg_count, char *argument_count, char *envp[]);

int upd_env_var(const char *poth, char *environ[]);

int change_dir(const char *poth, char *argvo);

int pass_cd_arg(const char *user_command);

ssize_t get_line(char *buffer, size_t size);

char *s_strdup(const char *string);

int s_strlen(const char *string);

int s_strcspn(const char *string, const char *chr);

char *s_strcpy(char *dest_string, const char *src_String);

char *s_strchr(const char *string, int chr);

char *s_strcat(char *dest, const char *src);

int s_strcmp(const char *str1, const char *str2);

char *s_strstr(const char *haystack, const char *needle);

int s_strncmp(const char *s1, const char *s2, size_t n);

char *s_strtok(char *str, const char *delim);

int is_delimiter(char c, const char *delim);

char *s_getenv(const char *string, char *envp[]);

int sep_cmd(const char *user_command, char *result[], int num);

char *handle_double_dollar(const char *cmd, char *envp[]);

void delete_comments(char *cmd);

int get_status_code(int status);

void IntStr(int val, char *strr, int size);

int executing_comm(char *args[], int check, int *last_status,
					char *argv, char *envp[]);

int handling_cd_command(char *mycmd, char *args[], int check,
			  int *last_status, char *argv, char *envp[]);

int handle_exit(char *args[], int check, char *argv);

int handling_setenv_command(char *mycmd, char *args[],
		int check, int *last_status);

int handling_unsetenv_command(char *mycmd, char *args[],
		int check, int *last_status);

void replace_status_variable(char *args[], int count, int *last_status);

int split_logical_operator(char *input, const char *delimiter,
						   char *output[]);

void remove_quote(char *input, char *output);

int alias(char *args[], int check);

void handling_signal(int signal);

int ispositiveInt(char *str);

int isnegativeInt(char *str);

int execute_commands_from_file(const char *filename, char *envp[],
							   char *program_name);

int check_cmd(char *mycmd);

char *_itoa(int num);

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t s_getline(char **lineptr, size_t *n, FILE *stream);
void *s_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int is_whitespace(char c);
int is_word_start(char *str, int index);

void pwd(void);
void handle_pwd(char *args[]);

char *handle_double_dollars(char *cmd, char *envp[]);
void deal_with_env_variable(char *cmd, char *output, int *i,
		int *j, char *envp[]);
void double_dollar(char *cmd, char *output, int *i, int *j);
char *get_environ(char *variable_name, char *envp[]);
char *get_pid_str();
int s_isalnum(unsigned char c);
char *StrCpyM(char *beginning, size_t n);

void createAndWriteErrorMessage(test *mytest, char *args[], char *argv);
void handleExitWithCode(test *mytest, int code);

void execute_logical_commands(char *copy, char *args[], int check,
							  int *last_status, char *argv, char *envp[]);
int is_whitespace_string(char *str);
int handle_noninbuilt_cmd(char *mycmd, char *args[], int check,
						  int *last_status, char *argv, char *envp[]);
int run_command(char *user_command, char *argv, char *envp[]);

void intToString(int num, char *str, int str_size);
void print_err(const char *command, char *argv);

#endif
