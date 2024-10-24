/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:05:23 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/02/04 15:05:23 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	ft_format(char c, va_list ap)
{
	int	result;

	result = 0;
	if (!c)
		return (0);
	else if (c == 'c')
		result += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		result += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		result += ft_putptr(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		result += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		result += ft_utoa(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		result += ft_putnbrhex(va_arg(ap, unsigned int), c);
	else if (c == '%')
		result += write(1, "%", 1);
	return (result);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		result;

	va_start(ap, str);
	result = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '%')
			result += ft_format(*(++str), ap);
		else
			result += write(1, str, 1);
		++str;
	}
	va_end(ap);
	return (result);
}
