/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:40 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:57:40 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(src);
	i = 0;
	if (!dst || !src)
		return (0);
	if (n == 0)
		return (size);
	while ((src[i]) && (i < n - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (size);
}
