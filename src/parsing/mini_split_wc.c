/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_wc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:46:07 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/31 17:00:19 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lock_count(char **s, int *c_words, int *i, int *quote)
{
	if (ft_pipe_or_redirect(*s) > 0 && i == 0)
	{
		if (ft_pipe_or_redirect(*s) == 2)
			(*s)++;
		c_words++;
	}
	else if (ft_isquote(*s) > 0 && i == 0)
	{
		i = 1
		c_words++;
		quote = ft_isquote(*s);
	}
	else if (!ft_iswhitespc(*s) && i == 0)
	{
		i = 1;
		c_words++;
	}
}

void	unlock_count(char **s, int *i)
{
	if (ft_isquote(*s) == quote && i == 1)
			i = 0;
	else if (ft_iswhitespc(*s))
			i = 0;
}
