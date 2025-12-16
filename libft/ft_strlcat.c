/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:48:51 by alacroix          #+#    #+#             */
/*   Updated: 2024/11/07 16:48:53 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_lengh;
	size_t	src_lengh;
	size_t	i;

	dst_lengh = ft_strlen(dst);
	src_lengh = ft_strlen(src);
	i = 0;
	if (size == 0 || dst_lengh > size)
		return (src_lengh + size);
	if (src == NULL)
		return (dst_lengh);
	while (src[i] && (dst_lengh + i < size -1))
	{
		dst[dst_lengh + i] = src[i];
		i++;
	}
	dst[dst_lengh + i] = '\0';
	return (src_lengh + dst_lengh);
}
