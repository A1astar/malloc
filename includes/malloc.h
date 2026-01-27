/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 17:32:40 by alacroix         ###   ########.fr       */
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

// MACROS
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
typedef struct s_arena_lst
{
	struct s_arena_lst *next_arena;
	struct s_arena_lst *prev_arena;
	size_t arena_type;
	size_t arena_size;
	size_t max_available;
	size_t nb_alloc;
} t_arena_lst;

typedef struct s_mmap_lst
{
	struct s_mmap_lst *next_mmap;
	struct s_mmap_lst *prev_mmap;
} t_mmap_lst;

typedef struct s_alloc_arenas
{
	t_arena_lst *arenas_lst[ARENA_TYPE];
	t_mmap_lst *mmap_lst;
	size_t total_alloc_bytes;
} t_alloc_arenas;

// GLOBAL VAR
extern t_alloc_arenas g_alloc_arenas;
extern pthread_mutex_t malloc_mutex;

// MALLOC
void *malloc(size_t size);
void *get_memblock_from_mmap(size_t requested_size);
void *get_memblock_from_arena(size_t arena_type, size_t requested_size);
void *choose_arena(t_arena_lst **arena, size_t arena_type, size_t requested_size);
void add_mmap_to_list(void **mapped_zone, t_mmap_lst **mmap_lst);

// FREE
void free(void *ptr);

// REALLOC
void *realloc(void *ptr, size_t size);

// SHOW ALLOC
void show_alloc_mem(void);
void show_alloc_mem_ex(void);

#endif
