/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:58:35 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/04/09 14:58:35 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char const *s, char const c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s;
	int		size;
	char	*newstring;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	i = 0;
	s = 0;
	while (s1[s] && ft_check(set, s1[s]))
		s++;
	while (size > s && ft_check(set, s1[size - 1]))
		size--;
	newstring = (char *)malloc(sizeof(char) * (size - s + 1));
	if (!newstring)
		return (0);
	while (size > s)
	{
		newstring[i] = s1[s];
		i++;
		s++;
	}
	newstring[i] = '\0';
	return (newstring);
}
