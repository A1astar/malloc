/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:15:13 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/26 11:34:16 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static inline size_t *get_memblock_metadatas(void *ptr)
{
	return (size_t *)((char *)ptr - align16(sizeof(size_t)));
}

static void free_inside_arena(size_t arena_type, size_t *memblock_metadatas)
{
	(void)arena_type;
	(void)memblock_metadatas;
	//TODO
}

static void free_using_munmap(size_t *memblock_metadatas)
{
	t_mmap_lst *current_node = (t_mmap_lst *)((char *)memblock_metadatas - align16(sizeof(t_mmap_lst)));
	t_mmap_lst *prev_node = current_node->prev_mmap;
	t_mmap_lst *next_node = current_node->next_mmap;

	if(prev_node == current_node && next_node == current_node)
		g_alloc_arenas.mmap_lst = NULL;
	else
	{
		prev_node->next_mmap = next_node;
		next_node->prev_mmap = prev_node;
		g_alloc_arenas.mmap_lst = next_node;
	}
	munmap((void *)current_node, *memblock_metadatas);
}

void	ft_free(void *ptr)
{
	printf("free(%p)\n", ptr);
	if(!ptr)
		return ;
	size_t *memblock_metadatas = get_memblock_metadatas(ptr);
	size_t memblock_size = *memblock_metadatas & ~1;
	printf("memblock[%p] (%zu bytes)\n",memblock_metadatas, memblock_size);
	if(memblock_size <= TINY_MAX_SIZE)
		free_inside_arena(TINY_ARENA, memblock_metadatas);
	else if (memblock_size <= SMALL_MAX_SIZE)
		free_inside_arena(SMALL_ARENA, memblock_metadatas);
	else
		free_using_munmap(memblock_metadatas);
}
