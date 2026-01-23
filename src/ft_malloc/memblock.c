/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memblock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:50:45 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/23 12:31:57 by alacroix         ###   ########.fr       */
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

static inline size_t *get_first_arena_memblock(void *current_arena)
{
	return (size_t *)((char *)current_arena + align16(sizeof(t_arena_lst)));
}

static inline void *get_end_of_arena(void *arena)
{
	t_arena_lst *current_arena = (t_arena_lst *)arena;
	return (char *)arena + current_arena->arena_size;
}

static inline size_t *next_memblock(size_t *current_memblock)
{
	return (size_t *)((char *)current_memblock + (*current_memblock & ~1));
}

static inline bool is_free(size_t *current_memblock)
{
	return !(*current_memblock & 1);
}

static inline bool is_fitting(size_t *current_memblock, size_t requested_size)
{
	return (*current_memblock & ~1) >= requested_size;
}

static void incr_alloc_count(void *arena)
{
	t_arena_lst *current_arena = (t_arena_lst *)arena;
	current_arena->nb_alloc++;
	//printf("alloc count: %zu\n", current_arena->nb_alloc);
}

static void split_memblock(void *arena, void *memblock, size_t requested_size)
{
	// TODO: define a limit for splitting to minimize external fragmentation
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
	size_t *current_block = get_first_arena_memblock(arena);
	size_t *end_of_arena = get_end_of_arena(arena);

	//printf("current arena: [%p] -> [%p]\n", arena, end_of_arena);

	while (current_block < end_of_arena)
	{
	//	printf("	block -> [%p] [alloc_state:%zu] (%zu Bytes)\n", current_block, *current_block & 1, *(size_t *)current_block & ~1);
		if (is_free(current_block) && is_fitting(current_block, requested_size))
		{
			incr_alloc_count(arena);
			split_memblock(arena, current_block, requested_size);
			mark_as_allocated(current_block);
			return memblock_payload_offset(current_block);
		}
		current_block = next_memblock(current_block);
	}
	return NULL;
}

void *get_memblock_from_arena(size_t arena_type, size_t requested_size)
{
	void *arena = choose_arena(&g_alloc_arenas.arenas[arena_type], arena_type, requested_size);
	if (!arena)
		return NULL;
	void *memblock = find_memblock(arena, requested_size);
	if (!memblock)
		return NULL;
	return memblock;
}

void *get_memblock_from_mmap(size_t requested_size)
{
	void *ptr = mmap(NULL, requested_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	*(size_t *)ptr = requested_size | 1;
	return (char *)ptr + align16(sizeof(size_t));
}
