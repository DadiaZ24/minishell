/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:50 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:42:50 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	echo_utils(char *str)
{
	int	i;

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

bool	echo(char **mtr, t_executor *exec)
{
	int		i;
	bool	check;

	i = 0;
	check = false;
	if (!mtr[1])
	{
		write(1, "\n", 1);
		if (exec->is_child)
		{
			free_process(exec);
			exit(0);
		}
		return (set_exit_status(exec->shell, 0), 1);
	}
	if (mtr[1] && mtr[1][0] && mtr[1][0] == '-'
		&& mtr[1][1] && mtr[1][1] == 'n')
	{
		while (mtr[++i])
		{
			if (!echo_utils(mtr[i]))
			{
				ft_putmtr(mtr + i);
				check = true;
			}
		}
	}
	if (!check)
	{
		if (mtr[1])
		{
			ft_putmtr(++mtr);
			write(1, "\n", 1);
		}
	}
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	return (set_exit_status(exec->shell, 0), 1);
}
