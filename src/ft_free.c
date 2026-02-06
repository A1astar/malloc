/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:15:13 by alacroix          #+#    #+#             */
/*   Updated: 2026/02/06 15:19:22 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static inline size_t *get_memblock_metadata(void *ptr)
{
	return (size_t *)((char *)ptr - align16(sizeof(size_t)));
}

static inline bool is_free(size_t *current_memblock)
{
	return !(*current_memblock & 1);
}

static inline void mark_memblock_as_free(size_t *memblock_metadata, t_arena_lst **arena)
{
	*memblock_metadata = *memblock_metadata & ~1;
	(*arena)->nb_alloc--;
}

static inline void merge_memblock(size_t *current_memblock, size_t *next_memblock)
{
	*current_memblock = *current_memblock + *next_memblock;
}

static void coalese_memblocks(t_arena_lst *arena, size_t *first_memblock, size_t *end_of_arena)
{
	size_t *current_memblock = first_memblock;
	while (current_memblock < end_of_arena)
	{
		size_t *next_memblock = (size_t *)((char *)current_memblock + (*current_memblock & ~1));
		while (next_memblock < end_of_arena && (is_free(current_memblock) && is_free(next_memblock)))
		{
			merge_memblock(current_memblock, next_memblock);
			if (*current_memblock > arena->max_available)
				arena->max_available = *current_memblock;
			next_memblock = (size_t *)((char *)current_memblock + (*current_memblock & ~1));
		}
		current_memblock = (size_t *)((char *)current_memblock + (*current_memblock & ~1));
	}
}

static void remove_arena(t_arena_lst *arena)
{
	t_arena_lst *current_node = arena;
	t_arena_lst *prev_node = current_node->prev_arena;
	t_arena_lst *next_node = current_node->next_arena;

	if (prev_node == current_node && next_node == current_node)
		g_alloc_arenas.arenas_lst[arena->arena_type] = NULL;
	else
	{
		prev_node->next_arena = next_node;
		next_node->prev_arena = prev_node;
		g_alloc_arenas.arenas_lst[arena->arena_type] = next_node;
	}
	munmap((void *)current_node, current_node->arena_size);
}

static t_arena_lst *find_arena(size_t arena_type, size_t *memblock_metadata)
{
	t_arena_lst *first_arena = g_alloc_arenas.arenas_lst[arena_type];
	t_arena_lst *current_arena = g_alloc_arenas.arenas_lst[arena_type];

	while (true)
	{
		size_t *end_of_arena = (size_t *)((char *)current_arena + current_arena->arena_size);
		if ((void *)current_arena < (void *)memblock_metadata && (void *)memblock_metadata < (void *)end_of_arena)
			return current_arena;
		current_arena = current_arena->next_arena;
		if (current_arena == first_arena)
			break;
	}
	return NULL;
}

static void free_inside_arena(size_t arena_type, size_t *memblock_metadata)
{
	t_arena_lst *arena = find_arena(arena_type, memblock_metadata);
	if (!arena)
		return;
	size_t *first_memblock = (size_t *)((char *)arena + align16(sizeof(t_arena_lst)));
	size_t *end_of_arena = (size_t *)((char *)arena + arena->arena_size);
	size_t *current_memblock = first_memblock;
	while (current_memblock != memblock_metadata && current_memblock < end_of_arena)
		current_memblock = (size_t *)((char *)current_memblock + (*current_memblock & ~1));
	if (current_memblock == end_of_arena)
		return;
	mark_memblock_as_free(memblock_metadata, &arena);
	g_alloc_arenas.total_alloc_bytes -= *(size_t *)memblock_metadata & ~1;
	if (arena->nb_alloc == 0  && (arena->prev_arena != arena))
		remove_arena(arena);
	else
		coalese_memblocks(arena, first_memblock, end_of_arena);
}

static void free_using_munmap(size_t *memblock_metadata)
{
	t_mmap_lst *current_node = (t_mmap_lst *)((char *)memblock_metadata - align16(sizeof(t_mmap_lst)));
	t_mmap_lst *prev_node = current_node->prev_mmap;
	t_mmap_lst *next_node = current_node->next_mmap;
	size_t memblock_size = *memblock_metadata & ~1;

	if (!current_node || (!prev_node && !next_node))
		return;

	if (prev_node == current_node && next_node == current_node)
		g_alloc_arenas.mmap_lst = NULL;
	else
	{
		prev_node->next_mmap = next_node;
		next_node->prev_mmap = prev_node;
		g_alloc_arenas.mmap_lst = next_node;
	}
	munmap((void *)current_node, memblock_size);
	g_alloc_arenas.total_alloc_bytes -= memblock_size;
}

void free(void *ptr)
{
	if (!ptr || !is_from_current_allocator(ptr))
		return;
	pthread_mutex_lock(&malloc_mutex);
	size_t *memblock_metadata = get_memblock_metadata(ptr);
	size_t memblock_size = *memblock_metadata & ~1;

	if (memblock_size <= TINY_MAX_SIZE)
		free_inside_arena(TINY_ARENA, memblock_metadata);
	else if (memblock_size <= SMALL_MAX_SIZE)
		free_inside_arena(SMALL_ARENA, memblock_metadata);
	else
		free_using_munmap(memblock_metadata);
	pthread_mutex_unlock(&malloc_mutex);
}
