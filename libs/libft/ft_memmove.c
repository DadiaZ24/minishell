/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:56:51 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:56:51 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, void *s2, size_t n)
{
	size_t	i;
	char	*dst;
	char	*src;

	dst = (char *)s1;
	src = (char *)s2;
	if (!s1 && !s2)
		return (0);
	i = -1;
	if (dst > src)
	{
		while (n-- > 0)
			dst[n] = src[n];
	}
	else
	{
		while (++i < n)
			dst[i] = src[i];
	}
	return (dst);
}
