/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:21:55 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/05 22:21:55 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int calculate_size(char *str)
{
	int i;
	int new_size;

	i = -1;
	new_size = 0;
	while (str[++i])
	{
		if (!((str[i] == ' ' || str[i] == '\t') && (str[i + 1] == ' ' || str[i + 1] == '\t')))
			new_size++;
	}
	return (new_size);
}

char	*ft_trim_spaces(char *str)
{
	int i;
	int new_size;
	int j;
	char	*new_str;

	i = -1;
	j = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	new_size = calculate_size(str);
	new_str = (char *)malloc(sizeof(char) * (new_size + 1));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (!((str[i] == ' ' || str[i] == '\t') && (str[i + 1] == ' ' || str[i + 1] == '\t')))
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}
