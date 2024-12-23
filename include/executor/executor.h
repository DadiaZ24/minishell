#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef MAX_PATH_LEN
#  define MAX_PATH_LEN 1024
# endif

int		pwd(char **mtr, t_executor *exec);
int 	cd(t_shell *shell, char **mtr, t_executor *exec);
bool	echo(char **mtr, t_executor *exec);
bool 	env(t_shell *shell, char **mtr, t_executor *exec);
void	exit_builtin(int status, t_executor *exec, char **mtr);
int		unset(char **mtr, t_executor *exec);

//Builtins.Utils
int		is_directory(char *path);
char	*getenvp(char **envp, char *var);
void	update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd);
void	update_env(t_shell *shell);
int 	exec_execve(int *r, char *str_path, t_executor *exec, t_cmds *cmds);
int		export(t_executor *exec);
char **realloc_env (char **env, int i);
bool bubblesort(t_executor *exec);
char	**export_body_update(char *arg, char **env, bool is_new, t_executor *exec);
int	print_export(t_executor *exec, char **env);
char	**export_body_update(char *arg, char **env, bool is_new, t_executor *exec);
char	**handle_entry(char *arg, char **env, bool is_new, char delimiter);
bool update_entry(char **env_entry, char *entry, bool is_new, int size);
char **new_entry(char **env, char *entry, int i);
char	**export_put_values(char **env, char *arg, int i);
bool	has_append_operator(char *arg);
bool	has_operator_before_equal(char *arg);
char **realloc_env (char **env, int i);

#endif