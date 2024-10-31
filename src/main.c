/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:29:40 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/10/26 18:39:59 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (0);
	minishell(tokens);
	free_tokens(tokens);
	return (1);
}
