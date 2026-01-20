/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/20 13:03:29 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void *malloc(size_t size)
{
	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Entering Malloc wrapper\n");

	static void *(*original_malloc)(size_t size) = NULL;
	if(!original_malloc)
		original_malloc = dlsym(RTLD_NEXT, "malloc");
	(void)original_malloc;

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Requested size = %d\n", (int)size);

	if(!size)
		size++;
	size_t block_size = align_to_16(align_to_16(sizeof(size_t)) + size);

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("aligned size = %d\n", (int)block_size);

	if(block_size <= TINY_MAX_SIZE)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			ft_printf("block size <= TINY_MAX_SIZE\n");

		if(!g_alloc_arenas.tiny_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.tiny_alloc_arena, TINY_MAX_SIZE);
		return get_arena_chunk(&g_alloc_arenas.tiny_alloc_arena, block_size);
	}
	else if(block_size <= SMALL_MAX_SIZE)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			ft_printf("block size <= SMALL_MAX_SIZE\n");

		if(!g_alloc_arenas.small_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.small_alloc_arena, SMALL_MAX_SIZE);
		return get_arena_chunk(&g_alloc_arenas.small_alloc_arena, block_size);
	}
	else
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			ft_printf("Direct call to mmap\n");

		return get_mapped_chunk(block_size);
	}
}
