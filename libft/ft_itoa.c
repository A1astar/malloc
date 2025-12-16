/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:59:47 by alacroix          #+#    #+#             */
/*   Updated: 2024/11/13 20:44:55 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	char_cpy(char c, char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	string[i] = c;
	string[i + 1] = '\0';
}

static void	ft_converter(int nbr, char *dest)
{
	long	nb;

	nb = nbr;
	if (nb < 0)
	{
		char_cpy('-', dest);
		nb *= -1;
	}
	if (nb >= 0 && nb <= 9)
	{
		char_cpy((48 + nb), dest);
	}
	else
	{
		ft_converter(nb / 10, dest);
		ft_converter(nb % 10, dest);
	}
}

static int	counter(int nb)
{
	int		i;
	long	nbr;

	nbr = nb;
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
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = counter(n);
	str = NULL;
	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	ft_converter(n, str);
	return (str);
}
