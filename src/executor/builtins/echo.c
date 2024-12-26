#include "minishell.h"

bool echo_utils(char *str)
{
	int i;

	i = -1;
	if (str[++i] == '-')
	{
		if (str[++i] == 'n')
			while (str[i] == 'n')
				++i;
		if (!str[i])
			return (true);
		else
			return (false);
	}
	return (false);
}

bool echo(char **mtr, t_executor *exec)
{
	if (!mtr[1])
	{
		write(1, "\n", 1);
		if (exec->is_child)
		{
			free_process(exec);
			exec->shell->status = 0;
			exit(0);
		}
		return (set_exit_status(exec->shell, 0), 1);
	}
	if (mtr[1] && echo_utils(mtr[1]))
		ft_putmtr(mtr + 2);
	else if (mtr[1])
	{
		ft_putmtr(++mtr);
		write(1, "\n", 1);
	}
	if (exec->is_child)
	{
		free_process(exec);
		set_exit_status(exec->shell, 0);
		exit(0);
	}
	return (set_exit_status(exec->shell, 0), 1);
}
