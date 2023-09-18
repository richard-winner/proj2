#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>


/* write/read buff */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* chaining command */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Number conversion */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly_linked lst
 * @str: The str
 * @num: Field number
 * @next: ptr to nxt ext node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-argument that passes into a function,
 * which allows uniform prototype for function pointer struct
 * @argv: args gotten from an array of str
 * @argc: arg count
 * @readfd: this reads the input of fd
 * @err_num: exits the error code
 * @path: a path from the current command str
 * @fname: the filename of a program
 * @line_count: error counter
 * @histcount: it counts the history line
 * @arg: a str generated from getline containing args
 * @env: a copy of linked list from local enviroment
 * @environ: custom modified enviroment copy
 * @history: the node history
 * @cmd_buf_type: && or CMD_type
 * @linecount_flag: counts line of an input
 * @env_changed: if environment changes
 * @status: it returns status of the last executed command
 * @cmd_buf: cmd_buf pointer address
 * @alias: node alias
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - it contains a built-in str and related function
 * @func: it's a function
 * @type: built-in command flag
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* atoi.c */
int simp_shll_interactive(info_t *);
int simp_shll_is_delim(char, char *);
int _simp_shll_isalpha(int);
int _simp_shll_atoi(char *);

/* parser.c */
int simp_shll_is_cmd(info_t *, char *);
char *simp_shll_dup_chars(char *, int, int);
char *simp_shll_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* string.c */
int _simp_shll_strlen(char *);
int _simp_shll_strcmp(char *, char *);
char *simp_shll_starts_with(const char *, const char *);
char *_simp_shll_strcat(char *, char *);

/* string1.c */
char *_simp_shll_strcpy(char *, char *);
char *_simp_shll_strdup(const char *);
void _simp_shll_puts(char *);
int _simp_shll_putchar(char);

/* exits.c */
char *_simp_shll_strncpy(char *, char *, int);
char *_simp_shll_strncat(char *, char *, int);
char *_simp_shll_strchr(char *, char);

/* errors1.c */
int _simp_shll_erratoi(char *);
void simp_shll_print_error(info_t *, char *);
int simp_shll_print_d(int, int);
char *simp_shll_convert_number(long int, int, int);
void simp_shll_remove_comments(char *);

/* errors.c */
void _simp_shll_eputs(char *);
int _simp_shll_eputchar(char);
int _simp_shll_putfd(char c, int fd);
int _simp_shll_putsfd(char *str, int fd);

/* realloc.c */
char *_simp_shll_memset(char *, char, unsigned int);
void simp_shll_ffree(char **);
void *_simp_shll_realloc(void *, unsigned int, unsigned int);

/* shloop.c */
int simp_shll_hsh(info_t *, char **);
int simp_shll_find_builtin(info_t *);
void simp_shll_find_cmd(info_t *);
void simp_shll_fork_cmd(info_t *);

/* lists.c */
list_t *simp_shll_add_node(list_t **, const char *, int);
list_t *simp_shll_add_node_end(list_t **, const char *, int);
size_t simp_shll_print_list_str(const list_t *);
int simp_shll_delete_node_at_index(list_t **, unsigned int);
void simp_shll_free_list(list_t **);

/* builtin.c */
int _simp_shll_myexit(info_t *);
int _simp_shll_mycd(info_t *);
int _simp_shll_myhelp(info_t *);

/* tokenizer.c */
char **simp_shll_strtow(char *, char *);
char **simp_shll_strtow2(char *, char);

/* getline.c */
ssize_t simp_shll_get_input(info_t *);
int _simp_shll_getline(info_t *, char **, size_t *);
void simp_shll_sigintHandler(int);

/* getinfo.c */
void simp_shll_clear_info(info_t *);
void simp_shll_set_info(info_t *, char **);
void simp_shll_free_info(info_t *, int);

/* environ.c */
char *_simp_shll_getenv(info_t *, const char *);
int _simp_shll_myenv(info_t *);
int _simp_shll_mysetenv(info_t *);
int _simp_shll_myunsetenv(info_t *);
int simp_shll_populate_env_list(info_t *);

/* getenv.c */
char **simp_shll_get_environ(info_t *);
int _simp_shll_unsetenv(info_t *, char *);
int _simp_shll_setenv(info_t *, char *, char *);

/* history.c */
char *simp_shll_get_history_file(info_t *info);
int simp_shll_write_history(info_t *info);
int simp_shll_read_history(info_t *info);
int simp_shll_build_history_list(info_t *info, char *buf, int linecount);
int simp_shll_renumber_history(info_t *info);

/* memory.c */
int simp_shll_bfree(void **);

/* builtin1.c */
int _simp_shll_myhistory(info_t *);
int _simp_shll_myalias(info_t *);

/* lists1.c */
size_t simp_shll_list_len(const list_t *);
char **simp_shll_list_to_strings(list_t *);
size_t simp_shll_print_list(const list_t *);
list_t *simp_shll_node_starts_with(list_t *, char *, char);
ssize_t simp_shll_get_node_index(list_t *, list_t *);

/* vars.c */
int simp_shll_is_chain(info_t *, char *, size_t *);
void simp_shll_check_chain(info_t *, char *, size_t *, size_t, size_t);
int simp_shll_replace_alias(info_t *);
int simp_shll_replace_vars(info_t *);
int simp_shll_replace_string(char **, char *);

#endif