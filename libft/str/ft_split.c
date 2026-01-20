/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:57:26 by alacroix          #+#    #+#             */
/*   Updated: 2025/04/07 11:13:05 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_separator(char c, char const *sep_set)
{
	while (*sep_set)
	{
		if (*sep_set == c)
			return (true);
		sep_set++;
	}
	return (false);
}

static char	*put_word(char const *str, char const *sep_set, size_t *index)
{
	char	*copy;
	size_t	word_len;

	word_len = 0;
	copy = NULL;
	while (str[*index] && is_separator(str[*index], sep_set))
		(*index)++;
	while (str[*index + word_len] && !is_separator(str[*index + word_len],
			sep_set))
		word_len++;
	copy = ft_strndup(&str[*index], word_len);
	if (!copy)
		return (NULL);
	*index += word_len;
	return (copy);
}

static int	words_count(char const *str, char const *sep_set)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && is_separator(*str, sep_set))
			str++;
		if (*str && !is_separator(*str, sep_set))
		{
			count++;
			while (*str && !is_separator(*str, sep_set))
				str++;
		}
	}
	return (count);
}

char	**ft_split(char const *str, char const *sep_set)
{
	char	**tab;
	size_t	words;
	size_t	tab_i;
	size_t	str_i;

	if (!str)
		return (NULL);
	tab_i = 0;
	str_i = 0;
	words = words_count(str, sep_set);
	tab = ft_calloc((words + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	while (tab_i < words)
	{
		tab[tab_i] = put_word(str, sep_set, &str_i);
		if (!tab[tab_i])
			return (ft_free_tab((void **)tab), NULL);
		tab_i++;
	}
	return (tab);
}
