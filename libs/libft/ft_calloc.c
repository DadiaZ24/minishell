/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:53:53 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:53:53 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*str;

	if (((nitems > 2147483647 && size != 0)
			|| (size > 2147483647 && nitems != 0)))
		return (NULL);
	str = malloc (nitems * size);
	if (!str)
		return (NULL);
	ft_bzero(str, size * nitems);
	return (str);
}
