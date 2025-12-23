/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:08:12 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/23 16:20:07 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*Returns rounded up block_size to the closest multipe of ALIGNEMENT_VALUE*/
size_t align_block(size_t block_size)
{
	return block_size + (ALIGNEMENT_VALUE - 1) & ~(ALIGNEMENT_VALUE - 1);
}

/*Returns rounded up pool_size to the closest multipe of sysconf(_SC_PAGESIZE)*/
size_t align_pool(size_t pool_size)
{
	size_t page_size = sysconf(_SC_PAGESIZE);

	/*Prefer the non-bitwise version for page_size may not be a multiple of 2*/
	return ((pool_size + page_size - 1) / page_size) * page_size;
}

/*Returns a pointer of requested size block (<= max_size) inside a mem_pool*/
void *allocator(void *mem_pool, size_t max_size, size_t requested_size)
{
	if(!mem_pool)
	{
		size_t raw_size = 100 * (sizeof(t_metadata) + align_block(max_size));
		size_t pool_size = align_pool(raw_size);

		mem_pool = mmap(NULL, pool_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANON, -1, NULL);

		if(mem_pool == MAP_FAILED)
			return NULL;
	}
	else
	{}
}

void *large_allocator(size_t size)
{
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
				-1, NULL);

	if(ptr == MAP_FAILED)
		return NULL;

	return ptr;
}

/*Allocates size bytes of memory and returns a pointer to the allocated memory*/
void	*malloc(size_t size)
{
	void *ptr = NULL;

	if(size <= TINY_MAX_SIZE)
		ptr = allocator(&g_alloc_pools.tiny_mem_pool, TINY_MAX_SIZE, size);
	else if(size > TINY_MAX_SIZE && size <= SMALL_MAX_SIZE)
		ptr = allocator(&g_alloc_pools.small_mem_pool, SMALL_MAX_SIZE, size);
	else
		ptr = large_allocator(size);
	return ptr;
}
