#include "minishell.h"

void	exit_builtin(int status, t_executor *exec, char **mtr)
{
	if (mtr[1])
	{
		if (mtr[2])
		{
			exec->shell->status = 1;
			return ;
		}
		status = ft_atoi(mtr[1]);
		if (!ft_isdigit(mtr[1][0]) && mtr[1][0] != '-' && mtr[1][0] != '+')
			status = 2;
	}
	free_process(exec);
	exit(status);
}
