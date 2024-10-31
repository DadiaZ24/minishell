/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:58:48 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:58:48 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstring;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	newstring = (char *)malloc(sizeof(char) * (len + 1));
	if (!newstring)
		return (0);
	i = 0;
	while (s[start] && i < len)
	{
		newstring[i] = s[start];
		start++;
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
