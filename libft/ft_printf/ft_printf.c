/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:09:08 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 12:40:55 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	ft_put_arg(const char c, va_list args)
{
	long long	nbr;

	if (c == '%')
		return (ft_putchar('%'), 1);
	if (c == 'c')
		return (ft_putchar((char)va_arg(args, int)), 1);
	if (c == 's')
		return (ft_str_count(va_arg(args, char *)));
	if (c == 'p')
		return (ft_print_address(va_arg(args, unsigned long long)));
	if (c == 'd' || c == 'i')
	{
		nbr = va_arg(args, int);
		ft_putnbr(nbr);
		return (ft_number_count(nbr, 10));
	}
	if (c == 'z')
	{
		size_t number = va_arg(args, size_t);
		ft_putnbr(number);
		return (ft_number_count(number, 10));
	}
	if (c == 'u')
	{
		nbr = ft_limit(va_arg(args, unsigned int));
		ft_putnbr(nbr);
		return (ft_number_count(nbr, 10));
	}
	if (c == 'x' || c == 'X')
		return (ft_hexa(va_arg(args, int), c));
	return (-1);
}

static int	ft_param_reader(const char *str, va_list args)
{
	int	len;
	int	temp;

	len = 0;
	temp = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			temp = ft_put_arg(*(++str), args);
			if (temp == -1)
				return (-1);
			len += temp;
			str++;
		}
		else
		{
			ft_putchar(*(str)++);
			len++;
		}
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	len = ft_param_reader(str, args);
	va_end(args);
	if (len == -1)
		return (-1);
	return (len);
}
