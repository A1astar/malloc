/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:54:31 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/20 13:05:18 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

static inline void *get_arena_end(t_arena *alloc_arena)
{
	return (char *)alloc_arena->arena_ptr + alloc_arena->arena_size;
}

static void split_chunk(void *chunk, size_t requested_size)
{
    //! --- FOR DEBUG PURPOSE ONLY ---
    ft_printf("splitting chunk[%p] (%d)\n", chunk, (int)*(size_t *)chunk);

	if(requested_size < *(size_t *)chunk)
		*(size_t *)((char *)chunk + requested_size) = *(size_t*)chunk - (requested_size & ~1);

	*(size_t *)chunk = requested_size | 1;

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("current chunk[%p] (%d)\n", chunk, (int)*(size_t *)chunk & ~1);
        ft_printf("next chunk[%p] (%d)\n", ((char *)chunk + requested_size), (int)*(size_t *)((char *)chunk + requested_size));
}

static void *find_chunk(t_arena *alloc_arena, size_t requested_size)
{
	size_t *current_chunk = alloc_arena->arena_ptr;
	size_t *end_of_arena = get_arena_end(alloc_arena);

	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Finding chunk in Arena: [%p] -> [%p]\n", current_chunk, end_of_arena);

	while (current_chunk < end_of_arena)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
			ft_printf(" -chunk[%p] (%d)\n", current_chunk, (int)*(size_t *)current_chunk);

		if(!(*current_chunk & 1L) && *current_chunk >= requested_size)
			return current_chunk;
		current_chunk = (size_t *)((char *)current_chunk + (*current_chunk & ~1));
	}
	return NULL;
}

void *get_arena_chunk(t_arena *alloc_arena, size_t requested_size)
{
	//! --- FOR DEBUG PURPOSE ONLY ---
		ft_printf("Searching a chunk of size: %d\n", (int)requested_size);

	if(!alloc_arena->arena_ptr)
		return NULL;
	void *chunk = find_chunk(alloc_arena, requested_size);
	if(chunk)
		split_chunk(chunk, requested_size);
	else
	{
		chunk = expand_alloc_arena(alloc_arena, requested_size);
		if(!chunk)
			return NULL;
		*(size_t *)chunk = requested_size | 1;
	}
	return (char *)chunk + align_to_16(sizeof(size_t));
}

void *get_mapped_chunk(size_t requested_size)
{
	void *ptr = mmap(NULL, requested_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	*(size_t *)ptr = requested_size | 1;
	return (char *)ptr + align_to_16(sizeof(size_t));
}
