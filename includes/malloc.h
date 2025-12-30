/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/30 11:44:27 by alacroix         ###   ########.fr       */
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
typedef struct s_alloc_pools
{
	void *tiny_mem_pool;
	void *small_mem_pool;
} t_alloc_pools;

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
extern	t_alloc_pools g_alloc_pools;

// FUNCTIONS
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

// BONUS FUNCTION

#endif
