#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef MAX_PATH_LEN
#  define MAX_PATH_LEN 1024
# endif

typedef struct s_shell
{
	char	*line;
	int		status;
	char	**env;
	char	**export;

}	t_shell;


int		pwd(t_token **tokens);
void 	cd(t_shell *shell, t_token **tokens);
bool	echo(t_shell *shell, t_token **tokens);
bool 	env(t_shell *shell, t_token **tokens);

//Builtins.Utils
int		is_directory(char *path);
char	*getenvp(char **envp, char *var);
void 	update_pwd_env(char **envp, char *oldpwd, char *pwd);
void	update_env(t_shell *shell);

#endif