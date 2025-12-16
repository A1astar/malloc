/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:51:00 by alacroix          #+#    #+#             */
/*   Updated: 2024/11/11 11:38:55 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, char const *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[j] != '\0')
	{
		j++;
	}
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		len;

	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	dest = (char *) malloc (len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = '\0';
	ft_strcpy(dest, s1);
	ft_strcpy(dest, s2);
	return (dest);
}
