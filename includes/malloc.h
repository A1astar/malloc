/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/20 13:07:58 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

// DEFINES
#define _GNU_SOURCE
#define BLOCKS_MAX_NB 100
#define TINY_MAX_SIZE 64
#define SMALL_MAX_SIZE 1024
#define TINY_ARNEA_PAGES 16
#define SMALL_ARNEA_PAGES 128
#define ALIGN_VAL 16

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

// STRUCTS
typedef struct s_arena
{
	size_t arena_size;
	void *arena_ptr;
} t_arena;

typedef struct s_alloc_arenas
{
	t_arena tiny_alloc_arena;
	t_arena small_alloc_arena;
} t_alloc_arenas;

// GLOBAL VAR
extern t_alloc_arenas g_alloc_arenas;

//ALIGN
static inline size_t align_to_16(size_t size)
{
	return (((size) + (ALIGN_VAL - 1)) & ~(ALIGN_VAL - 1));
}

static inline size_t align_to_pagesize(size_t size)
{
	size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
	return ((size + page_size - 1) / page_size) * page_size;
}

// MALLOC
void *malloc(size_t size);

void create_alloc_arena(t_arena *alloc_arena, size_t chunk_max_size);
void *expand_alloc_arena(t_arena *alloc_arena, size_t requested_size);

void *get_mapped_chunk(size_t requested_size);
void *get_arena_chunk(t_arena *alloc_arena, size_t requested_size);

// FREE
void free(void *ptr);

// REALLOC
void *realloc(void *ptr, size_t size);

//SHOW ALLOC
void show_alloc_mem(void);
void show_alloc_mem_ex(void);

#endif
