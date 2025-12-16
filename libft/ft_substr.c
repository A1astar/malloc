/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:28:46 by alacroix          #+#    #+#             */
/*   Updated: 2024/11/15 12:39:43 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char const *src, char *dst, size_t len)
{
	char	*source;
	char	*dest;
	size_t	i;

	source = (char *)src;
	dest = (char *)dst;
	i = 0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	src_len;

	copy = NULL;
	src_len = ft_strlen(s);
	if (len > src_len)
		len = src_len;
	if (start >= src_len)
		len = 0;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strncpy(&s[start], copy, len);
	return (copy);
}
