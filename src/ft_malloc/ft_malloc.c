/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/21 17:39:46 by alacroix         ###   ########.fr       */
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
	return align_to_16(sizeof(size_t)) + align_to_16(size > 0 ? size : 1);
}

void *ft_malloc(size_t size)
{
	init_arenas();
	void *ptr = NULL;
	size_t aligned_size = align_requested_size(size);
	printf("Aligned size: [%zu] -> [%zu]\n", size, aligned_size);
	if (aligned_size <= TINY_MAX_SIZE)
	{
		printf("Searching inside tiny arena\n");
		ptr = get_memblock_from_arena(TINY_ARENA, aligned_size);
	}
	else if (aligned_size <= SMALL_MAX_SIZE)
	{
		printf("Searching inside small arena\n");
		ptr = get_memblock_from_arena(SMALL_ARENA, aligned_size);
	}
	else
	{
		printf("using mmap\n");
		ptr = get_memblock_from_mmap(aligned_size);
	}
	return ptr;
}
