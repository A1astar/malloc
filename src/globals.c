/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:00:00 by alacroix          #+#    #+#             */
/*   Updated: 2026/01/27 16:00:59 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_alloc_arenas g_alloc_arenas = {0};
pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
