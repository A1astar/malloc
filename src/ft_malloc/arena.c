/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:54:31 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/22 12:58:11 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static inline size_t get_memblock_max_size(size_t arena_type)
{
	return arena_type == TINY_ARENA ? TINY_MAX_SIZE : SMALL_MAX_SIZE;
}

static inline size_t align_to_pagesize(size_t size)
{
	/*
		The arena size should be aligned to the system _SC_PAGEZISE value
		thus, it prevent a potential heap breakpoint between two pages boudaries
	*/
	size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
	return ((size + page_size - 1) / page_size) * page_size;
}

static inline size_t get_arena_size(size_t memblock_max_size)
{
	/*
		According to the subject, the arena should countain at least 100 * memblock_max_size
		So we should also take in count size of memblocks metadatas and arena_header struct
	*/
	return 100 * (align16(sizeof(size_t)) + align16(memblock_max_size)) + align16(sizeof(t_arena_header));
}

void create_arena(void **arena, size_t arena_type)
{
	/*
		In this malloc implementation, arenas are linked together by the t_arena_header struct
		This struct also indicates the nb of allocs inside the current arena and its total size
	*/
	size_t memblock_max_size = get_memblock_max_size(arena_type);
	size_t arena_size = align_to_pagesize(get_arena_size(memblock_max_size));
	*arena = mmap(NULL, arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (*arena == MAP_FAILED)
		*arena = NULL;
	else
	{
		t_arena_header *header = (t_arena_header *)*arena;
		header->next_arena = NULL;
		header->size = arena_size;
		header->nb_alloc = 0;
		size_t *first_memblock = (size_t *)((char *)*arena + align16(sizeof(t_arena_header)));
		*first_memblock = arena_size - align16(sizeof(t_arena_header));
		header->max_available = *(size_t *)first_memblock;
		printf("Creating a new arena [%p] (%zu Bytes)\n", *arena, header->size);
	}
}

static inline void *get_next_arena(void *arena)
{
	t_arena_header *header = (t_arena_header *)arena;
	return header->next_arena;
}

void *choose_arena(void *arena, size_t *requested_size)
{
	//! wip
	void *current_arena = arena;

	while(current_arena)
	{
		t_arena_header *header = (t_arena_header *)arena;
		if(header->max_available >= requested_size)
			return current_arena;
		current_arena = get_next_arena(current_arena);
	}
}

void init_arenas()
{
	if (!g_alloc_arenas.arenas[TINY_ARENA])
		create_arena(&g_alloc_arenas.arenas[TINY_ARENA], TINY_ARENA);
	if (!g_alloc_arenas.arenas[SMALL_ARENA])
		create_arena(&g_alloc_arenas.arenas[SMALL_ARENA], SMALL_ARENA);
}
