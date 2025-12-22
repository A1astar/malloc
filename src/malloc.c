/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/22 16:22:29 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void *tiny_allocator(size_t size)
{
	//TODO: manage tiny alloc with g_alloc_arena
}

static void *small_allocator(size_t size)
{
	//TODO: manage small alloc with g_alloc_arena
}

static void *large_allocator(size_t size)
{
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
				-1, NULL);

	if(ptr == MAP_FAILED)
		return NULL;

	return ptr;
}

void	*malloc(size_t size)
{
	if(size <= TINY_MAX_SIZE)
		return tiny_allocator(size);
	else if(size > TINY_MAX_SIZE && size <= SMALL_MAX_SIZE)
		return small_allocator(size);
	else
		return large_allocator(size);
}
