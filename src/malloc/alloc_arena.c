/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:50:45 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/20 13:02:09 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static inline size_t get_arena_size(size_t chunk_max_size)
{
	return 100 * (align_to_16(sizeof(size_t)) + align_to_16(chunk_max_size));
}

void *expand_alloc_arena(t_arena *alloc_arena, size_t requested_size)
{
	size_t map_size = align_to_pagesize(requested_size);
	void *current_end = alloc_arena->arena_ptr + alloc_arena->arena_size;
	void *block = mmap(current_end, map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_FIXED_NOREPLACE, -1, 0);
	if(block == MAP_FAILED)
		return NULL;
	alloc_arena->arena_size += requested_size;
	return block;
}

void create_alloc_arena(t_arena *alloc_arena, size_t chunk_max_size)
{
	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Creating new alloc_arena with 100 * %d of size\n", (int)chunk_max_size);

	alloc_arena->arena_size = align_to_pagesize(get_arena_size(chunk_max_size));

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Aligned arene size calculated: %d\n", (int)alloc_arena->arena_size);

	alloc_arena->arena_ptr = mmap(NULL, alloc_arena->arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Arena ptr: %p\n", alloc_arena->arena_ptr);

	*(size_t *)alloc_arena->arena_ptr = alloc_arena->arena_size;

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("first block size: %d\n", (int)*(size_t *)alloc_arena->arena_ptr);

	if(alloc_arena->arena_ptr == MAP_FAILED)
		alloc_arena->arena_ptr = NULL;
}
