/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:58:26 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:58:26 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *origin, char *find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!n && !origin)
		return (NULL);
	if (!origin[i] && !find[i])
		return (origin);
	if (!find[i])
		return (origin);
	while ((origin[i]))
	{
		j = 0;
		while (origin[i + j] == find[j] && (i + j) < n)
		{
			if (find[j] == '\0' && origin[i + j] == '\0')
				return (origin + i);
			j++;
		}
		if (find[j] == '\0')
			return (origin + i);
		i++;
	}
	return (0);
}
