#ifndef _MAIN_
#define _MAIN_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM "\t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct data - struct that contains all relevant data on runtime
 * @aev: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @__environ: environment variable
 * @pid: process ID of the shell.
 */
typedef struct data
{
	char **aev;
	char *input;
	char **args;
	int status;
	int counter;
	char **__environ;
	char *pid;
} data__shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data__shell *node);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data__shell *node, char *input, int i, int bool);
int check_syntax_error(data__shell *node, char *input);

/* shell.c */
char *without_comment(char *in);
void shell(data__shell *node);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data__shell *node);
int split_commands(data__shell *node, char *input);
char **split_line(char *input);

/* rep_var.c */
void check__env(r_var **h, char *in, data__shell *data);
int check_vars(r_var **h, char *in, char *st, data__shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data__shell *node);

/* get_line.c */
void bring__line(char **linptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **linptr, size_t *n, FILE *str_eam);

/* Exec__line */
int Exec__line(data__shell *node);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **__environ);
int is_executable(data__shell *node);
int check_error_cmd(char *dir, data__shell *node);
int cmd_exec(data__shell *node);

/* env1.c */
char *_getenv(const char *name, char **__environ);
int __env(data__shell *node);

/* env2.c */
char *copy_info(char *name, char *value);
void set__env(char *name, char *value, data__shell *node);
int _setenv(data__shell *node);
int _unsetenv(data__shell *node);

/* cd.c */
void cd_dot(data__shell *node);
void cd_to(data__shell *node);
void cd_previous(data__shell *node);
void cd_to_home(data__shell *node);

/* cd_shell.c */
int cd_shell(data__shell *node);

/* git__builtin */
int (*git__builtin(char *commnd))(data__shell *node);

/* _exit.c */
int temp(data__shell *node);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(data__shell *, char *, char *, char *);
char *error_get_cd(data__shell *node);
char *error_not_found(data__shell *node);
char *error_temp(data__shell *node);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error__env(data__shell *node);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data__shell *node);


/* get_error.c */
int get_error(data__shell *node, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help__env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(data__shell *node);

#endif
