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

void prompt(char *c, int len);

ssize_t take_input(char *input);

int run_commandfile(char *user_command, char *argv, char *envp[]);

void handle_command_exit(int status, const char *user_command);

void tokenize_command(char *user_command, char **args);

int exec_command(char *user_command, char *args[], char *argv, char **env);

int exec_command_withpath(char *user_command, char *args[], char **env);

void exitShell(int status);

int chk_cmd_before_fork(char *user_command);

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

char *custom_string_duplicate(const char *custom_string);

int custom_string_length(const char *custom_string);

int custom_string_cspan(const char *custom_string, const char *custom_chr);

char *custom_string_copy(char *custom_dest_string, const char *custom_src_string) ;

char *s_strchr(const char *string, int chr);

char *s_strcat(char *dest, const char *src);

int s_strcmp(const char *str1, const char *str2);

char *s_strstr(const char *haystack, const char *needle);

int s_strncmp(const char *s1, const char *s2, size_t n);

char *s_strtok(char *str, const char *delim);

int is_delimiter(char c, const char *delim);

char *getEnvVarValue(const char *envVarName, char *envp[]);

int tokenizeCommand(const char *userCommand, char *tokens[], int maxTokens);

char *handle_double_dollar(const char *cmd, char *envp[]);

void delete_comments(char *cmd);

int get_status_code(int status);

void IntStr(int val, char *strr, int size);

int execute_command(char *args[], int check, int *last_status,
					char *argv, char *envp[]);

int handle_cd(char *mycmd, char *args[], int check,
			  int *last_status, char *argv, char *envp[]);

int processExit(char *arguments[], int statusCheck, char *errorMsg);

int handle_setenv(char *mycmd, char *args[], int check, int *last_status);

int handle_unsetenv(char *mycmd, char *args[], int check, int *last_status);

void updateStatusVariable(char *arguments[], int argumentCount, int *result_size);
void generateEnvVarName(int value, char *result, int str_size);

int custom_string_parser(char *custom_input, const char *custom_delimiter,
						   char *custom_output[]);

void remove_quote(char *input, char *output);
int custom_program_entry(int custom_argc, char *custom_argv[], char *custom_envp[]);

int alias(char *args[], int check);

void signal_handler(int signal);

int check_positive_integer(char *custom_str);

int is_negative_integer(char *custom_str);

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
void char *cmd, char *output, int *i,
int *j, char *envp[]);
void double_dollar(char *cmd, char *output, int *i, int *j);
char *get_environ(char *var_name, char *envp[]);
char *get_process_id_string();
int s_isalnum(unsigned char c);
char *StrCpyM(char *beginning, size_t n);

void generateErrorMessage(test *testInstance, char *arguments[], char *errorMessage);
void processExitCode(test *unusedTestInstance, int exitCode);

void execute_custom_tasks(char *custom_copy, char *custom_args[], int custom_check,
							  int *custom_last_status, char *custom_argv, char *custom_envp[]);
int check_for_whitespace(char *custom_str);
int custom_command_handler(char *custom_mycmd, char *custom_args[], int custom_check,
                           int *custom_last_status, char *custom_argv, char *custom_envp[]);
int execute_custom_command(char *custom_command, char *custom_argv, char *custom_envp[]);

void intToString(int num, char *str, int str_size);
void print_err(const char *command, char *argv);

#endif
