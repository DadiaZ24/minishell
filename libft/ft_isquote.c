/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:48:21 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/10/30 17:50:33 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isquote(int c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	else
		return (0);
}
