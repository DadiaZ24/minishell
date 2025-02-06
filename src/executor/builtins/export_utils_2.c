/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:41:11 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/06 14:41:11 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_result(t_export *export, char *s1, char *s2)
{
	int	result;

	if (export->arg_equals)
		result = ft_strncmp(s1, s2, ft_strlen(s1) - 1);
	else
		result = ft_strncmp(s1, s2, ft_strlen(s1));
	return (result);
}

bool	check_append(char *arg)
{
	if (!arg)
		return (false);
	if (ft_strchr(arg, '='))
	{
		while (*arg)
		{
			if (*arg == '+' && *(arg + 1) == '=')
				return (true);
		}
	}
	return (false);
}
