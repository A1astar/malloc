/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:30:58 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/29 15:35:53 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t len)
{
	void *dst_origin;

	if (len == 0)
		return (dst);
	if (dst < src)
		return ft_memcpy(dst, src, len);
	else if (dst == src)
		return (dst);
	else
	{
		dst_origin = dst;
		while (len--)
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
		return dst_origin;
	}
}
