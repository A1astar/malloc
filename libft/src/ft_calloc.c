/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:08:33 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/18 12:14:28 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
