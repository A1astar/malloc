/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/20 15:05:30 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/malloc.h"

void *malloc(size_t size)
{
	//! --- FOR DEBUG PURPOSE ONLY ---1
	//len = snprintf(buffer, sizeof(buffer), "Entering Malloc wrapper\n");
	//write(STDOUT_FILENO, buffer, len);

	static void *(*original_malloc)(size_t size) = NULL;
	if(!original_malloc)
		original_malloc = dlsym(RTLD_NEXT, "malloc");
	(void)original_malloc;

	//! --- FOR DEBUG PURPOSE ONLY ---
	//len = snprintf(buffer, sizeof(buffer), "Requested size before align: %zu\n",size);
	//write(STDOUT_FILENO, buffer, len);

	if(!size)
		size++;
	size_t chunk_size = align_to_16(align_to_16(sizeof(size_t)) + size);

	//! --- FOR DEBUG PURPOSE ONLY ---
	//len = snprintf(buffer, sizeof(buffer), "Requested size after align: %zu\n" ,chunk_size);
	//write(STDOUT_FILENO, buffer, len);

	if(chunk_size <= TINY_MAX_SIZE)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
	//	len = snprintf(buffer, sizeof(buffer), "chunk size <= TINY_MAX_SIZE\n");
	//	write(STDOUT_FILENO, buffer, len);

		if(!g_alloc_arenas.tiny_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.tiny_alloc_arena, TINY_MAX_SIZE);
		return get_arena_chunk(&g_alloc_arenas.tiny_alloc_arena, chunk_size);
	}
	else if(chunk_size <= SMALL_MAX_SIZE)
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
	//	len = snprintf(buffer, sizeof(buffer), "chunk size <= SMALL_MAX_SIZE\n");
	//	write(STDOUT_FILENO, buffer, len);

		if(!g_alloc_arenas.small_alloc_arena.arena_ptr)
			create_alloc_arena(&g_alloc_arenas.small_alloc_arena, SMALL_MAX_SIZE);
		return get_arena_chunk(&g_alloc_arenas.small_alloc_arena, chunk_size);
	}
	else
	{
		//! --- FOR DEBUG PURPOSE ONLY ---
	//	len = snprintf(buffer, sizeof(buffer), "direct mmap call\n");
	//	write(STDOUT_FILENO, buffer, len);

		return get_mapped_chunk(chunk_size);
	}
}
