/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 17:13:57 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void override_malloc()
{
	static void *(*original_malloc)(size_t size) = NULL;
	if(!original_malloc)
	original_malloc = dlsym(RTLD_NEXT, "malloc");
	(void)original_malloc;
}

static inline size_t align_requested_size(size_t size)
{
	return align16(sizeof(size_t)) + align16(size);
}

void *malloc(size_t size)
{
	//override_malloc();
	//pthread_mutex_lock(&malloc_mutex);
	if (size == 0)
		return NULL;
	size_t aligned_size = align_requested_size(size);
	void *ptr = NULL;
	if (aligned_size <= TINY_MAX_SIZE)
		ptr = get_memblock_from_arena(TINY_ARENA, aligned_size);
	else if (aligned_size <= SMALL_MAX_SIZE)
		ptr = get_memblock_from_arena(SMALL_ARENA, aligned_size);
	else
		ptr = get_memblock_from_mmap(aligned_size);
//	pthread_mutex_unlock(&malloc_mutex);
	return ptr;
}
