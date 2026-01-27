/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memblock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:50:45 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 12:01:30 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static inline void mark_as_allocated(void *memblock)
{
	*(size_t *)memblock = *(size_t *)memblock | 1;
}

static inline void *memblock_payload_offset(void *memblock)
{
	return (char *)memblock + align16(sizeof(size_t));
}

static inline bool is_free(size_t *current_memblock)
{
	return !(*current_memblock & 1);
}

static inline bool is_fitting(size_t *current_memblock, size_t requested_size)
{
	return (*current_memblock & ~1) >= requested_size;
}

static void split_memblock(void *arena, void *memblock, size_t requested_size)
{
	size_t *next_memblock = (size_t *)((char *)memblock + requested_size);

	if (requested_size < *(size_t *)memblock)
		*next_memblock = *(size_t *)memblock - (requested_size & ~1);
	*(size_t *)memblock = requested_size | 1;

	t_arena_lst *current_arena = (t_arena_lst *)arena;
	current_arena->max_available -= (requested_size & ~1);
	current_arena->nb_alloc++;
}

static void *find_memblock(void *arena, size_t requested_size)
{
	t_arena_lst *current_arena = (t_arena_lst *)arena;
	size_t *current_block = (size_t *)((char *)current_arena + align16(sizeof(t_arena_lst)));
	size_t *end_of_arena = (size_t *)((char *)arena + current_arena->arena_size);

	while (current_block < end_of_arena)
	{
		if (is_free(current_block) && is_fitting(current_block, requested_size))
		{
			split_memblock(arena, current_block, requested_size);
			mark_as_allocated(current_block);
			return memblock_payload_offset(current_block);
		}
		current_block = (size_t *)((char *)current_block + (*current_block & ~1));
	}
	return NULL;
}

void *get_memblock_from_arena(size_t arena_type, size_t requested_size)
{
	void *arena = choose_arena(&g_alloc_arenas.arenas_lst[arena_type], arena_type, requested_size);
	if (!arena)
		return NULL;
	void *memblock = find_memblock(arena, requested_size);
	if (!memblock)
		return NULL;
	return memblock;
}

void *get_memblock_from_mmap(size_t requested_size)
{
	size_t mapping_size = align16(sizeof(t_mmap_lst)) + align16(sizeof(size_t)) + requested_size;
	void *ptr = mmap(NULL, mapping_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	void *metadata = (char *)ptr + align16(sizeof(t_mmap_lst));
	*(size_t *)metadata = mapping_size | 1;
	add_mmap_to_list(&ptr, &g_alloc_arenas.mmap_lst);
	return memblock_payload_offset(metadata);
}
