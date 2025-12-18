/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:00:04 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/18 12:16:39 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_strcomp(const char *a, const char *b, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && a[i] && b[i])
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	if (b[i] != '\0')
		return ((unsigned char)a[i] - (unsigned char)b[i]);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (i + little_len <= len && big[i])
	{
		if (big[i] == little[0])
		{
			if (ft_strcomp(&big[i], little, len - i) == 0)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
