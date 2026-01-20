/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:09:47 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:09:59 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(long long nbr)
{
	long	nb;

	nb = nbr;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar(48 + nb);
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

void	ft_codex(int nb, char mod)
{
	char	*tab1;
	char	*tab2;

	tab1 = "0123456789abcdef";
	tab2 = "0123456789ABCDEF";
	if (mod == 'x')
		ft_putchar(tab1[nb]);
	if (mod == 'X')
		ft_putchar(tab2[nb]);
}

void	ft_hexa_conv(unsigned long long nbr, char mod)
{
	if (nbr >= 16)
	{
		ft_hexa_conv((nbr / 16), mod);
		ft_hexa_conv((nbr % 16), mod);
	}
	else
		ft_codex(nbr, mod);
}

int	ft_hexa(unsigned int nbr, char mod)
{
	ft_hexa_conv(nbr, mod);
	return (ft_number_count(nbr, 16));
}

int	ft_print_address(unsigned long long nbr)
{
	if (nbr == 0)
		return (ft_str_count("(nil)"));
	ft_putchar('0');
	ft_putchar('x');
	ft_hexa_conv(nbr, 'x');
	return (2 + ft_hex_count(nbr, 16));
}
