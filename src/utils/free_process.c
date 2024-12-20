#include "minishell.h"

void	free_d(t_executor *exec)
{
	free_mtr(exec->shell->env);
	free(exec->cmds);
	free(exec->shell);
	free(exec->token);
	free(exec);
}

void	free_all(t_executor *exec)
{
	free(exec->shell->line);
	/* free_ast(exec->ast); */
	ft_free_cmds(*exec->cmds);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
}

void	free_process(t_executor *exec)
{
	free_all(exec);
	free_d(exec);
}
