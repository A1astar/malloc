/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:54:31 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/26 11:36:17 by alacroix         ###   ########.fr       */
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
		So we should also take in count size of memblocks metadatas and arena_lst struct
	*/
	return 100 * (align16(sizeof(size_t)) + align16(memblock_max_size)) + align16(sizeof(t_arena_lst));
}

static void create_memblock_boudary(t_arena_lst **arena)
{
	size_t *first_memblock = (size_t *)((char *)*arena + align16(sizeof(t_arena_lst)));
	*first_memblock = (*arena)->arena_size - align16(sizeof(t_arena_lst));
	(*arena)->max_available = *(size_t *)first_memblock;
}

static void *create_new_arena_list(t_arena_lst **first_arena, size_t arena_type)
{
	size_t memblock_max_size = get_memblock_max_size(arena_type);
	size_t arena_size = align_to_pagesize(get_arena_size(memblock_max_size));
	*first_arena = mmap(NULL, arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (*first_arena == MAP_FAILED)
		return NULL;

	(*first_arena)->next_arena = *first_arena;
	(*first_arena)->prev_arena = *first_arena;
	(*first_arena)->arena_type = arena_type;

	(*first_arena)->arena_size = arena_size;
	(*first_arena)->nb_alloc = 0;

	create_memblock_boudary(first_arena);

	return (void *)(*first_arena);
}

static void *append_new_arena_list(t_arena_lst **first_arena, size_t arena_type)
{
	size_t memblock_max_size = get_memblock_max_size(arena_type);
	size_t arena_size = align_to_pagesize(get_arena_size(memblock_max_size));
	t_arena_lst *new_arena = mmap(NULL, arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (new_arena == MAP_FAILED)
		return NULL;

	t_arena_lst *prev_arena = (*first_arena)->prev_arena;
	new_arena->next_arena = *first_arena;
	new_arena->prev_arena = prev_arena;
	(*first_arena)->prev_arena = new_arena;
	prev_arena->next_arena = new_arena;

	new_arena->arena_type = arena_type;
	new_arena->arena_size = arena_size;
	new_arena->nb_alloc = 0;

	create_memblock_boudary(&new_arena);

	return (void *)new_arena;
}

static void *add_new_arena_to_lst(t_arena_lst **arena_lst, size_t arena_type)
{
	if (!*arena_lst)
		return create_new_arena_list(arena_lst, arena_type);
	else
		return append_new_arena_list(arena_lst, arena_type);
}

static void *choose_from_existing_arena_lst(t_arena_lst **arena_lst, size_t requested_size)
{
	if (!*arena_lst)
		return NULL;
	t_arena_lst *current_arena = *arena_lst;
	while (true)
	{
		if (current_arena->max_available >= requested_size)
			return (void *)current_arena;
		current_arena = current_arena->next_arena;
		if (current_arena == *arena_lst)
			break;
	}
	return NULL;
}

static void create_new_mmap_lst(void **mapped_zone, t_mmap_lst **mmap_lst)
{
	*mmap_lst = *mapped_zone;
	(*mmap_lst)->next_mmap = *mmap_lst;
	(*mmap_lst)->prev_mmap = *mmap_lst;
}

static void append_to_mmap_lst(void **mapped_zone, t_mmap_lst **mmap_lst)
{
	t_mmap_lst *new_maping = (t_mmap_lst *)*mapped_zone;
	t_mmap_lst *last_mapped_zone = (*mmap_lst)->prev_mmap;
	new_maping->next_mmap = *mmap_lst;
	new_maping->prev_mmap = last_mapped_zone;
	last_mapped_zone->next_mmap = new_maping;
	(*mmap_lst)->prev_mmap = new_maping;
}

void add_mmap_to_list(void **mapped_zone, t_mmap_lst **mmap_lst)
{
	if (!*mmap_lst)
		create_new_mmap_lst(mapped_zone, mmap_lst);
	else
		append_to_mmap_lst(mapped_zone, mmap_lst);
}

void *choose_arena(t_arena_lst **arena_lst, size_t arena_type, size_t requested_size)
{
	void *choosen_arena = choose_from_existing_arena_lst(arena_lst, requested_size);
	if (choosen_arena)
		return choosen_arena;
	return add_new_arena_to_lst(arena_lst, arena_type);
}
