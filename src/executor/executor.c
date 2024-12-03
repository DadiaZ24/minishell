#include "minishell.h"

int	executor(t_ast **ast, t_shell *shell)
{
	if (!strncmp((*ast)->arg[0], "cd", ft_strlen((*ast)->arg[0])))
		cd(shell, (*ast)->arg);
	else if (!strncmp((*ast)->arg[0], "pwd", ft_strlen((*ast)->arg[0])))
		pwd((*ast)->arg);
	else if (!strncmp((*ast)->arg[0], "echo", ft_strlen((*ast)->arg[0])))
		echo((*ast)->arg);
	/*else if (!strncmp((*tokens)->info, "export", ft_strlen((*tokens)->info)))
		//TODO
		(void);
	else if (!strncmp((*tokens)->info, "unset", ft_strlen((*tokens)->info)))
		//TODO
		(void);*/
	else if (!strncmp((*ast)->arg[0], "env", ft_strlen((*ast)->arg[0])))
		env(shell, (*ast)->arg);
	else if (!strncmp((*ast)->arg[0], "exit", ft_strlen((*ast)->arg[0])))
		exit(shell->status);
	else
		return (1);
	// TODO EXECVE
	return (1);
}

