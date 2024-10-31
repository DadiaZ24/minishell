/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:55:36 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:55:36 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ms;

	ms = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		if (ms[i] == (unsigned char)c)
			return (ms + i);
		i++;
		n--;
	}
	return (NULL);
}
