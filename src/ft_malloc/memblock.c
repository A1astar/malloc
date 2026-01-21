/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memblock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:50:45 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/21 18:15:43 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static inline void incr_alloc_count(void *arena)
{
	t_arena_header *header = (t_arena_header *)arena;
	header->nb_alloc++;
	printf("alloc count: %zu\n", header->nb_alloc);
}

static inline void *get_next_arena(void *arena)
{
	t_arena_header *header = (t_arena_header *)arena;
	return header->next_arena;
}

static inline void mark_as_allocated(void *memblock)
{
	*(size_t *)memblock = *(size_t *)memblock | 1;
}

static void split_memblock(void *memblock, size_t requested_size)
{
	//TODO: define a limit for splitting to minimize external fragmentation

	if(requested_size < *(size_t *)memblock)
		*(size_t *)((char *)memblock + requested_size) = *(size_t*)memblock - (requested_size & ~1);
	*(size_t *)memblock = requested_size;
}

static inline void *memblock_payload_offset(void *memblock)
{
	return (char *)memblock + align_to_16(sizeof(size_t));
}

static inline size_t *get_first_arena_memblock(void *current_arena)
{
	return (size_t *)((char *)current_arena + align_to_16(sizeof(t_arena_header)));
}

static inline void *get_end_of_arena(void *arena)
{
	t_arena_header *header = (t_arena_header *)arena;
	return (char *)arena + header->size;
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

static void *find_memblock(void *arena, size_t requested_size)
{
	size_t *current_block = get_first_arena_memblock(arena);
	size_t *end_of_arena = get_end_of_arena(arena);

	printf("current arena: [%p] -> [%p]\n", arena, end_of_arena);

	while(current_block < end_of_arena)
	{
		printf("	block -> [%p] [alloc_state:%zu] (%zu Bytes)\n", current_block, *current_block & 1, *(size_t *)current_block & ~1);
		if(is_free(current_block) && is_fitting(current_block, requested_size))
		{
			incr_alloc_count(arena);
			split_memblock(current_block, requested_size);
			mark_as_allocated(current_block);
			return memblock_payload_offset(current_block);
		}
		current_block = next_memblock(current_block);
	}
	return NULL;
}

void *get_memblock_from_arena(size_t arena_type, size_t requested_size)
{
	void *current_arena = g_alloc_arenas.arenas[arena_type];
	while(current_arena)
	{
		void *memblock = find_memblock(current_arena, requested_size);
		if(memblock)
			return memblock;
		current_arena = get_next_arena(current_arena);
	}
	//TODO: Create a new arena if no memblock found
	return NULL;
}

void *get_memblock_from_mmap(size_t requested_size)
{
	void *ptr = mmap(NULL, requested_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	*(size_t *)ptr = requested_size | 1;
	return (char *)ptr + align_to_16(sizeof(size_t));
}
