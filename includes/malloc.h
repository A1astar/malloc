/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/22 16:10:18 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

// INCLUDES
# include <../libft/include/libft.h>
# include <pthread.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <sys/time.h>

// DEFINES
# define TINY_MAX_SIZE 512
# define SMALL_MAX_SIZE 4096
# define MAX_NB_ALLOC 100
# define ALIGNEMENT_VALUE 16

// STRUCTS
typedef struct s_alloc_arena
{
	void *tiny_arena;
	void *small_arena;
} t_alloc_arena;

typedef struct s_metadata
{
	unsigned int block_size;
	unsigned int is_free;
} t_metadata;

typedef struct s_block
{
	t_metadata metadata;
	char *data;
} t_block;

// GLOBAL VAR
extern	t_alloc_arena g_alloc_arena = {0};

// FUNCTIONS
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

// BONUS FUNCTION

#endif
