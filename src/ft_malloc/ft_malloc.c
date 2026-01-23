/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/23 12:32:04 by alacroix         ###   ########.fr       */
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
	return align16(sizeof(size_t)) + align16(size > 0 ? size : 1);
}

void *ft_malloc(size_t size)
{
	void *ptr = NULL;
	size_t aligned_size = align_requested_size(size);
	printf("malloc([%zu] -> [%zu])\n", size, aligned_size);

	if (aligned_size <= TINY_MAX_SIZE)
	{
		printf("Searching inside tiny arena lst\n");
		ptr = get_memblock_from_arena(TINY_ARENA, aligned_size);
	}
	else if (aligned_size <= SMALL_MAX_SIZE)
	{
		printf("Searching inside small arena lst\n");
		ptr = get_memblock_from_arena(SMALL_ARENA, aligned_size);
	}
	else
	{
		printf("using mmap\n");
		ptr = get_memblock_from_mmap(aligned_size);
	}
	printf("\n");
	return ptr;
}
