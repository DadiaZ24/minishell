/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:50:38 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/31 17:22:12 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_token **tokens)
{
	char	*str;
	
	while(true)
	{
		str = read_history("Minishell: ")
		mini_split(str);
	}
}
