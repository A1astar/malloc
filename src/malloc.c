/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/19 12:26:02 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static inline size_t align(size_t size)
{
	return (((size) + (ALIGN_VAL - 1)) & ~ (ALIGN_VAL -1));
}

static inline size_t get_header_size()
{
	return align(sizeof(size_t));
}

static inline size_t get_raw_arena_size(size_t max_block_size)
{
	return 100 * ((get_header_size() * 2) + align(max_block_size));
}

static inline size_t align_arena(size_t pool_size)
{
	size_t page_size;
	page_size = sysconf(_SC_PAGESIZE);
	return ((pool_size + page_size - 1) / page_size) * page_size;
}

int create_alloc_arena(t_arena *alloc_arena, size_t max_block_size)
{
	alloc_arena->arena_size = align_arena(get_raw_arena_size(max_block_size));
	alloc_arena->arena_ptr = mmap(NULL, alloc_arena->arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if(alloc_arena->arena_ptr == MAP_FAILED)
		alloc_arena->arena_ptr = NULL;
}

void *get_arena_end(t_arena *alloc_arena)
{
	return (char *)alloc_arena->arena_ptr + alloc_arena->arena_size;
}

void *expend_arena(t_arena *alloc_arena, size_t request_size)
{
	size_t map_size = align_arena(request_size);
	void *current_end = alloc_arena->arena_ptr + alloc_arena->arena_size;
	void *block = mmap(current_end, map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_FIXED_NOREPLACE, -1, 0);
	if(block == MAP_FAILED)
		return NULL;
	alloc_arena->arena_size += request_size;
	return block;
}

void *find_block(t_arena *alloc_arena, size_t requested_size)
{
	size_t *current_block = alloc_arena->arena_ptr;
	while (current_block < get_arena_end(alloc_arena))
	{
		if(!(*current_block & 1) && *current_block >= requested_size)
			return current_block;
		current_block = (char *)current_block + (*current_block & ~1);
	}
	return NULL;
}

void *get_memblock(t_arena *alloc_arena, size_t request_size)
{
	if(!alloc_arena->arena_ptr)
		return NULL;
	size_t *block = find_block(alloc_arena, request_size);
	if(block)
		*block = *block | 1;
	else
	{
		block = expend_arena(alloc_arena, request_size);
		if(!block)
			return NULL;
		*block = request_size | 1;
	}
	return (char *)block + get_header_size();
}

void *get_mapped_area(size_t requested_size)
{
	void *ptr = mmap(NULL, requested_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	*(size_t *)ptr = requested_size | 1;
	return (char *)ptr + get_header_size();
}

void *malloc(size_t size)
{
	if(!size)
		size++;
	size_t block_size = align(size + get_header_size());

	if(block_size <= TINY_MAX_SIZE)
	{
		if(!g_alloc_arenas.tiny_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.tiny_alloc_arena, TINY_MAX_SIZE);
		return get_memblock(&g_alloc_arenas.tiny_alloc_arena, block_size);
	}
	else if(block_size <= SMALL_MAX_SIZE)
	{
		if(!g_alloc_arenas.small_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.small_alloc_arena, SMALL_MAX_SIZE);
		return get_memblock(&g_alloc_arenas.small_alloc_arena, block_size);
	}
	else
		return get_mapped_area(block_size);
}
