#include "minishell.h"

void	exit_builtin(int status, t_executor *exec)
{
	free_process(exec);
	exit(status);
}
