/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:59:54 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/26 13:02:11 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Ne pas oublier de caster en (void **) quand on appelle la fonction !!
size_t	ft_tabsize(void **tab)
{
	size_t	i;

	i = 0;
	if (!*tab || !tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}
