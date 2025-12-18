/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:30:58 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/18 12:15:30 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*ptr;

	ptr = dst;
	if (dst > src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	return (ptr);
}
