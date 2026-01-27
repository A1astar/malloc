/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:14:01 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 15:46:29 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void print_arena(t_arena_lst *arena, size_t arena_size)
{
    size_t *current_block = (size_t *)((char *)arena + align16(sizeof(t_arena_lst)));
    size_t *end_of_arena = (size_t *)((char *)arena + arena_size);

    ft_printf(BOLD "    Arena [%p] -> [%p] (%z bytes)\n" RESET, arena, end_of_arena, arena->arena_size);
    while (current_block < end_of_arena)
    {
        size_t *next_block = (size_t *)((char *)current_block + (*current_block & ~1));
        if ((*current_block & 1))
            ft_printf("    [%p] - [%p] : %z bytes\n", current_block, next_block, *current_block & ~1);
        current_block = next_block;
    }
}

void print_arena_lst(t_arena_lst *first_node, char *name)
{
    ft_printf(BOLD "%s:\n" RESET, name);
    t_arena_lst *current_node = first_node;
    if (!current_node)
    {
        ft_printf(ITALIC"    Empty\n"RESET);
        return;
    }
    while (true)
    {
        print_arena(current_node, current_node->arena_size);
        current_node = current_node->next_arena;
        if (current_node == first_node)
            break;
    }
}

void print_mmap_lst(t_mmap_lst *first_node)
{
    ft_printf(BOLD "LARGE:\n" RESET);
    t_mmap_lst *current_node = first_node;
    if (!current_node)
    {
        printf(ITALIC"    Empty\n"RESET);
        return;
    }
    while (true)
    {
        size_t *metadata = (size_t *)((char *)current_node + align16(sizeof(t_mmap_lst)));
        ft_printf("   [%p] - [%p] : %z bytes\n", current_node, ((char *)current_node + (*metadata & ~1)), *metadata & ~1);
        current_node = current_node->next_mmap;
        if (current_node == first_node)
            break;
    }
}

void ft_show_alloc_mem(void)
{
    pthread_mutex_lock(&malloc_mutex);
    print_arena_lst(g_alloc_arenas.arenas_lst[TINY_ARENA], "TINY");
    print_arena_lst(g_alloc_arenas.arenas_lst[SMALL_ARENA], "SMALL");
    print_mmap_lst(g_alloc_arenas.mmap_lst);
    ft_printf(BOLD "Total: %z bytes\n" RESET, g_alloc_arenas.total_alloc_bytes);
	pthread_mutex_unlock(&malloc_mutex);
}
