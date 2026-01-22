/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:54:31 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/22 12:15:36 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static inline size_t get_memblock_max_size(size_t arena_type)
{
	return arena_type == TINY_ARENA ? TINY_MAX_SIZE : SMALL_MAX_SIZE;
}

static inline size_t align_to_pagesize(size_t size)
{
	size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
	return ((size + page_size - 1) / page_size) * page_size;
}

static inline size_t get_arena_size(size_t memblock_max_size)
{
	return 100 * (align16(sizeof(size_t)) + align16(memblock_max_size)) + align16(sizeof(t_arena_header));
}

void create_arena(void **arena, size_t arena_type)
{
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
		printf("Creating a new arena [%p] (%zu Bytes)\n", *arena, header->size);
	}
}

void init_arenas()
{
	if (!g_alloc_arenas.arenas[TINY_ARENA])
		create_arena(&g_alloc_arenas.arenas[TINY_ARENA], TINY_ARENA);
	if (!g_alloc_arenas.arenas[SMALL_ARENA])
		create_arena(&g_alloc_arenas.arenas[SMALL_ARENA], SMALL_ARENA);
}
