/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem_ex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 12:24:07 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/28 14:31:08 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void format_hex_output(unsigned char c)
{
    if (c == '\0')
        ft_printf("00");
    else if (c < 0x10)
    {
        ft_printf("0");
        ft_printf("%x", c);
    }
    else
        ft_printf("%x", c);
}

static void format_char_output(unsigned char c)
{
    if(c >= ' ' && c <= '~')
        ft_printf("%c", c);
    else
        ft_printf(".");
}

static void print_16_bytes(void *memory, void *end_of_memory)
{
    ft_printf("        [%p]: ", (unsigned char *)memory);
    unsigned char *string_portion = (unsigned char *)memory;
    for (size_t i = 0; i < 16; i++)
    {
        if ((void *)((unsigned char *)memory + i) >= end_of_memory)
            break;
        format_hex_output(string_portion[i]);
        if (i % 1 == 0)
            ft_printf(" ");
    }
    ft_printf(" | ");
    for (size_t i = 0; i < 16; i++)
    {
        if ((void *)((unsigned char *)memory + i) >= end_of_memory)
            break;
        format_char_output(string_portion[i]);
    }
    ft_printf("\n");
}

static void hexdump_mmap(void *memory, size_t size)
{
    ft_printf("    Arena [%p] -> [%p]:\n", memory, (char *)memory + (size - 1));
    for (size_t i = 0; i < size; i += 16)
        print_16_bytes((char *)memory + i, (char *)memory + size);
    ft_printf("\n");
}

static void hexdump_arena_lst(t_arena_lst *first_node, char *type)
{
    ft_printf(BOLD "%s:\n" RESET, type);
    t_arena_lst *current_node = first_node;
    if (!current_node)
    {
        ft_printf(ITALIC "    Empty\n" RESET);
        return;
    }
    while (true)
    {
        hexdump_mmap((void *)current_node, current_node->arena_size);
        current_node = current_node->next_arena;
        if (current_node == first_node)
            break;
    }
}

static void hexdump_mmap_lst(t_mmap_lst *first_node)
{
    ft_printf(BOLD "BIG:\n" RESET);
    t_mmap_lst *current_node = first_node;
    if (!current_node)
    {
        ft_printf(ITALIC "  Empty\n" RESET);
        return;
    }
    while (true)
    {
        size_t *metadata = (size_t *)((char *)current_node + align16(sizeof(t_mmap_lst)));
        hexdump_mmap((void *)current_node, *metadata & ~1);
        current_node = current_node->next_mmap;
        if (current_node == first_node)
            break;
    }
}

void show_alloc_mem_ex(void)
{
    pthread_mutex_lock(&malloc_mutex);
    hexdump_arena_lst(g_alloc_arenas.arenas_lst[TINY_ARENA], "TINY");
    hexdump_arena_lst(g_alloc_arenas.arenas_lst[SMALL_ARENA], "SMALL");
    hexdump_mmap_lst(g_alloc_arenas.mmap_lst);
    pthread_mutex_unlock(&malloc_mutex);
}
