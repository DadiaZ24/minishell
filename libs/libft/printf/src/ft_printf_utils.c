/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:09:22 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/05/04 14:11:26 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putchar(int c)
{
	int	result;

	result = 0;
	result += write(1, &c, 1);
	return (result);
}

int	ft_putnbr(int nbr)
{
	int	result;

	result = 0;
	if (nbr == -2147483648)
	{
		result += write(1, "-2147483648", 11);
		return (result);
	}
	if (nbr < 0)
	{
		result += ft_putchar('-');
		nbr *= -1;
	}
	if (nbr < 10)
		result += ft_putchar(nbr + 48);
	else
	{
		result += ft_putnbr((nbr / 10));
		result += ft_putnbr((nbr % 10));
	}
	return (result);
}

int	ft_putnbrhex(unsigned int nbr, const char c)
{
	char	*base;
	int		result;

	result = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		result += ft_putnbrhex((nbr / 16), c);
		result += ft_putnbrhex((nbr % 16), c);
	}
	else
	{
		result += write(1, &base[nbr], 1);
	}
	return (result);
}

int	putptrhex(unsigned long nbr, const char c)
{
	char	*base;
	int		result;

	result = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		result += putptrhex((nbr / 16), c);
		result += putptrhex((nbr % 16), c);
	}
	else
	{
		result += write(1, &base[nbr], 1);
	}
	return (result);
}

int	ft_putptr(unsigned long nbr)
{
	int		result;

	result = 0;
	if (!nbr)
		return (write(1, "(nil)", 5));
	result += ft_putstr("0x");
	result += putptrhex(nbr, 'x');
	return (result);
}
