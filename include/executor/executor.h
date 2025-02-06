#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN 1024
#endif

#include <stdbool.h>

typedef struct s_export
{
	char	**key_left;
	char	**key_right;
	char	*arg_left;
	char	*arg_right;
	bool	append;
	bool 	arg_equals;
	bool 	env_equals;
	bool 	new_entry;
	bool 	do_nothing;
}	t_export;

int pwd(char **mtr, t_executor *exec);
int cd(t_shell *shell, char **mtr, t_executor *exec);
bool echo(char **mtr, t_executor *exec);
bool env(t_shell *shell, char **mtr, t_executor *exec);
int exit_builtin(int status, t_executor *exec, char **mtr);
int unset(char **mtr, t_executor *exec);

// Builtins.Utils
int is_directory(char *path);
int	check_is_dir(char *path);
char *getenvp(char **envp, char *var);
void update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd);
int exec_execve(int *r, char *str_path, t_executor *exec, t_cmds *cmds);
int export(t_executor *exec);
bool bubblesort(t_export *export);
char **export_body_update(char *arg, char **env, bool is_new, t_executor *exec);
void print_export(t_export *export);
char **export_body_update(char *arg, char **env, bool is_new, t_executor *exec);
char **handle_entry(char *arg, char **env, bool is_new, char delimiter);
bool update_entry(char **env_entry, char *entry, int size);
char **new_entry(char **env, char *entry, int i);
char **export_put_values(char **env, char *arg, int i);
bool has_append_operator(char *arg);
bool has_operator_before_equal(char *arg);
bool	check_if_exists(char *arg, char **env);
char	*join_entry(char *env_entry, char *entry, int size);
char	*swap_export(char *entry, int j);
int env_len(char **env);
t_export *init_export(t_export *export, t_executor *exec);
void free_export(t_export *export);
bool	check_append(char *arg);
void execute_append(t_export *export, t_executor *exec);
bool make_new_entry(t_export *export, t_executor *exec);
bool replace_entry(t_export *export, t_executor *exec);
bool execute_export(t_export *export, t_executor *exec);bool parse_export_equal(char *arg, t_export *export);
bool parse_export_no_equal(t_export *export);
bool parse_export(char *arg, t_export *export);
char **realloc_env(char **env);
void free_export_args(t_export *export);
int compare_result(t_export *export, char *s1, char *s2);

#endif