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
			set_exit_status(exec->shell, 1);
			w_error("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		while(*mtr[1])
		{
			if (!ft_isdigit(*mtr[1]))
			{
				set_exit_status(exec->shell, 255);
				w_error("exit\nminishell: exit: ");
				w_error(mtr[1]);
				w_error(": numeric argument required\n");
				return ;
			}
			mtr[1]++;
		}
		status = ft_atoi(mtr[1]);
	}
	free_process(exec);
	exit(status);
}
