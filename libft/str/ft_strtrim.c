/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:28:26 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:54:46 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_a_sep(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = ft_strlen(s1) - 1;
	i = 0;
	if (s1[0] == '\0')
		return (ft_calloc(sizeof(char), 1));
	while (ft_is_a_sep(s1[start], set) == 1 && start <= end)
		start++;
	while (ft_is_a_sep(s1[end], set) == 1 && end >= start)
		end--;
	dest = (char *)malloc(((end - start) + 2) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (start <= end)
	{
		dest[i] = s1[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
