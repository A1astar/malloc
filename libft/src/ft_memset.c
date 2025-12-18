/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:31:10 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/18 12:15:34 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	unsigned char	*string;
	size_t			i;

	value = (unsigned char)c;
	string = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		string[i] = value;
		i++;
	}
	return (b);
}
