/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/19 18:09:22 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

//! --- FOR DEBUG PURPOSE ONLY ---
char wbuffer[1024];
int len = 0;

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

void create_alloc_arena(t_arena *alloc_arena, size_t max_block_size)
{
	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "Creating new alloc_arena with 100 * %zu of size\n", max_block_size);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	alloc_arena->arena_size = align_arena(get_raw_arena_size(max_block_size));

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "Aligned arene size calculated: %zu\n", alloc_arena->arena_size);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	alloc_arena->arena_ptr = mmap(NULL, alloc_arena->arena_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "Arena ptr: %p\n", alloc_arena->arena_ptr);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	*(size_t *)alloc_arena->arena_ptr = alloc_arena->arena_size;

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "first block size: %zu\n", *(size_t *)alloc_arena->arena_ptr);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------


	if(alloc_arena->arena_ptr == MAP_FAILED)
		alloc_arena->arena_ptr = NULL;
}

void *get_arena_end(t_arena *alloc_arena)
{
	return (char *)alloc_arena->arena_ptr + alloc_arena->arena_size;
}

void *expand_arena(t_arena *alloc_arena, size_t request_size)
{
	size_t map_size = align_arena(request_size);
	void *current_end = alloc_arena->arena_ptr + alloc_arena->arena_size;
	void *block = mmap(current_end, map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_FIXED_NOREPLACE, -1, 0);
	if(block == MAP_FAILED)
		return NULL;
	alloc_arena->arena_size += request_size;
	return block;
}

void split_block(void *block, size_t requested_size)
{
	if(requested_size < *(size_t *)block)
	{
		*(size_t *)((char *)block + requested_size) = *(size_t*)block - (requested_size & ~1);

		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "splitting block: %p\n", block);
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------

		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "original block size: %zu\n", *(size_t *)block & ~1);
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------

		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "next block size: %zu\n", *(size_t *)((char *)block + requested_size));
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------
	}

	*(size_t *)block = requested_size | 1;

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "current block size: %zu\n", *(size_t *)block & ~1);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------
}
void *find_block(t_arena *alloc_arena, size_t requested_size)
{
	size_t *current_block = alloc_arena->arena_ptr;

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "current_block ptr: %p\n", current_block);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	size_t *end_of_arena = get_arena_end(alloc_arena);

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "end_of_arena ptr: %p\n", end_of_arena);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	while (current_block < end_of_arena)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "checking block ptr: %p\n", current_block);
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------

		if(!(*current_block & 1L) && *current_block >= requested_size)
			return current_block;
		current_block = (size_t *)((char *)current_block + (*current_block & ~1));
	}
	return NULL;
}

void *get_memblock(t_arena *alloc_arena, size_t request_size)
{
	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "Searching a block of size: %zu\n", request_size);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	if(!alloc_arena->arena_ptr)
		return NULL;
	void *block = find_block(alloc_arena, request_size);
	if(block)
		split_block(block, request_size);
	else
	{
		block = expand_arena(alloc_arena, request_size);
		if(!block)
			return NULL;
		*(size_t *)block = request_size | 1;
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
	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "Entering Malloc wrapper\n");
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	static void *(*original_malloc)(size_t size) = NULL;
	if(!original_malloc)
		original_malloc = dlsym(RTLD_NEXT, "malloc");
	(void)original_malloc;

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "Requested size = %zu\n", size);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	if(!size)
		size++;
	size_t block_size = align(size + get_header_size());

	//! --- FOR DEBUG PURPOSE ONLY ---
		len = snprintf(wbuffer, sizeof(wbuffer), "aligned size = %zu\n", block_size);
		write(STDOUT_FILENO, wbuffer, len);
	//! ------------------------------

	if(block_size <= TINY_MAX_SIZE)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "block size <= TINY_MAX_SIZE\n");
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------

		if(!g_alloc_arenas.tiny_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.tiny_alloc_arena, TINY_MAX_SIZE);
		return get_memblock(&g_alloc_arenas.tiny_alloc_arena, block_size);
	}
	else if(block_size <= SMALL_MAX_SIZE)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "block size <= SMALL_MAX_SIZE\n");
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------

		if(!g_alloc_arenas.small_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.small_alloc_arena, SMALL_MAX_SIZE);
		return get_memblock(&g_alloc_arenas.small_alloc_arena, block_size);
	}
	else
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			len = snprintf(wbuffer, sizeof(wbuffer), "Direct call to mmap\n");
			write(STDOUT_FILENO, wbuffer, len);
		//! ------------------------------

		return get_mapped_area(block_size);
	}
}
