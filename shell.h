#ifndef _SHELL_H_
#define _SHELL_H_

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
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - the real struct that contains all relevant data on runtime
 * @av: an argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

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
 * struct r_var_list - The real single linked list
 * @len_var: a length of the variable
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
 * struct builtin_s - The builtin struct for command args.
 * @name: name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *mydata);
} builtin_t;

/* 0_list.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* 1_list.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* 0_string.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/*memory.c*/

void _memcpy(void *dp, const void *sp, unsigned int size);
void *_realloc(void *p, unsigned int o_s, unsigned int n_s);
char **_reallocdp(char **p, unsigned int o_s, unsigned int n_s);

/* 1_string.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* 2_string.c */
void rev_string(char *s);

/* 4_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *mydata, char *input, int i, int bool);
int check_syntax_error(data_shell *mydata, char *input);

/* shellLoop.c */
char *without_comment(char *in);
void shell_loop(data_shell *datash);

/* readLine.c */
char *read_line(int *value);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *mydata);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* repVar.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *mydata);

/* getLine.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* execLine */
int exec_line(data_shell *mydata);

/* executor.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *mydata);
int check_error_cmd(char *dir, data_shell *mydata);
int cmd_exec(data_shell *mydata);

/* 0_envi.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *mydata);

/* 1_envi.c */
char *copy_info(char *n, char *v);
void set_env(char *n, char *v, data_shell *mydata);
int _setenv(data_shell *mydata);
int _unsetenv(data_shell *mydata);

/* changdir.c */
void cd_dot(data_shell *mydata);
void cd_to(data_shell *mydata);
void cd_previous(data_shell *mydata);
void cd_to_home(data_shell *mydata);

/* cdShell.c */
int cd_shell(data_shell *mydatash);

/* builtin.c */
int (*get_builtin(char *cmd))(data_shell *mydata);

/* exitShell.c */
int exit_shell(data_shell *mydata);

/* stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* 0_error.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *mydata);
char *error_not_found(data_shell *mydata);
char *error_exit_shell(data_shell *mydata);

/* 1_error.c */
char *error_get_alias(char **args);
char *error_env(data_shell *mydata);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *mydata);


/* 2_error.c */
int get_error(data_shell *mydata, int eval);

/* getSigint.c */
void get_sigint(int sig);

/* 0_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* 1_help.c */
void help(void);
void help_alias(void);
void help_cd(void);

/* 2_help.c */
int get_help(data_shell *mydata);

#endif /*SHELL.H*/
