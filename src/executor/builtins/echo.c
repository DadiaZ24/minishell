#include "minishell.h"

bool	echo_utils(char *str)
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

bool	 echo(char **mtr, t_executor *exec)
{
	if (!mtr[1])
	{
		printf("\n");
		if (exec->is_child)
		{
			free_process(exec);
			exit(0);
		}
		return (1);
	}
	if (mtr[1] && echo_utils(mtr[1]))
		ft_putmtr(mtr + 2);
	else if (mtr[1])
	{
		ft_putmtr(++mtr);
		printf("\n");
	}
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	return (1);
}
