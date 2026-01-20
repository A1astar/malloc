/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:11:56 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/06 11:34:20 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			sign;
	long long	resultat;

	i = 0;
	sign = 1;
	resultat = 0;
	if (nptr[i] == '\0')
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		resultat = (resultat * 10) + (nptr[i] - '0');
		i++;
	}
	return (sign * resultat);
}
