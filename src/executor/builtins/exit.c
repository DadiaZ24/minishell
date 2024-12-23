#include "minishell.h"

void	w_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}

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
