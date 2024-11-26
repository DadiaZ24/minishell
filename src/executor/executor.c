#include "minishell.h"

int executor(t_token **tokens, t_shell *shell)
{
	if (!strncmp((*tokens)->info, "cd", ft_strlen((*tokens)->info)))
		cd(shell, tokens);
	else if (!strncmp((*tokens)->info, "pwd", ft_strlen((*tokens)->info)))
		pwd(tokens);
	else if (!strncmp((*tokens)->info, "echo", ft_strlen((*tokens)->info)))
		echo(shell, tokens);
	/*else if (!strncmp((*tokens)->info, "export", ft_strlen((*tokens)->info)))
		//TODO
		(void);
	else if (!strncmp((*tokens)->info, "unset", ft_strlen((*tokens)->info)))
		//TODO
		(void);*/
	else if (!strncmp((*tokens)->info, "env", ft_strlen((*tokens)->info)))
		env(shell, tokens);
	else if (!strncmp((*tokens)->info, "exit", ft_strlen((*tokens)->info)))
		exit(shell->status);
	else
		return (1);
	// TODO EXECVE
	return (1);
}

