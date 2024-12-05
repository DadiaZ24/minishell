/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:00:00 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/12/05 19:51:53 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	s_i;
	char	*new_s;

	i = 0;
	s_i = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (s_i + 1));
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strdup_quotes(const char *s)
{
	size_t	i;
	size_t	s_i;
	size_t	j;
	char	*new_s;

	i = 0;
	j = 0;
	s_i = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (s_i + 3));
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		if (s[i - 1] == '=')
			new_s[j++] = '"';
		new_s[j++] = s[i++];
	}
	new_s[j] = '"';
	new_s[j + 1] = '\0';
	return (new_s);
}
