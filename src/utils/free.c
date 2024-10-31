/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:26:12 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/30 15:45:06 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(char **tokens)
{
	t_token	*temp;
	
	temp = *tokens;
	while (temp)
	{
		temp = (*tokens)->next;
		temp->previous = NULL;
		free(*tokens);
		*tokens = temp;
	}
	ft_split
	free(tokens);
	exit(1);
}

void	ft_free_mtr(char **str)
{
	int	j;

	j = -1;
	while (str[++j])
		free(str[j]);
	free(str);
}
