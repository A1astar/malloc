/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem_ex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 12:24:07 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/28 12:33:43 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void print_16_bytes(void *memory)
{
    ft_printf("[%p]: ", (char *)memory);
    char *string_portion = (char *)memory;
    for (size_t i = 0; i < 16; i++)
    {
        if(string_portion[i] == '\0')
            ft_printf("00");
        else
            ft_printf("%x", string_portion[i]);
        if(i % 1 == 0)
            ft_printf(" ");
    }
    ft_printf("\n");
}

static void hexdump_mmap(void *memory, size_t size)
{
    ft_printf("Arena [%p] -> [%p]:\n", memory, (char *)memory + size);
    for(size_t i = 0; i < size; i +=16)
        print_16_bytes((char *)memory + i);
    ft_printf("\n");
}

static void hexdump_arena_lst(t_arena_lst *first_node, char *type)
{
    ft_printf(BOLD "%s:\n"RESET, type);
    t_arena_lst *current_node = first_node;
    if (!current_node)
    {
        ft_printf(ITALIC "    Empty\n" RESET);
        return;
    }
    while(true)
    {
        hexdump_mmap((void *)current_node, current_node->arena_size);
        current_node = current_node->next_arena;
        if(current_node == first_node)
            break;
    }
}

void show_alloc_mem_ex(void)
{
    pthread_mutex_lock(&malloc_mutex);
    hexdump_arena_lst(g_alloc_arenas.arenas_lst[TINY_ARENA], "TINY");
    hexdump_arena_lst(g_alloc_arenas.arenas_lst[TINY_ARENA], "SMALL");
    //hexdump_mmap_lst();
    pthread_mutex_unlock(&malloc_mutex);
}
