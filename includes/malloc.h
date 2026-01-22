/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/22 12:51:02 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

// DEFINES
#define _GNU_SOURCE
#define BLOCKS_MAX_NB 100
#define TINY_MAX_SIZE 64
#define SMALL_MAX_SIZE 1024
#define TINY_ARENA 0
#define SMALL_ARENA 1
#define ARENA_TYPE 2

//MACROS
#define align16(size) ((size + (16 - 1)) & ~(16 - 1))

// INCLUDES
#include "../libft/includes/libft.h"
#include <pthread.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>

// DEBUG
#include <stdio.h>
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define ITALIC "\033[3m"

// STRUCTS
typedef struct arena_header
{
	void *next_arena;
	size_t size;
	size_t max_available;
	size_t nb_alloc;
}t_arena_header;

typedef struct s_arena
{
	size_t arena_size;
	void *arena_ptr;
} t_arena;

typedef struct s_alloc_arenas
{
	void *arenas[ARENA_TYPE];
} t_alloc_arenas;

// GLOBAL VAR
extern t_alloc_arenas g_alloc_arenas;

// MALLOC
void *ft_malloc(size_t size);
void init_arenas();
void create_arena(void **arena, size_t arena_type);
void *get_memblock_from_mmap(size_t requested_size);
void *get_memblock_from_arena(size_t arena_type, size_t requested_size);

// FREE
void ft_free(void *ptr);

// REALLOC
void *ft_realloc(void *ptr, size_t size);

//SHOW ALLOC
void ft_show_alloc_mem(void);
void ft_show_alloc_mem_ex(void);

#endif
