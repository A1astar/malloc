/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:30:49 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 16:43:13 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int nb, int power)
{
	int	i;
	int	j;

	i = 1;
	j = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power == 1)
		return (nb);
	while (i < power)
	{
		nb *= j;
		i++;
	}
	return (nb);
}
