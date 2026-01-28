/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_analyser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:13:35 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/28 16:31:52 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static bool is_inside_arena_lst(void *ptr, t_arena_lst *first_node)
{
    t_arena_lst *current_arena = first_node;
    if(!current_arena)
        return false;
    while (true)
    {
		size_t *end_of_arena = (size_t *)((char *)current_arena + current_arena->arena_size);
        if((void *)current_arena < ptr && ptr < (void *)end_of_arena)
            return true;
        current_arena = current_arena->next_arena;
        if(current_arena == first_node)
            return false;
    }
}

static bool is_inside_mmap_lst(void *ptr, t_mmap_lst *first_node)
{
    t_mmap_lst *current_arena = first_node;
    if(!current_arena)
        return false;
    while (true)
    {
        size_t *arena_metadata = (size_t *)((char *)current_arena + align16(sizeof(t_mmap_lst)));
        size_t arena_size = *arena_metadata & ~1;
        size_t *end_of_arena = (size_t *)((char *)current_arena + arena_size);
        if((void *)current_arena < ptr && ptr < (void *)end_of_arena)
            return true;
        current_arena = current_arena->next_mmap;
        if(current_arena == first_node)
            return false;
    }
}

bool is_from_current_allocator(void *ptr)
{
    if (!is_inside_arena_lst(ptr, g_alloc_arenas.arenas_lst[TINY_ARENA])
    && !is_inside_arena_lst(ptr, g_alloc_arenas.arenas_lst[TINY_ARENA])
    && !is_inside_mmap_lst(ptr, g_alloc_arenas.mmap_lst))
        return false;
    return true;
}
