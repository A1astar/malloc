/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:09:16 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/22 15:18:09 by alacroix         ###   ########.fr       */
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

// BLOCK_STRUCT
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

// GLOBAL VARIABLE

extern t_alloc_arena alloc_arena = {0};

// FUNCTIONS
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

// BONUS FUNCTION
void	show_alloc_mem_ex(void);

#endif
