/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:08:33 by alacroix          #+#    #+#             */
/*   Updated: 2025/01/04 15:55:03 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = NULL;
	ptr = malloc (nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
