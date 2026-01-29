/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:14:42 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/29 18:12:02 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static inline size_t *get_memblock_metadatas(void *ptr)
{
	return (size_t *)((char *)ptr - align16(sizeof(size_t)));
}

void *realloc(void *ptr, size_t size)
{
	if (!ptr)
		return malloc(size);
	if (!is_from_current_allocator(ptr))
		return NULL;
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	size_t *memblock_metadata = get_memblock_metadatas(ptr);
	size_t current_memblock_size = *memblock_metadata & ~1;
	size_t user_data_size;
	if (current_memblock_size > SMALL_MAX_SIZE)
		user_data_size = current_memblock_size - align16(sizeof(size_t)) - align16(sizeof(t_mmap_lst));
	else
		user_data_size = current_memblock_size - align16(sizeof(size_t));
	if (size <= user_data_size)
		return ptr;
	void *new_ptr = malloc(size);
	if (!new_ptr)
		return NULL;
	ft_memmove(new_ptr, ptr, size < user_data_size ? size : user_data_size);
	free(ptr);
	return new_ptr;
}
