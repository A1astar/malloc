/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:14:42 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/28 16:32:55 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static inline size_t *get_memblock_metadatas(void *ptr)
{
	return (size_t *)((char *)ptr - align16(sizeof(size_t)));
}

void *realloc(void *ptr, size_t size)
{
	if (!ptr || !is_from_current_allocator(ptr))
		return malloc(size);
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	size_t *memblock_metadata = get_memblock_metadatas(ptr);
	size_t current_memblock_size = *memblock_metadata & ~1;
	size_t user_data_size = current_memblock_size - align16(sizeof(size_t));
	if (size <= user_data_size)
		return ptr;
	void *new_ptr = malloc(size);
	if (!new_ptr)
		return NULL;
	ft_memmove(new_ptr, ptr, current_memblock_size - align16(sizeof(size_t)));
	free(ptr);
	return new_ptr;
}
