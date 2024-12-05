#include "minishell.h"

void	free_d(t_executor *exec)
{
	free_mtr(exec->shell->env);
	free(exec->shell);
	free(exec->token);
	free(exec->ast);
	free(exec);
}

void	free_all(t_executor *exec)
{
	free(exec->shell->line);
	free_ast(exec->ast);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
}

void	free_process(t_executor *exec)
{
	free_all(exec);
	free_d(exec);
}
