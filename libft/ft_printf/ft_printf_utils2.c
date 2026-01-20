/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:10:13 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:10:25 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_limit(int nbr)
{
	if (nbr < 0)
		return (4294967296 + nbr);
	else
		return (nbr);
}

int	ft_hex_count(unsigned long long nbr, int base)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

int	ft_number_count(long long nbr, int base)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

unsigned int	ft_str_count(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str)
	{
		ft_putchar(*(str++));
		i++;
	}
	return (i);
}
