#include "minishell.h"

void	w_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}

int	exit_builtin(int status, t_executor *exec, char **mtr)
{
	int i;

	i = -1;
	if (mtr[1])
	{
		if (mtr[2])
			return (set_exit_status(exec->shell, 1), w_error("exit\nminishell: exit: too many arguments\n"), 1);
		while(mtr[1][++i])
		{
			if (!ft_isdigit(mtr[1][i]))
			{
				set_exit_status(exec->shell, 255);
				w_error("exit\nminishell: exit: ");
				w_error(mtr[1]);
				w_error(": numeric argument required\n");
				return (1);
			}
		}
		status = ft_atoi(mtr[1]);
	}
	free_process(exec);
	exit(status);
}
