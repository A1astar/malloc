/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/19 16:07:55 by alacroix         ###   ########.fr       */
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
#include "../libft/include/libft.h"
#include <pthread.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>

//! --- FOR DEBUG PURPOSE ONLY ---
#include <stdio.h>

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

// FUNCTIONS
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);

// BONUS FUNCTION
void show_alloc_mem_ex(void);

#endif
