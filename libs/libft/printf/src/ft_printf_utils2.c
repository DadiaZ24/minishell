/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:11:05 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/05/05 16:54:21 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

unsigned int	ft_usize(unsigned int nbr)
{
	unsigned int	count;

	count = 0;
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}

int	ft_utoa(unsigned int nbr)
{
	char	*newstr;
	int		size;
	int		result;

	size = ft_usize(nbr);
	newstr = (char *)malloc(sizeof(char) * (1 + size));
	if (!newstr)
		return (0);
	newstr[size] = '\0';
	if (nbr == 0)
		newstr[0] = '0';
	while (nbr != 0)
	{
		size--;
		newstr[size] = (nbr % 10) + 48;
		nbr /= 10;
	}
	result = ft_putstr(newstr);
	free(newstr);
	return (result);
}

int	ft_putstr(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!str)
	{
		result += write(1, "(null)", 6);
		return (result);
	}
	while (str[i])
	{
		result += write(1, &str[i], 1);
		i++;
	}
	return (result);
}
