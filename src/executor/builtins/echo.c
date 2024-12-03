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

bool	echo(char **mtr)
{
	if (!mtr[1])
		return (printf("\n"), false);
	if (mtr[1] && echo_utils(mtr[1]))
		ft_putmtr(mtr + 2);
	else if (mtr[1])
	{
		ft_putmtr(++mtr);
		write(1, "\n", 1);
	}
	return (true);
}
