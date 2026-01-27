/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:14:42 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 15:45:52 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static inline size_t *get_memblock_metadatas(void *ptr)
{
	return (size_t *)((char *)ptr - align16(sizeof(size_t)));
}

void *ft_realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&malloc_mutex);
	if (!ptr)
		return ft_malloc(size);
	if (size == 0)
	{
		ft_free(ptr);
		return NULL;
	}
	size_t *memblock_metadata = get_memblock_metadatas(ptr);
	size_t current_memblock_size = *memblock_metadata & ~1;
	if (size <= current_memblock_size)
		return ptr;
	void *new_ptr = ft_malloc(size);
	if (!new_ptr)
		return NULL;
	ft_memmove(new_ptr, ptr, current_memblock_size);
	ft_free(ptr);
	pthread_mutex_unlock(&malloc_mutex);
	return new_ptr;
}
