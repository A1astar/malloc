/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:09:45 by alacroix          #+#    #+#             */
/*   Updated: 2025/02/26 13:16:27 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	char	*new;
	size_t	s1_len;
	size_t	i;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (s1_len < size)
		size = s1_len;
	new = ft_calloc((size + 1), sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	return (new);
}
