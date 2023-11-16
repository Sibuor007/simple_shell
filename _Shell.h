#ifndef SHELL_H
#define SHELL_H

#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* these are MACROS to read and or write buffer */
#define BUFFER_SIZE_READ 	1024
#define BUFFER_SIZE_WRITE 	1024
#define FLUSH_BUFFER 		-1

/* these are MACROS used in command chaining */
#define NORMAL_COMMAND	0
#define OR_COMMAND	1
#define AND_COMMAND	2
#define CHAIN_COMMAND	3

/* these are function-like macros used in conversion */
#define _TO_LOWERCASE		1
#define UNSIGNED_CONVERSION	2

/* for string tokenizer and getline()*/
#define GETLINE_USAGE	0
#define STRTOK_USAGE 	0

#define FILE_HISTORY	"SIMPLE SHELL CMD HISTORY"
#define MAX_HISTORY	4096

extern char **_env_rn;


/**
 * struct str_lists - for a linked list (singly)
 * @_data: placeholder for data
 * @ptr_string: pointer a string
 * @_next: points to the _next node
 */
typedef struct str_lists
{
	int _data;
	char *ptr_string;
	struct str_lists *_next;
} str_lists_t;

/**
 *struct _info_pass - the function that holds arguments
 *to be passed to function calls. This eliminates bugs
 *that may be associated with function pointer for the structure
 *@_args: a string read from the arguments passed in getline()
 *@_argv: number of strings generated
 *@_str_path: string path for the read command
 *@_argc: count for the arguments passed
 *@_counts_line: count for the errors encountered
 *@_errno: generates error code with exit()
 *@flag_count: counter for flags encountered
 *@_filename: name of the program file
 *@_env_copy: the local copy of the linked list environment
 *@dl_env_rn: a modified copy of the linked list environment
 *@_history: the node that invokes relevant history
 *@_alias: node that invokes alias
 *@change_env_rn: activates when environment changes
 *@_status: the return type or value of the previous command
 *@buffer_cmd: in case of chaining, returns address of buffer cmd
 *@type_cmd_buffer: type of command
 *@_input_read: function that reads input from command line
 *@count_history: number of count in of lines in the history
 */

typedef struct _info_pass
{
	
	str_lists_t *_env_copy;
	str_lists_t *_history;
	str_lists_t *_alias;
	char *_args;
	char **_argv;
	char *_str_path;
	int _argc;
	unsigned int _counts_line;
	int _errno;
	int flag_count;
	char *_filename;
	char **dl_env_rn;
	int change_env_rn;
	int _status;

	char **buffer_cmd; /* in memory management - buffer and pointer */
	int type_cmd_buffer; /* type of command */
	int _input_read;
	int count_history;
} _info_pass_t;

#define INIT_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - structure that has the relevant
 *function and built_in string
 *@flag_type: command flag, builtin
 *@def_f: relevant function
 */
typedef struct built_in
{
	char *flag_type;
	int (*def_f)(_info_pass_t *);
} built_in_table;

/* function prototypes for _shLoop.c */
int _sh_loop(char **);

/* function prototypes for _Errors.c */
void puts_err(char *);
int putchar_err(char);
int put_def_f(char *c, char *def_f);
int puts_def_f(char *ptr_string, int def_f);

/* function prototypes for _String.c */
int str_len(char *);
int str_cmp(char *, char *);
char *_start(const char *, const char *);
char *str_cat(char *, char *);

/* function prototypes for _String_b.c */
char *str_cpy(char *, char *);
char *str_up(const char *);
void puts_(char *);
int putchar_(char);

/* function prototypes for _shellLoop.c */
int _h_shell(_info_pass_t *, char **);
int builtin_find(_info_pass_t *);
void command_find(_info_pass_t *);
void command_fork(_info_pass_t *);

/* function prototypes for _Parser.c */
int curr_cmd(_info_pass_t *, char *);
char *char_duplicate(char *, int, int);
char *_path_find(_info_pass_t *, char *, char *);

/* function prototypes for _Exits.c */
char* str_n_cpy(char *, char *, int);
char* str_n_cat(char *, char *, int);
void *str_chr(char *, char);

/* function prototypes for _Tokenizer.c */
char **_str_tow(char *, char *);
char **_str_tow_b(char *, char);

/* function prototypes for _Realloc.c */
char *mem_set(char *, char, unsigned int);
void _free(char **);
void *re_alloc(void *, unsigned int, unsigned int);

/* function prototypes for _Environ.c */
char *get_env(_info_pass_t *, const char *);
int e_env(_info_pass_t *);
int s_setenv(_info_pass_t *);
int u_unsetenv(_info_pass_t *);
int env_populate(_info_pass_t *);

/* function prototypes for _Getenv.c */
char **g_environ(_info_pass_t *);
int unset_env(_info_pass_t *, char *);
int set_env(_info_pass_t *, char *, char *);

/* function prototypes for _History.c */
char *g_history_f(_info_pass_t *info);
int history_write(_info_pass_t *info);
int history_read(_info_pass_t *info);
int history_built_l(_info_pass_t *info, char *_buff, int count_line);
int history_recall(_info_pass_t *info);

/* function prototypes for _Lists.c */
str_lists_t *node_add(str_lists_t **, const char *, int);
str_lists_t *node_add_end(str_lists_t **, const char *, int);
size_t p_str_list(const str_lists_t *);
int del_node_indx(str_lists_t **, unsigned int);
void _free_l(str_lists_t **);

/* function prototypes for _Memory.c*/
int free_f(void **);

/* function prototypes for _Atoi.c */
int _i_active(_info_pass_t *);
int delim_(char, char *);
int is_alpha(int);
int a_toi(char *);

/* function prototypes for _Errors_b.c */
int err_atoi(char *);
void p_error(_info_pass_t *, char *, char *);
int p_delim(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/* function prototypes for _Builtin.c */
int e_exit(_info_pass_t *);
int _cd(_info_pass_t *);
int _help(_info_pass_t *);

/* function prototypes for _Builtin_b.c */
int h_history(_info_pass_t *);
int a_alias(_info_pass_t *);
int our_unset_alias(_info_pass_t *, char *);
int our_set_alias(_info_pass_t *, char *);
int _printalias(str_lists_t *);


/* function prototypes for _Getline.c */
ssize_t g_input(_info_pass_t *);
int g_line(_info_pass_t *, char **, size_t *);
void in_handler(int);
ssize_t read_buf(_info_pass_t *, char *, size_t *);
ssize_t buff_input (_info_pass_t *, char **, size_t *);


/* function prototypes for _Getinfo.c */
void info_clear(_info_pass_t *);
void info_set(_info_pass_t *, char **);
void info_free(_info_pass_t *, int);

/* function prototypes for _Lists_b.c */
size_t len_list(const str_lists_t *);
char **str_list(str_lists_t *);
size_t p_list(const str_lists_t *);
str_lists_t *node_beg(str_lists_t *, char *, char);
ssize_t g_node_indx(str_lists_t *, str_lists_t *);

/* function prototypes for _Vars.c*/
int _chain(_info_pass_t *, char *, size_t *);
void _chain_check(_info_pass_t *, char *, size_t *, size_t, size_t);
int _alias_replace(_info_pass_t *);
int _vars_replace(_info_pass_t *);
int _str_replace(char **, char *);

#endif
