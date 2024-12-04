#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef MAX_PATH_LEN
#  define MAX_PATH_LEN 1024
# endif

int		pwd(char **mtr, t_executor *exec);
int 	cd(t_shell *shell, char **mtr, t_executor *exec);
bool	echo(char **mtr, t_executor *exec);
bool 	env(t_shell *shell, char **mtr, t_executor *exec);
void	exit_builtin(int status, t_executor *exec);

//Builtins.Utils
int		is_directory(char *path);
char	*getenvp(char **envp, char *var);
void 	update_pwd_env(char **envp, char *oldpwd, char *pwd);
void	update_env(t_shell *shell);

#endif