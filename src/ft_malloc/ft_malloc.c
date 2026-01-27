/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 15:39:34 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

// void override_malloc()
// {
// 	static void *(*original_malloc)(size_t size) = NULL;
// 	if(!original_malloc)
// 	original_malloc = dlsym(RTLD_NEXT, "malloc");
// 	(void)original_malloc;
// }

static inline size_t align_requested_size(size_t size)
{
	return align16(sizeof(size_t)) + align16(size);
}

static inline mutex_init()
{
	static volatile bool mutex_initialized = false;
	if(!mutex_initialized)
	{
		pthread_mutex_init(&malloc_mutex, NULL);
		mutex_initialized = true;
	}
}

void *ft_malloc(size_t size)
{
	mutex_init();
	//TODO: MUTEX START
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
	//TODO: MUTEX END
	return ptr;
}
